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

uniform mat4 vertex_model_to_world;
uniform mat4 normal_model_to_world;
uniform mat4 vertex_world_to_clip;

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
} vs_out;

void main()
{
    vs_out.TBNp = mat3(tangent, binormal, normal);
    
    vs_out.TBN = mat3(vec3(normal_model_to_world * vec4(tangent, 0.0)),
                      vec3(normal_model_to_world * vec4(binormal, 0.0)),
                      vec3(normal_model_to_world * vec4(normal, 0.0))
                     );
    /*vs_out.TBN = mat3(vec3(vec4(tangent, 0.0  )* -1.0 ),
                      vec3(vec4(binormal, 0.0 ) * -1.0),
                      vec3(vec4(normal, 0.0   ) )
                     );
*/
    //mat2 rot90 = mat2(vec2(0,1), vec2(1, 0));
    vs_out.tex_coord = vec3(texcoord.xy, 0);
    vs_out.vertex = vec3(vertex_model_to_world * vec4(vertex, 1.0));
    vs_out.normal = vec3(normal_model_to_world * vec4(normal, 0.0));

	gl_Position = vertex_world_to_clip * vertex_model_to_world * vec4(vertex, 1.0);

}



