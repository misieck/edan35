#version 410

in VS_OUT {
	vec3 normal;
} fs_in;

out vec4 frag_color;

void main()
{
	frag_color = vec4((normalize(round(fs_in.normal*1.3f)/1.3) + 1.0) * 0.5, 1.0);
}
