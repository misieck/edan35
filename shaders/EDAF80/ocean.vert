#version 410

// Remember how we enabled vertex attributes in assignment 2 and attached some
// data to each of them, here we retrieve that data. Attribute 0 pointed to the
// vertices inside the OpenGL buffer object, so if we say that our input
// variable `vertex` is at location 0, which corresponds to attribute 0 of our
// vertex array, vertex will be effectively filled with vertices from our
// buffer.
// Similarly, normal is set to location 1, which corresponds to attribute 1 of
// the vertex array, and therefore will be filled with normals taken out of our
// buffer.
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

uniform mat4 vertex_model_to_world;
uniform mat4 normal_model_to_world;
uniform mat4 vertex_world_to_clip;
uniform float elapsed_time_s;

// This is the custom output of this shader. If you want to retrieve this data
// from another shader further down the pipeline, you need to declare the exact
// same structure as in (for input), with matching name for the structure
// members and matching structure type. Have a look at
// shaders/EDAF80/diffuse.frag.
out VS_OUT {
	vec3 vertex;
	vec3 normal;
} vs_out;

vec3 wave(vec2 pos, vec2 vel, float amp, float freq, float phase, float sharp, float time, out vec3 T, out vec3 B, out vec3 N)
{
   float sin_p = sin((pos.x * vel.x + pos.y * vel.y) * freq + phase * time) * 0.5 + 0.5;
   float cos_p = cos((pos.x * vel.x + pos.y * vel.y) * freq + phase * time)
   float g = amp * pow(sin_p, sharp);
   float dg_dx = 0.5 * freq * sharp * pow(sin_p, sharp-1) * cos_p * pos.x;
   float dg_dy = 0.5 * freq * sharp * pow(sin_p, sharp-1) * cos_p * pos.y;
   T = vec3(0,1,dg_dy);
   B = vec3(1,0,dg_dx);
   N = vec3(-dg_dx, -dg_dy, 1);
   return vec3(0,0,g);
   

}


void main()
{
    vec2 amp = vec2(1.0, 0.5) ;
    vec2 freq = vec2(0.2, 0.4);
    vec2 phase = vec2(0.5, 1.3);
    vec2 sharp = vec2(2.0, 2.0);
    vec4 dir = vec4(-1.0, 0.0, -0.7, 0.7);
    vec3 T;
    vec3 B;
    vec3 N;
	vs_out.vertex = wave(vertex.xy, dir.xy, amp[0], freq[0], phase[0], sharp[0], elapsed_time_s, T, B, N);
    
	vs_out.normal = vec3(normal_model_to_world * vec4(normal, 0.0));

	gl_Position = vertex_world_to_clip * vertex_model_to_world * vec4(vertex, 1.0);
}



