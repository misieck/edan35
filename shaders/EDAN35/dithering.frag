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
uniform samplerCube dither_texture;
uniform samplerCube dither_texture_bayer;
uniform sampler2D dither_simple_texture;
uniform sampler2D depth_texture;
uniform sampler2D dither_bigdot_texture;


uniform float camera_fov;
uniform vec3 camera_position;

uniform int use_cubemap;
uniform int use_blue;


layout (pixel_center_integer) in vec4 gl_FragCoord;

uniform vec2 inverse_screen_resolution;

out vec4 frag_color;

vec4 ordered_dithering(vec4 color)
{

    vec4 cam_offset = camera.view_projection * vec4(0.0, 0.0, -1.0, 1.0);
    // cam_offset = vec4(0);
    int x = 0;
    x = int((gl_FragCoord.x + cam_offset.x * 4/inverse_screen_resolution.x)); // + cam_offset.x/inverse_screen_resolution.x);
	int y = int((gl_FragCoord.y + cam_offset.x * 4/inverse_screen_resolution.y)); // + cam_offset.y/inverse_screen_resolution.y);
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
    float dither_color = dither_pattern[x%4][y%4];
	float dp = bw + dither_color * intensity;
	//float dp = bw + texture(dither_texture, cam_offset.xyz).x - 0.5; 
	if (dp < 0.5) {
	  return  dark;
	}
	else {
	  return bright;
	}


}

vec4 blue_dithering(vec4 color)
{

    vec4 cam_offset = camera.view_projection * vec4(0.0, 0.0, -1.0, 1.0);
    // cam_offset = vec4(0);
    int x = 0;
    x = int((gl_FragCoord.x + cam_offset.x * 4/inverse_screen_resolution.x)); // + cam_offset.x/inverse_screen_resolution.x);
	int y = int((gl_FragCoord.y + cam_offset.x * 4/inverse_screen_resolution.y)); // + cam_offset.y/inverse_screen_resolution.y);
	float intensity = 0.9999999999999;
	vec4 dark = vec4(0.2, 0.0, 0.0, 1.0);
	vec4 bright = vec4(1.0, 1.0, 1.0, 1.0);

    // dither_pattern = camera.view_projection * dither_pattern;
	float bw = dot(vec3(0.3,0.55,0.15), color.xyz);
    ivec2 tCoord;
    tCoord.x = int( gl_FragCoord.x)%1024;
    tCoord.y = int( gl_FragCoord.y)%1024;
    
    float dither_color = (texelFetch(dither_simple_texture,  tCoord, 0)).y;
    
	float dp = bw + dither_color - 0.5;
    //return vec4(vec3(dither_color), 1.0);
	
	if (dp < 0.5) {
	  return  dark;
	}
	else {
	  return bright;
	}


}

vec4 dot_dithering(vec4 color)
{

    vec4 cam_offset = camera.view_projection * vec4(0.0, 0.0, -1.0, 1.0);
    // cam_offset = vec4(0);
    int x = 0;
    x = int((gl_FragCoord.x + cam_offset.x * 4/inverse_screen_resolution.x)); // + cam_offset.x/inverse_screen_resolution.x);
	int y = int((gl_FragCoord.y + cam_offset.x * 4/inverse_screen_resolution.y)); // + cam_offset.y/inverse_screen_resolution.y);
	float intensity = 0.9999999999999;
	vec4 dark = vec4(0.2, 0.0, 0.0, 1.0);
	vec4 bright = vec4(1.0, 1.0, 1.0, 1.0);

    // dither_pattern = camera.view_projection * dither_pattern;
	float bw = dot(vec3(0.3,0.55,0.15), color.xyz);
    ivec2 tCoord;
    tCoord.x = int( gl_FragCoord.x)%128;
    tCoord.y = int( gl_FragCoord.y)%128;
    
    float dither_color = (texelFetch(dither_bigdot_texture,  tCoord, 0)).y;
    
	float dp = bw + dither_color - 0.5;
    //return vec4(vec3(dither_color), 1.0);
	
	if (dp < 0.5) {
	  return  dark;
	}
	else {
	  return bright;
	}


}



