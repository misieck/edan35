#version 410

uniform sampler2D diffTex;
uniform sampler2D specTex;
uniform sampler2D normalTex;


//uniform mat4 vertex_model_to_world;
uniform mat4 normal_model_to_world;
//uniform mat4 vertex_world_to_clip;

uniform vec3 light_position;
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
  vec2 sphereCoord;
} fs_in;

out vec4 frag_color;

const vec4 water_deep = vec4(0.0, 0.0, 0.1, 1.0);
const vec4 water_shallow = vec4(0.0, 0.5, 0.5, 1.0);
float n1 = 1.0;
float n2 = 1.333;
int show_only_color = 1;
void main()
{
    vec3 N;
    if (false) {
        vec3 t_N = texture(normalTex, fs_in.tex_coord.xy).rgb * 2.0 - 1.0;
        N = normalize( fs_in.TBN * t_N );
        N = (normal_model_to_world*vec4(N,1)).xyz;
    } else {
        N = normalize(fs_in.normal);
    }
    
  	vec3 L = normalize(light_position - fs_in.vertex);
    vec3 V = normalize(camera_position - fs_in.vertex);
    vec3 R = normalize(reflect(-L,N));
    vec4 diffuse = texture(diffTex, fs_in.tex_coord.xy) * clamp( dot(N, L), 0.0, 1.0);
    vec4 spec = texture(specTex, fs_in.tex_coord.xy)
              * vec4(specular_colour, 1)
              * pow( max(dot(R,V),0.0), shininess_value);
    //frag_color = vec4(1.0) * clamp(dot(normalize(fs_in.normal), L), 0.0, 1.0);
	frag_color = vec4(ambient_colour, 1)
                + diffuse
                + spec;





    float R0 = pow((n1-n2)/(n1+n2), 2);
    float eta = n1/n2;
    V = normalize(camera_position - fs_in.vertex); // normalize(camera_position - fs_in.vertex);


    float facing_factor = 1.0 - max(dot(V,N), 0.0);
	frag_color = mix(water_deep, water_shallow, facing_factor);

    if (show_only_color == 1) return;
    float fresnel = 1.0;
    
    fresnel = R0 + (1.0 - R0) * pow( 1-dot(V,N), 5.0);
    
    
    vec3 reflection = normalize(reflect(-V, N));
    vec3 refraction = normalize(refract(-V, N, eta));
    //frag_color =  (frag_color + fresnel*texture(skybox, reflection) + (1-fresnel)*texture(skybox, refraction));

}
