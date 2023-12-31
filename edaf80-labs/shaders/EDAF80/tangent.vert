#version 410

layout (location = 0) in vec3 vertex;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 binormal;

uniform mat4 vertex_model_to_world;
uniform mat4 normal_model_to_world;
uniform mat4 vertex_world_to_clip;

out VS_OUT {
	vec3 tangent;
} vs_out;


void main()
{
	vs_out.tangent = normalize(vec3(normal_model_to_world * vec4(tangent, 0.0)));

	gl_Position = vertex_world_to_clip * vertex_model_to_world * vec4(vertex, 1.0);
}
