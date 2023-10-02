#version 410

uniform sampler2D demoDiffTex;
uniform sampler2D demoSpecTex;
uniform sampler2D demoNormalTex;


//uniform mat4 vertex_model_to_world;
uniform mat4 normal_model_to_world;
//uniform mat4 vertex_world_to_clip;

uniform vec3 light_position;
uniform int use_normal_mapping;
uniform vec3 camera_position;
uniform vec3 diffuse_colour;
uniform vec3 specular_colour;
uniform vec3 ambient_colour;
//uniform vec3 emissive_colour;
uniform float shininess_value;


in VS_OUT {
  vec3 tex_coord;
  vec3 vertex;
  vec3 normal;
  mat3 TBN;
  mat3 TBNp;
} fs_in;

out vec4 frag_color;

void main()
{
    vec3 N;
    if (use_normal_mapping == 1) {
        vec3 t_N = texture(demoNormalTex, fs_in.tex_coord.xy).rgb * 2.0 - 1.0;
        N = normalize( fs_in.TBNp * t_N );
        N = (normal_model_to_world*vec4(N,1)).xyz;
    } else {
        N = normalize(fs_in.normal);
    }
    
  	vec3 L = normalize(light_position - fs_in.vertex);
    vec3 V = normalize(camera_position - fs_in.vertex);
    vec3 R = normalize(reflect(-L,N));
    vec4 diffuse = texture(demoDiffTex, fs_in.tex_coord.xy) * clamp( dot(N, L), 0.0, 1.0);
    vec4 spec = texture(demoSpecTex, fs_in.tex_coord.xy)
              * vec4(specular_colour, 1)
              * pow( max(dot(R,V),0.0), shininess_value);
    //frag_color = vec4(1.0) * clamp(dot(normalize(fs_in.normal), L), 0.0, 1.0);
	frag_color = vec4(ambient_colour, 1)
                + diffuse
                + spec;
}
