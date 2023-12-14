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
uniform sampler2D normal_texture;

uniform sampler2D dither_bigdot_texture;


uniform float camera_fov;
uniform vec3 camera_position;

uniform bool use_cubemap;
uniform bool use_blue;
uniform bool add_sobel;
uniform bool add_white_sobel;
uniform bool only_sobel;
uniform bool turn_on_dithering;
uniform float brightness;
uniform float intensity;
uniform float edginess;


layout (pixel_center_integer) in vec4 gl_FragCoord;

uniform vec2 inverse_screen_resolution;

out vec4 frag_color;

float ordered_dithering(vec4 color)
{

    vec4 cam_offset = camera.view_projection * vec4(0.0, 0.0, -1.0, 1.0);
     int x = 0;
    x = int((gl_FragCoord.x + cam_offset.x * 4/inverse_screen_resolution.x)); // + cam_offset.x/inverse_screen_resolution.x);
	int y = int((gl_FragCoord.y + cam_offset.x * 4/inverse_screen_resolution.y)); // + cam_offset.y/inverse_screen_resolution.y);
	
    mat4 dither_pattern = mat4(
	  -0.5,     0.0,    -0.375,   0.125,
       0.25,   -0.25,    0.375,  -0.125,
      -0.3125,  0.1875, -0.4375,  0.0625,
       0.4375, -0.0625,  0.3125, -0.1875
	) ;

 	float bw = dot(vec3(0.3,0.55,0.15), color.xyz);
    float dither_color = dither_pattern[x%4][y%4];
	float dp = bw + dither_color * intensity;
	//float dp = bw + texture(dither_texture, cam_offset.xyz).x - 0.5; 

    return dp;
}

float blue_dithering(vec4 color)
{

    vec4 cam_offset = camera.view_projection * vec4(0.0, 0.0, -1.0, 1.0);
    int x = 0;
    x = int((gl_FragCoord.x + cam_offset.x * 4/inverse_screen_resolution.x)); // + cam_offset.x/inverse_screen_resolution.x);
	int y = int((gl_FragCoord.y + cam_offset.x * 4/inverse_screen_resolution.y)); // + cam_offset.y/inverse_screen_resolution.y);

	float bw = dot(vec3(0.3,0.55,0.15), color.xyz);
    ivec2 tCoord;
    tCoord.x = int( gl_FragCoord.x)%1024;
    tCoord.y = int( gl_FragCoord.y)%1024;
    
    float dither_color = (texelFetch(dither_simple_texture,  tCoord, 0)).y;
    
	float dp = bw + (dither_color - 0.5)*intensity;
    return dp;
}

float dot_dithering(vec4 color)
{

    vec4 cam_offset = camera.view_projection * vec4(0.0, 0.0, -1.0, 1.0);
    // cam_offset = vec4(0);
    int x = 0;
    x = int((gl_FragCoord.x + cam_offset.x * 4/inverse_screen_resolution.x)); // + cam_offset.x/inverse_screen_resolution.x);
	int y = int((gl_FragCoord.y + cam_offset.x * 4/inverse_screen_resolution.y)); // + cam_offset.y/inverse_screen_resolution.y);
	vec4 dark = vec4(0.2, 0.0, 0.0, 1.0);
	vec4 bright = vec4(1.0, 1.0, 1.0, 1.0);

    // dither_pattern = camera.view_projection * dither_pattern;
	float bw = dot(vec3(0.3,0.55,0.15), color.xyz);
    ivec2 tCoord;
    tCoord.x = int( gl_FragCoord.x)%128;
    tCoord.y = int( gl_FragCoord.y)%128;
    
    float dither_color = (texelFetch(dither_bigdot_texture,  tCoord, 0)).y;
    
	float dp = bw + (dither_color - 0.5)*intensity;
    return dp;
	
}



float cube_dithering(vec4 color, vec3 dir)
{
	vec4 dark = vec4(0.2, 0.0, 0.0, 1.0);
	vec4 bright = vec4(1.0, 1.0, 1.0, 1.0);

	float bw = dot(vec3(0.3,0.55,0.15), color.xyz);
	float dp = (texture(dither_texture, dir).x - 0.5)*intensity;
    return bw+dp;
}

float cube_dithering_bayer(vec4 color, vec3 dir)
{
	vec4 dark = vec4(0.2, 0.0, 0.0, 1.0);
	vec4 bright = vec4(1.0, 1.0, 1.0, 1.0);

	float bw = dot(vec3(0.3,0.55,0.15), color.xyz);
	float dp = (texture(dither_texture_bayer, dir).x - 0.5)*intensity;
    return bw + dp;
}


float near = 0.01*100;
float far = 18*100;
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


float sobel_kernel(mat3 image){
  mat3 sx = mat3( 
    1.0, 2.0, 1.0, 
    0.0, 0.0, 0.0, 
   -1.0, -2.0, -1.0 
  );
  mat3 sy = mat3( 
    1.0, 0.0, -1.0, 
    2.0, 0.0, -2.0, 
    1.0, 0.0, -1.0 
  );

  float gx = dot(sx[0], image[0]) + dot(sx[1], image[1]) + dot(sx[2], image[2]); 
  float gy = dot(sy[0], image[0]) + dot(sy[1], image[1]) + dot(sy[2], image[2]);

  float g = sqrt(pow(gx, 2.0)+pow(gy, 2.0));
  return g;
}



