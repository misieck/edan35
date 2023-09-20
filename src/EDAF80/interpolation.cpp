#include "interpolation.hpp"

glm::vec3
interpolation::evalLERP(glm::vec3 const& p0, glm::vec3 const& p1, float const x)
{
    auto X = glm::vec2(1, x);
    auto tr = glm::mat2(glm::vec2(1, 0),
                        glm::vec2(-1, 1));
    
    auto ret_x = X*tr*glm::vec2(p0.x, p1.x);
    auto ret_y = X*tr*glm::vec2(p0.y, p1.y);
    auto ret_z = X*tr*glm::vec2(p0.z, p1.z);
    
	return  glm::vec3(ret_x[0], ret_y[0], ret_z[0]);
}

glm::vec3
interpolation::evalCatmullRom(glm::vec3 const& p0, glm::vec3 const& p1,
                              glm::vec3 const& p2, glm::vec3 const& p3,
                              float const t, float const x)
{
	glm::vec3 result;

	glm::vec4 x_vector(1, x, x*x, x*x*x);

	glm::vec4 tau_col1(0.0f, -t, 2*t, -t);
	glm::vec4 tau_col2(1.0f, 0, t-3.0, 2.0-t);
	glm::vec4 tau_col3(0.0f, t, 3.0-2.0*t, t-2.0);
	glm::vec4 tau_col4(0.0f, 0.0f, -t, t);

	/*
	glm::vec4 tau_row1(0.0f, 1.0f, 0.0f, 0.0f);
	glm::vec4 tau_row2(-t, 0.0, t, 0.0);
	glm::vec4 tau_row3(2*t, t-3.0f, 3.0f-2.0f*t, -t);
	glm::vec4 tau_row4(-t, 2.0f-t, t-2.0f, t);
	glm::mat4 tau_matrix(tau_row1, tau_row2, tau_row3, tau_row4);
	*/


	result.x = p0.x * glm::dot(x_vector, tau_col1) + p1.x * glm::dot(x_vector, tau_col2) + 
				p2.x * glm::dot(x_vector, tau_col3) + p3.x * glm::dot(x_vector, tau_col4);
	
	result.y = p0.y * glm::dot(x_vector, tau_col1) + p1.y * glm::dot(x_vector, tau_col2) + 
				p2.y * glm::dot(x_vector, tau_col3) + p3.y * glm::dot(x_vector, tau_col4);

	result.z = p0.z * glm::dot(x_vector, tau_col1) + p1.z * glm::dot(x_vector, tau_col2) + 
				p2.z * glm::dot(x_vector, tau_col3) + p3.z * glm::dot(x_vector, tau_col4);
	

	return result;
}
