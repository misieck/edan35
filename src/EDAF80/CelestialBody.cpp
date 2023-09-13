#include "CelestialBody.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

#include "core/helpers.hpp"
#include "core/Log.h"

CelestialBody::CelestialBody(bonobo::mesh_data const& shape,
                             GLuint const* program,
                             GLuint diffuse_texture_id)
{
	_body.node.set_geometry(shape);
	_body.node.add_texture("diffuse_texture", diffuse_texture_id, GL_TEXTURE_2D);
	_body.node.set_program(program);
}

glm::mat4 CelestialBody::render(std::chrono::microseconds elapsed_time,
                                glm::mat4 const& view_projection,
                                glm::mat4 const& parent_transform,
                                bool show_basis)
{
	// Convert the duration from microseconds to seconds.
	auto const elapsed_time_s = std::chrono::duration<float>(elapsed_time).count();
	// If a different ratio was needed, for example a duration in
	// milliseconds, the following would have been used:
	// auto const elapsed_time_ms = std::chrono::duration<float, std::milli>(elapsed_time).count();

	//_body.spin.rotation_angle = -glm::half_pi<float>() / 2.0f;

	//I changed this here 
	//glm::mat4 world = parent_transform;
	
	//scale factor 
	glm::vec3 scaleFactorsidentity = _body.scale;

	//identity matrix
	glm::mat4 identityMatrix = glm::mat4(1.0f);

	//scaling
	glm::mat4 world = glm::scale(identityMatrix, scaleFactorsidentity);

	
	//second scaling (rugby ball)
	glm::vec3 scaleFactorsrugby(1.0f, 0.2f, 0.2f);
	set_scale(scaleFactorsrugby);

	/*
	//spinning 
	_body.spin.rotation_angle += _body.spin.speed * elapsed_time_s; 											//[rad] = [rad/s] * [s] 
	glm::mat4 R1s = glm::rotate(identityMatrix, _body.spin.rotation_angle, glm::vec3(0.0f, 1.0f, 0.0f));  		//y-axis
	
	printf("%f\n", elapsed_time_s);
	printf("%f\n", _body.spin.rotation_angle);
	//world = R1s;

	//tilting
	glm::mat4 R2s = glm::rotate(identityMatrix, _body.spin.axial_tilt, glm::vec3(0.0f, 0.0f, 1.0f));			//z-axis
	

	//translate 
	glm::mat4 To = glm::translate(identityMatrix, glm::vec3(_body.orbit.radius, 0.0f, 0.0f));					//x-axis


	//rotate orbit 
	_body.orbit.rotation_angle += _body.orbit.speed * elapsed_time_s;
	glm::mat4 R1o = glm::rotate(identityMatrix, _body.orbit.rotation_angle, glm::vec3(0.0f, 1.0f, 0.0f));		//z-axis
	

	//tilting orbit 
	glm::mat4 R2o = glm::rotate(identityMatrix, _body.orbit.inclination, glm::vec3(0.0f, 0.0f, 1.0f));


	world = parent_transform * R2o * R1o * To * R2s * R1s;
	
	glm::mat4 child_transform = parent_transform * R2o * R1o * To;

	*/
	if (show_basis)
	{
		bonobo::renderBasis(1.0f, 2.0f, view_projection, world);
	}

	// Note: The second argument of `node::render()` is supposed to be the
	// parent transform of the node, not the whole world matrix, as the
	// node internally manages its local transforms. However in our case we
	// manage all the local transforms ourselves, so the internal transform
	// of the node is just the identity matrix and we can forward the whole
	// world matrix.
	_body.node.render(view_projection, world);

	return world;
	//return child_transform;
}

void CelestialBody::add_child(CelestialBody* child)
{
	_children.push_back(child);
}

std::vector<CelestialBody*> const& CelestialBody::get_children() const
{
	return _children;
}

void CelestialBody::set_orbit(OrbitConfiguration const& configuration)
{
	_body.orbit.radius = configuration.radius;
	_body.orbit.inclination = configuration.inclination;
	_body.orbit.speed = configuration.speed;
	_body.orbit.rotation_angle = 0.0f;
}

void CelestialBody::set_scale(glm::vec3 const& scale)
{
	_body.scale = scale;
}

void CelestialBody::set_spin(SpinConfiguration const& configuration)
{
	_body.spin.axial_tilt = configuration.axial_tilt;
	_body.spin.speed = configuration.speed;
	_body.spin.rotation_angle = 0.0f;
}

void CelestialBody::set_ring(bonobo::mesh_data const& shape,
                             GLuint const* program,
                             GLuint diffuse_texture_id,
                             glm::vec2 const& scale)
{
	_ring.node.set_geometry(shape);
	_ring.node.add_texture("diffuse_texture", diffuse_texture_id, GL_TEXTURE_2D);
	_ring.node.set_program(program);

	_ring.scale = scale;

	_ring.is_set = true;
}