float sobel_depth(vec2 coord, sampler2D texture){
  mat3 image;
  for (int i=0; i<3; i++) {
    for (int j=0; j<3; j++){
      vec3 tex  = vec3(depth_val(texture, coord + vec2(i-1,j-1)));
      image[i][j] = max (tex.z, max(tex.x, tex.y)); 
    }
  }
  return sobel_kernel(image);
}



//bonobo::displayTexture({-0.95f,  0.55f}, {-0.55f,  0.95f}, textures[toU(Texture::ShadowMap)],                 samplers[toU(Sampler::Linear)], {0, 0, 0, -1}, glm::uvec2(framebuffer_width, framebuffer_height), true, lightProjectionNearPlane, lightProjectionFarPlane);

void sobel2_make_kernel(inout vec4 n[9], sampler2D tex, ivec2 coord)
{
	int w = 1 ;
	int h = 1 ; 
    n[0] = texelFetch(tex, coord + ivec2( -w, -h), 0);
	n[1] = texelFetch(tex, coord + ivec2( 0, -h), 0);
	n[2] = texelFetch(tex, coord + ivec2(  w, -h), 0);
	n[3] = texelFetch(tex, coord + ivec2( -w, 0), 0);
	n[4] = texelFetch(tex, coord, 0);
	n[5] = texelFetch(tex, coord + ivec2(  w, 0), 0);
	n[6] = texelFetch(tex, coord + ivec2( -w, h), 0);
	n[7] = texelFetch(tex, coord + ivec2(  0, h), 0);
	n[8] = texelFetch(tex, coord + ivec2(  w, h), 0);
}

vec4 sobel2(sampler2D texture, sampler2D depth, ivec2 coord) 
{
	vec4 n[9];
	sobel2_make_kernel( n, texture, coord );

	vec4 sobel_edge_h = n[2] + (2.0*n[5]) + n[8] - (n[0] + (2.0*n[3]) + n[6]);
  	vec4 sobel_edge_v = n[0] + (2.0*n[1]) + n[2] - (n[6] + (2.0*n[7]) + n[8]);
	vec4 sobel = sqrt((sobel_edge_h * sobel_edge_h) + (sobel_edge_v * sobel_edge_v));
    float sob = max (sobel.z, max(sobel.x, sobel.y));
    sob = length(sobel.xyz);
    float D =  texelFetch(depth, coord, 0).x;
    D = 1.2*lineariseDepth(D);
    
    if (sob >(1-edginess)) return vec4( normalize(sobel.rgb) * (max(1.0-D, 0))  , 1.0);
    else return vec4(0.0, 0.0, 0.0, 1.0);
}


void main()
{
	ivec2 pixel_coord = ivec2(gl_FragCoord.xy);
    vec2 texCoords = gl_FragCoord.xy * inverse_screen_resolution;
    
    float D = texture(depth_texture, texCoords).x;
    vec4 clipSpacePosition = vec4(texCoords*2.0f - vec2(1.0f), D, 1 );
    vec4 worldSpacePosition = camera.view_projection_inverse*clipSpacePosition;
    worldSpacePosition /= worldSpacePosition.w;
    vec3 V = normalize(worldSpacePosition.xyz - camera_position);


	vec3 diffuse  = texelFetch(diffuse_texture,  pixel_coord, 0).rgb;
    vec3 specular = texelFetch(specular_texture, pixel_coord, 0).rgb;

	vec3 light_d  = texelFetch(light_d_texture,  pixel_coord, 0).rgb;
	vec3 light_s  = texelFetch(light_s_texture,  pixel_coord, 0).rgb;
	const vec3 ambient = vec3(0.15);

	vec4 rcol =  vec4((ambient + light_d) * diffuse + light_s * specular, 1.0);

    vec4 N = texture(normal_texture, texCoords);
    
    vec4 sobel_d = vec4(vec3(sobel_depth(texCoords, depth_texture)), 1);

    //sobel_d = depth_val(depth_texture, texCoords);
    vec4 sobel_n = sobel2(normal_texture, depth_texture, pixel_coord);
    vec4 sobel = sobel_n;

    if (! add_white_sobel){
      sobel = -sobel;
    }

    if (only_sobel){
      rcol = vec4(-0.01);
    }
    
    if (add_sobel){
      rcol = rcol + sobel;
    }
    //rcol =  1-sobel_n-0.02;
    
    float dithering=0.0;
    if (turn_on_dithering){
      if (use_cubemap) {
        if (use_blue) {
          dithering = cube_dithering(rcol, V);
        }
        else {
          dithering = cube_dithering_bayer(rcol, V);
        }
      }
      else {
        if (use_blue) {
          dithering = blue_dithering(rcol);   
        }
        else {
          dithering = ordered_dithering(rcol);
        }
      }
    }

    vec4 dark = vec4(0.2, 0.0, 0.0, 1.0);
	vec4 bright = vec4(1.0, 1.0, 1.0, 1.0);

    
    if (dithering < (1-brightness) ) {
	  frag_color =  dark;
	}
	else {
	  frag_color =  bright;
	}

    if (!turn_on_dithering){
      frag_color = rcol;
    }
    //frag_color = vec4(vec3(lineariseDepth(D)), 1.0);//depth_val(depth_texture, gl_FragCoord.xy * inverse_screen_resolution);
        
}


