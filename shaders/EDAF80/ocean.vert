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

uniform mat4 vertex_model_to_world;
uniform mat4 normal_model_to_world;
uniform mat4 vertex_world_to_clip;
uniform float elapsed_time_s;
uniform float size;

// This is the custom output of this shader. If you want to retrieve this data
// from another shader further down the pipeline, you need to declare the exact
// same structure as in (for input), with matching name for the structure
// members and matching structure type. Have a look at
// shaders/EDAF80/diffuse.frag.
out VS_OUT {
	vec3 vertex;
	vec3 normal;
    mat4x2 normalWavesCoord;
    mat3 TBN;
} vs_out;


vec3 wave(vec2 pos, vec2 vel, float amp, float freq, float phase, float sharp, float time, inout vec3 T, inout vec3 B, inout vec3 N)
{
   float sin_p = sin((pos.x * vel.x + pos.y * vel.y) * freq + phase * time) * 0.5 + 0.5;
   float cos_p = cos((pos.x * vel.x + pos.y * vel.y) * freq + phase * time);

   float g = amp * pow(sin_p, sharp);
   float dg_dx = 0.5 * freq * sharp * amp * pow(sin_p, sharp-1) * cos_p * vel.x;
   float dg_dz = 0.5 * freq * sharp * amp * pow(sin_p, sharp-1) * cos_p * vel.y;

   T += (vec3(0,dg_dz,1));
   B += (vec3(1,dg_dx,0));
   N += (vec3(-dg_dx, 1, -dg_dz));
   return vec3(0,g,0);   

}  

mat4x2 getNormalWavesCoord(float time)
{

  vec2 texScale = vec2(7, 4);
  float normalTime = mod(time, 100.0);
  vec2 normalSpeed = vec2(-0.05, 0.0);
  vec2 texCoord = vertex.xz / size;
  mat4x2 ret = mat4x2(0);
  const ivec4 scale_mults = ivec4(1, 2, 4, 7);
  const ivec4 speed_mults = ivec4(1, 4, 8, 12);
  for (int i = 0; i<4; ++i)
  {
    
    ret[i].xy = (texCoord.xy * texScale   * scale_mults[i] +
                    normalTime * normalSpeed * speed_mults[i]);
  }
  
  return ret;
}



void main()
{
    vec2 amp = vec2(1.0, 0.5) ;
    vec2 freq = vec2(0.2, 0.4);
    vec2 phase = vec2(0.5, 1.3);
    vec2 sharp = vec2(2.0, 2.0);
    vec4 dir = vec4(-1.0, 0.0, -0.7, 0.7);
    vec3 T = vec3(0.0);
    vec3 B = vec3(0.0);
    vec3 N = vec3(0.0);
    vec3 w1 = wave(vertex.xz, dir.xy, amp[0], freq[0], phase[0], sharp[0], elapsed_time_s, T, B, N);
    vec3 w2 = wave(vertex.xz, dir.zw, amp[1], freq[1], phase[1], sharp[1], elapsed_time_s, T, B, N); 
    vec3 v =  vertex + w1 + w2;

    vs_out.TBN = mat3(normalize(T),normalize(B),normalize(N));

	vs_out.vertex = vec3(vertex_model_to_world * vec4(v, 1.0));
	vs_out.normal = normalize( (normal_model_to_world * vec4(N, 0.0)).xyz );
    vs_out.normalWavesCoord = getNormalWavesCoord(elapsed_time_s);

	gl_Position = vertex_world_to_clip * vertex_model_to_world * vec4(v, 1.0);
}



