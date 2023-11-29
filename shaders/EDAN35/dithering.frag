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

uniform sampler2D screen_texture;
uniform sampler2D depth_texture;
uniform sampler2D normal_texture;
uniform sampler2D shadow_texture;

uniform vec2 inverse_screen_resolution;

uniform vec3 camera_position;

in vec4 gl_FragCoord;

/*
  	vec3 L = normalize(light_position - fs_in.vertex);
    vec3 V = normalize(camera_position - fs_in.vertex);
    vec3 R = normalize(reflect(-L,N));
    vec4 diffuse = texture(demoDiffTex, fs_in.tex_coord.xy) * clamp( dot(N, L), 0.0, 1.0);
    vec4 spec = texture(demoSpecTex, fs_in.tex_coord.xy)
              * vec4(specular_colour, 1)
              * pow( max(dot(R,V),0.0), shininess_value);

*/

out vec4 frag_color;

void main()
{
    int x = int(gl_FragCoord.x);
	int y = int(gl_FragCoord.y);
	float intensity = 0.95;
	vec4 dark = vec4(0.0, 0.0, 0.0, 1.0);
	vec4 bright = vec4(1.0, 1.0, 1.0, 1.0);

    vec2 texCoords = gl_FragCoord.xy * inverse_screen_resolution;
	vec4 rcol = texture(normal_texture, texCoords);
    mat4 dither_pattern = mat4(
	  -0.5,     0.0,    -0.375,   0.125,
       0.25,   -0.25,    0.375,  -0.125,
      -0.3125,  0.1875, -0.4375,  0.0625,
       0.4375, -0.0625,  0.3125, -0.1875
	);
	float bw = dot(vec3(0.3,0.55,0.15), rcol);
	float dp = bw + dither_pattern[x%4][y%4] * intensity;
	if (dp < 0.5) {
	  frag_color = dark;
	}
	else {
	  frag_color = bright;
	}
}
