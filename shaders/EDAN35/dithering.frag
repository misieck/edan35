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

uniform sampler2D diffuse_texture;
uniform sampler2D specular_texture;
uniform sampler2D light_d_texture;
uniform sampler2D light_s_texture;

uniform float camera_fov;



layout (pixel_center_integer) in vec4 gl_FragCoord;

uniform vec2 inverse_screen_resolution;

out vec4 frag_color;

vec4 ordered_dithering(vec4 color)
{

    vec4 cam_offset = camera.view_projection * vec4(0.0, 0.0, -1.0, 1.0);
   // cam_offset = vec4(0);
    int x = int(gl_FragCoord.x + cam_offset.x * 1/inverse_screen_resolution.x);
	int y = int(gl_FragCoord.y + cam_offset.y * 1/inverse_screen_resolution.y);
	float intensity = 0.9999999999999;
	vec4 dark = vec4(0.2, 0.0, 0.0, 1.0);
	vec4 bright = vec4(1.0, 1.0, 1.0, 1.0);

    mat4 dither_pattern = mat4(
	  -0.5,     0.0,    -0.375,   0.125,
       0.25,   -0.25,    0.375,  -0.125,
      -0.3125,  0.1875, -0.4375,  0.0625,
       0.4375, -0.0625,  0.3125, -0.1875
	) ;

    mat4 dither_pattern2 = mat4(
	  -0.5,     0.0,    -0.375,   0.125,
       0.25,   -0.25,    0.375,  -0.125,
      -0.3125,  0.1875, -0.4375,  0.0625,
       0.4375, -0.0625,  0.3125, -0.1875
	) ;


   // dither_pattern = camera.view_projection * dither_pattern;
	float bw = dot(vec3(0.3,0.55,0.15), color.xyz);
	float dp = bw + dither_pattern[x%4][y%4] * intensity;
	if (dp < 0.5) {
	  return  dark;
	}
	else {
	  return bright;
	}


}

void main()
{
	ivec2 pixel_coord = ivec2(gl_FragCoord.xy);

	vec3 diffuse  = texelFetch(diffuse_texture,  pixel_coord, 0).rgb;
	vec3 specular = texelFetch(specular_texture, pixel_coord, 0).rgb;

	vec3 light_d  = texelFetch(light_d_texture,  pixel_coord, 0).rgb;
	vec3 light_s  = texelFetch(light_s_texture,  pixel_coord, 0).rgb;
	const vec3 ambient = vec3(0.15);

	vec4 rcol =  vec4((ambient + light_d) * diffuse + light_s * specular, 1.0);


    frag_color = ordered_dithering(rcol);

    
        
}
