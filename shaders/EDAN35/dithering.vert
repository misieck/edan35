#version 410

// Trick from
// https://rauwendaal.net/2014/06/14/rendering-a-screen-covering-triangle-in-opengl/
struct ViewProjTransforms
{
	mat4 view_projection; // mCamera.GetWorldToClipMatrix();
	mat4 view_projection_inverse; // mCamera.GetClipToWorldMatrix();
};

layout (std140) uniform CameraViewProjTransforms
{
	ViewProjTransforms camera;
};



void main()
{
	float x = -1.0 + float((gl_VertexID & 1) << 2);
	float y = -1.0 + float((gl_VertexID & 2) << 1);

	gl_Position = vec4(x, y, 0.0, 1.0);
}
