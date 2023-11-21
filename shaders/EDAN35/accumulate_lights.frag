#version 410

struct ViewProjTransforms
{
	mat4 view_projection; // mCamera.GetWorldToClipMatrix();
	mat4 view_projection_inverse; // mCamera.GetClipToWorldMatrix();
};

layout (std140) uniform CameraViewProjTransforms
{
	ViewProjTransforms camera;
};

layout (std140) uniform LightViewProjTransforms
{
	ViewProjTransforms lights[4];
};

uniform int light_index;

uniform sampler2D depth_texture;
uniform sampler2D normal_texture;
uniform sampler2D shadow_texture;

uniform vec2 inverse_screen_resolution;

uniform vec3 camera_position;

uniform vec3 light_color;
uniform vec3 light_position;
uniform vec3 light_direction;
uniform float light_intensity;
uniform float light_angle_falloff;

in vec4 gl_FragCoord;

layout (location = 0) out vec4 light_diffuse_contribution;
layout (location = 1) out vec4 light_specular_contribution;

/*
  	vec3 L = normalize(light_position - fs_in.vertex);
    vec3 V = normalize(camera_position - fs_in.vertex);
    vec3 R = normalize(reflect(-L,N));
    vec4 diffuse = texture(demoDiffTex, fs_in.tex_coord.xy) * clamp( dot(N, L), 0.0, 1.0);
    vec4 spec = texture(demoSpecTex, fs_in.tex_coord.xy)
              * vec4(specular_colour, 1)
              * pow( max(dot(R,V),0.0), shininess_value);

*/

void main()
{
    vec2 texCoords = gl_FragCoord.xy * inverse_screen_resolution;
    vec3 Ntex = texture(normal_texture, texCoords).xyz;
    vec3 N = texture(normal_texture, texCoords).xyz * 2.0f - 1.0f;
   
    
    

    float shininess_value = 0.2f; 
    vec3 specular_color = vec3(1.0f, 1.0f, 1.0f);
  
	vec2 shadowmap_texel_size = 1.0f / textureSize(shadow_texture, 0);

    float D = texture(depth_texture, texCoords).x *2.0 - 1.0;
    vec4 clipSpacePosition = vec4(texCoords*2.0f - vec2(1.0f), D, 1 );
    vec4 worldSpacePosition = camera.view_projection_inverse*clipSpacePosition;
    worldSpacePosition /= worldSpacePosition.w;
    vec4 vertex = worldSpacePosition;
    vec3 distL = (light_position - vertex.xyz)/350;
    vec3 L = normalize(distL);
    vec3 R = normalize(reflect(-L,N));
    vec3 V = normalize(camera_position - vertex.xyz);

    float x_45 = 0.7071067f; //dot(45 degrees)
    float x_40 = 0.7671067f;
    float x_35 = 0.81915f; 
    float x0 = x_35;
    float angle_falloff = dot(normalize(light_direction), -L);
    angle_falloff = clamp((angle_falloff - x0) / (1-x0),0.0,1.0) ;
    float dist_falloff = dot(distL, distL); 
    
    vec4 test = vec4(light_color * clamp( dot(N, L), 0.0, 1.0), 1); //vec4(0.2, 0.0, 0.0, 1.0);
    //test = ((vertex * .0012f)+vec4(1.0))*0.5f;
    //test = vec4(vec3(dot(Ntex,L)), 1);
    //test = vec4(vec3(angle_falloff), 1);
    if ( (test.x) < 0.0f ){
      // test = vec4(1.0f, 0.0f, 1.0f, 1.0f);
    }

   // test = vec4(light_position*0.002f, 1);
    //test = vec4((L +1.0f)*0.5f,1);
	light_diffuse_contribution  = test*angle_falloff/dist_falloff;
	light_specular_contribution = vec4(specular_color*pow( max(dot(R,V),0.0), shininess_value), 1);
    light_specular_contribution = light_specular_contribution * angle_falloff / dist_falloff;
}
