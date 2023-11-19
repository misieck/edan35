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
layout (location = 2) in vec3 texcoord;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 binormal;
layout (location = 5) in vec2 sphereCoord;


uniform mat4 vertex_model_to_world;
uniform mat4 normal_model_to_world;
uniform mat4 vertex_world_to_clip;
uniform float elapsed_time_s;

// This is the custom output of this shader. If you want to retrieve this data
// from another shader further down the pipeline, you need to declare the exact
// same structure as in (for input), with matching name for the structure
// members and matching structure type. Have a look at
// shaders/EDAF80/diffuse.frag.
//out VS_OUT {
//	vec3 vertex;
//	vec3 normal;
//} vs_out;
out VS_OUT{
    vec3 tex_coord;
    vec3 vertex;
    vec3 normal;
    mat3 TBN;
    mat3 TBNp;
    vec2 sphereCoord;
} vs_out;

vec3 wave(vec2 pos, vec2 vel, float amp, float freq, float phase, float sharp, float time, inout float dg_dx, inout float dg_dz)
{
   float sin_p = sin( (pos.x * vel.x + pos.y * vel.y)*freq + phase*time) * 0.5 + 0.5;
   float cos_p = cos( (pos.x * vel.x + pos.y * vel.y)*freq + phase*time);

   float g = amp * pow(sin_p, sharp);

   
   dg_dx = dg_dx + 0.5 * freq * sharp * amp * pow(sin_p, sharp-1) * cos_p * vel.x;
   dg_dz = dg_dz + 0.5 * freq * sharp * amp * pow(sin_p, sharp-1) * cos_p * vel.y;

   return vec3(0,g,0);   
}

void main()
{

    vs_out.TBNp = mat3(tangent, binormal, normal);
    
    vs_out.TBN = mat3(vec3(vertex_model_to_world * vec4(tangent, 0.0)),
                      vec3(vertex_model_to_world * vec4(binormal, 0.0)),
                      vec3(normal_model_to_world * vec4(normal, 0.0))
                     );
    /*vs_out.TBN = mat3(vec3(vec4(tangent, 0.0  )* -1.0 ),
                      vec3(vec4(binormal, 0.0 ) * -1.0),
                      vec3(vec4(normal, 0.0   ) )
                     );
*/

    vec2 amp = vec2(1.5, 2.0) ;
    vec2 freq = vec2(0.3, 0.6);
    vec2 phase = vec2(0.5, 1.3);
    vec2 sharp = vec2(6.0, 2.0);
    vec4 dir = vec4(-1.0, 0.0, -0.7, 0.7);
    float dg_dx = 0;
    float dg_dz = 0;
    vec3 w1 = wave(sphereCoord, dir.xy, amp[0], freq[0], phase[0], sharp[0], elapsed_time_s, dg_dx, dg_dz);
    vec3 w2 = wave(sphereCoord, dir.zw, amp[1], freq[1], phase[1], sharp[1], elapsed_time_s, dg_dx, dg_dz);
    
    vec3 d_surf= vs_out.TBN * (w1+w2);
    
    
    //mat2 rot90 = mat2(vec2(0,1), vec2(1, 0));
    vs_out.tex_coord = vec3(texcoord.xy, 0);
    vs_out.vertex = vec3(vertex_model_to_world * vec4(vertex+d_surf, 1.0));
    vs_out.normal = vec3(normal_model_to_world * vec4(normal, 0.0));
    vs_out.sphereCoord = sphereCoord;
	gl_Position = vertex_world_to_clip * vertex_model_to_world * vec4(vs_out.vertex, 1.0);

}



