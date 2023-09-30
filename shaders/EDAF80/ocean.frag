#version 410

uniform vec3 camera_position;

in VS_OUT {
    vec3 vertex;
	vec3 normal;
} fs_in;

out vec4 frag_color;


const vec4 water_deep = vec4(0.0,0.0,0.1, 1.0);
const vec4 water_shallow = vec4(0.0, 0.5, 0.5, 1.0);


void main()
{
    vec3 light_position = vec3(0.5, 3.0, -0.6);
	vec3 L = normalize(light_position - fs_in.vertex);
    vec3 V = normalize(camera_position - fs_in.vertex);
    float facing_factor = 1 - max(dot(V,fs_in.normal), 0);
	frag_color = mix(water_deep, water_shallow, facing_factor);
      //vec4(1.0) *clamp(dot(normalize(fs_in.normal), L), 0.0, 1.0);
}