vec4 cube_dithering(vec4 color, vec3 dir)
{
	float intensity = 0.9999999999999;
	vec4 dark = vec4(0.2, 0.0, 0.0, 1.0);
	vec4 bright = vec4(1.0, 1.0, 1.0, 1.0);


	float bw = dot(vec3(0.3,0.55,0.15), color.xyz);
	float dp = (texture(dither_texture, dir).x - 0.5);
	//return vec4(dp);
	if (bw + dp < 0.5) {
	  return  dark;
	}
	else {
	  return bright;
	}
}

vec4 cube_dithering_bayer(vec4 color, vec3 dir)
{
	float intensity = 0.9999999999999;
	vec4 dark = vec4(0.2, 0.0, 0.0, 1.0);
	vec4 bright = vec4(1.0, 1.0, 1.0, 1.0);


	float bw = dot(vec3(0.3,0.55,0.15), color.xyz);
	float dp = (texture(dither_texture_bayer, dir).x - 0.5);
	//return vec4(dp);
	if (bw + dp < 0.5) {
	  return  dark;
	}
	else {
	  return bright;
	}
}

//bonobo::displayTexture({-0.95f,  0.55f}, {-0.55f,  0.95f}, textures[toU(Texture::ShadowMap)],                 samplers[toU(Sampler::Linear)], {0, 0, 0, -1}, glm::uvec2(framebuffer_width, framebuffer_height), true, lightProjectionNearPlane, lightProjectionFarPlane);

float near = 0.01*100;
float far = 20*100;
bool linearise = true;

float lineariseDepth(float value)
{
	return (2.0 * near) / (far + near - value * (far - near));
}

vec4 depth_val(sampler2D tex, vec2 coord)
{
    vec4 result;
    ivec4 swizzle = ivec4(0,0,0,-1);
	vec4 value = texture(tex, coord);
	for (int i = 0; i < 4; ++i)
		result[i] = (0 <= swizzle[i]) && (swizzle[i] <= 3)
		          ? (linearise ? lineariseDepth(value[swizzle[i]]) : value[swizzle[i]])
		          : 1.0;
    return result;
}


void main()
{
	ivec2 pixel_coord = ivec2(gl_FragCoord.xy);
    vec2 texCoords = gl_FragCoord.xy * inverse_screen_resolution;
    
    float D = texture(depth_texture, texCoords).x *2.0 - 1.0;
    vec4 clipSpacePosition = vec4(texCoords*2.0f - vec2(1.0f), D, 1 );
    vec4 worldSpacePosition = camera.view_projection_inverse*clipSpacePosition;
    worldSpacePosition /= worldSpacePosition.w;
    vec3 V = normalize(worldSpacePosition.xyz - camera_position);


	vec3 diffuse  = texelFetch(diffuse_texture,  pixel_coord, 0).rgb;
    //diffuse  = texelFetch(dither_simple_texture,  pixel_coord, 0).rgb;
	vec3 specular = texelFetch(specular_texture, pixel_coord, 0).rgb;

	vec3 light_d  = texelFetch(light_d_texture,  pixel_coord, 0).rgb;
	vec3 light_s  = texelFetch(light_s_texture,  pixel_coord, 0).rgb;
	const vec3 ambient = vec3(0.15);

	vec4 rcol =  vec4((ambient + light_d) * diffuse + light_s * specular, 1.0);


    //frag_color = texture(depth_texture, gl_FragCoord.xy * inverse_screen_resolution);
    //frag_color = texelFetch(specular_texture, pixel_coord, 0);
    //frag_color = ordered_dithering(rcol);
	if (use_cubemap) {
	  if (use_blue) {
        frag_color = cube_dithering(rcol, V);
	  }
	  else {
	    frag_color = cube_dithering_bayer(rcol, V);
	  }
	}
	else {
	  if (use_blue) {
        frag_color = blue_dithering(rcol);   
	  }
	  else {
	    frag_color = ordered_dithering(rcol);
	  }
	}
    //frag_color = depth_val(depth_texture, gl_FragCoord.xy * inverse_screen_resolution);
    
        
}


