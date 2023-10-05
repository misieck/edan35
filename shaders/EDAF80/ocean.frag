#version 410

uniform mat4 normal_model_to_world;
uniform vec3 camera_position;
uniform samplerCube skybox;
uniform sampler2D wavesNormal;
uniform int use_normal_mapping;
uniform int use_refractions;
uniform int show_fresnel;
uniform int show_only_color;

in VS_OUT {
    vec3 vertex;
	vec3 normal;
    mat4x2 normalWavesCoord;
    mat3 TBN;
    vec3 col;
    
} fs_in;

out vec4 frag_color;

const vec4 water_deep = vec4(0.0, 0.0, 0.1, 1.0);
const vec4 water_shallow = vec4(0.0, 0.5, 0.5, 1.0);
const float n1 = 1.0;
const float n2 = 1.333;
// this is tangent space
vec3 bumpWave()
{
    vec3 ret = vec3(0);
    for (int i = 0; i<3; ++i)
    {
        vec4 tx = texture(wavesNormal, fs_in.normalWavesCoord[i]);
        ret += (tx.rgb) * 2.0 - 1.0;;
    }
    //return normalize(fs_in.col);
    return normalize(ret);
}



void main()
{
    float R0 = pow((n1-n2)/(n1+n2), 2);
    float eta = n1/n2;
    //R0 = 0.02037;
  
    vec3 bumpN = (fs_in.TBN * bumpWave());
    vec3 N = normalize(fs_in.normal);
    if (use_normal_mapping == 1)
    {
        N = (normal_model_to_world * vec4(bumpN, 1 )).xyz;
        //N = normalize(N);
    }
          
    //vec3 light_position = vec3(1, 13.0, 1);
	//vec3 L = normalize(light_position - fs_in.vertex);
    vec3 V = normalize(camera_position - fs_in.vertex);


    float facing_factor = 1.0 - max(dot(V,N), 0.0);
	frag_color = mix(water_deep, water_shallow, facing_factor);

    if (show_only_color == 1) return;
    float fresnel = 1.0;
    if (use_refractions == 1){
      fresnel = R0 + (1.0 - R0) * pow( facing_factor, 5);
    }
    
    vec3 reflection = normalize(reflect(-V, N));
    vec3 refraction = normalize(refract(-V, N, eta));
    frag_color =  (frag_color + fresnel*texture(skybox, reflection) + (1-fresnel)*texture(skybox, refraction));



    // frag_color = vec4( normalize( vec3( (dot(V,N)+1)/2  ) ) ,1 );
   //
    if (show_fresnel == 1){
      vec3 D = vec3(facing_factor);
      //D = (fs_in.TBN[2]*0.5+0.5);
      frag_color = vec4(   (D)   , 1.0 );
    }
}
