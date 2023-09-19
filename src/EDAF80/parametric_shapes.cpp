#include "parametric_shapes.hpp"
#include "core/Log.h"

#include <cstddef>
#include <glm/ext/scalar_constants.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>

#include <array>
#include <cassert>
#include <cmath>
#include <glm/gtc/constants.hpp>
#include <iostream>
#include <string.h>
#include <vector>
#include <cmath>

using std::cout;
using std::endl;

bonobo::mesh_data
parametric_shapes::createQuad(float const width, float const height,
                              unsigned int const horizontal_split_count,
                              unsigned int const vertical_split_count)
{
	auto const vertices = std::array<glm::vec3, 4>{
		glm::vec3(0.0f,  0.0f,   0.0f),
		glm::vec3(width, 0.0f,   0.0f),
		glm::vec3(width, height, 0.0f),
		glm::vec3(0.0f,  height, 0.0f)
	};

	auto const index_sets = std::array<glm::uvec3, 2>{
		glm::uvec3(0u, 1u, 2u),
		glm::uvec3(0u, 2u, 3u)
	};

	bonobo::mesh_data data;

	if (horizontal_split_count > 0u || vertical_split_count > 0u)
	{
		LogError("parametric_shapes::createQuad() does not support tesselation.");
		return data;
	}

	//
	// NOTE:
	//
	// Only the values preceeded by a `\todo` tag should be changed, the
	// other ones are correct!
	//

	// Create a Vertex Array Object: it will remember where we stored the
	// data on the GPU, and  which part corresponds to the vertices, which
	// one for the normals, etc.
	//
	// The following function will create new Vertex Arrays, and pass their
	// name in the given array (second argument). Since we only need one,
	// pass a pointer to `data.vao`.
	glGenVertexArrays(1, &data.vao);

	// To be able to store information, the Vertex Array has to be bound
	// first.
  	assert(data.vao != 0u);
	glBindVertexArray(data.vao);
    
	// To store the data, we need to allocate buffers on the GPU. Let's
	// allocate a first one for the vertices.
	//
	// The following function's syntax is similar to `glGenVertexArray()`:
	// it will create multiple OpenGL objects, in this case buffers, and
	// return their names in an array. Have the buffer's name stored into
	// `data.bo`.
	glGenBuffers(1, &data.bo);

	// Similar to the Vertex Array, we need to bind it first before storing
	// anything in it. The data stored in it can be interpreted in
	// different ways. Here, we will say that it is just a simple 1D-array
	// and therefore bind the buffer to the corresponding target.
	glBindBuffer(GL_ARRAY_BUFFER, data.bo);
    
    size_t bo_size = vertices.size() * sizeof(glm::vec3);


    //QUESTION: how does it know where to write data?
    glBufferData(GL_ARRAY_BUFFER, bo_size,
	             /* where is the data stored on the CPU? */vertices.data(),
	             /* inform OpenGL that the data is modified once, but used often */GL_STATIC_DRAW);

	// Vertices have been just stored into a buffer, but we still need to
	// tell Vertex Array where to find them, and how to interpret the data
	// within that buffer.
	//
	// You will see shaders in more detail in lab 3, but for now they are
	// just pieces of code running on the GPU and responsible for moving
	// all the vertices to clip space, and assigning a colour to each pixel
	// covered by geometry.
	// Those shaders have inputs, some of them are the data we just stored
	// in a buffer object. We need to tell the Vertex Array which inputs
	// are enabled, and this is done by the following line of code, which
	// enables the input for vertices:
	glEnableVertexAttribArray(static_cast<unsigned int>(bonobo::shader_bindings::vertices));

	// Once an input is enabled, we need to explain where the data comes
	// from, and how it interpret it. When calling the following function,
	// the Vertex Array will automatically use the current buffer bound to
	// GL_ARRAY_BUFFER as its source for the data. How to interpret it is
	// specified below:
    glVertexAttribPointer(
                          static_cast<unsigned int>(bonobo::shader_bindings::vertices),
                          /*! \todo how many components do our vertices have? */
                          glm::vec3::length(), 
                          /* what is the type of each component? */GL_FLOAT,
	                      /* should it automatically normalise the values stored */GL_FALSE,
	                      /* once all components of a vertex have been read, how far away (in bytes) is the next vertex? */0,
	                      /* how far away (in bytes) from the start of the buffer is the first vertex? */reinterpret_cast<GLvoid const*>(0x0));

	// Now, let's allocate a second one for the indices.
	//
	// Have the buffer's name stored into `data.ibo`.
	glGenBuffers(1, &data.ibo);

	// We still want a 1D-array, but this time it should be a 1D-array of
	// elements, aka. indices!
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data.ibo);

    size_t ibo_size = index_sets.size() *  sizeof( decltype(index_sets)::value_type );
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibo_size,
	             /* where is the data stored on the CPU? */index_sets.data(),
	             /* inform OpenGL that the data is modified once, but used often */GL_STATIC_DRAW);

	data.indices_nb = index_sets.size() * decltype(index_sets)::value_type::length();

	// All the data has been recorded, we can unbind them.
	glBindVertexArray(0u);
	glBindBuffer(GL_ARRAY_BUFFER, 0u);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);

	return data;
}


bonobo::mesh_data
parametric_shapes::createTorus(float const major_radius,
                               float const minor_radius,
                               unsigned int const major_split_count,
                               unsigned int const minor_split_count)
{
	//! \todo (Optional) Implement this function
	return bonobo::mesh_data();
}

bonobo::mesh_data
parametric_shapes::createCircleRing(float const radius,
                                    float const spread_length,
                                    unsigned int const circle_split_count,
                                    unsigned int const spread_split_count)
{
	auto const circle_slice_edges_count = circle_split_count + 1u;
	auto const spread_slice_edges_count = spread_split_count + 1u;
	auto const circle_slice_vertices_count = circle_slice_edges_count + 1u;
	auto const spread_slice_vertices_count = spread_slice_edges_count + 1u;
	auto const vertices_nb = circle_slice_vertices_count * spread_slice_vertices_count;

	auto vertices  = std::vector<glm::vec3>(vertices_nb);
	auto normals   = std::vector<glm::vec3>(vertices_nb);
	auto texcoords = std::vector<glm::vec3>(vertices_nb);
	auto tangents  = std::vector<glm::vec3>(vertices_nb);
	auto binormals = std::vector<glm::vec3>(vertices_nb);

	float const spread_start = radius - 0.5f * spread_length;
	float const d_theta = glm::two_pi<float>() / (static_cast<float>(circle_slice_edges_count));
	float const d_spread = spread_length / (static_cast<float>(spread_slice_edges_count));

	// generate vertices iteratively
	size_t index = 0u;
	float theta = 0.0f;
	for (unsigned int i = 0u; i < circle_slice_vertices_count; ++i) {
		float const cos_theta = std::cos(theta);
		float const sin_theta = std::sin(theta);

		float distance_to_centre = spread_start;
		for (unsigned int j = 0u; j < spread_slice_vertices_count; ++j) {
			// vertex
			vertices[index] = glm::vec3(distance_to_centre * cos_theta,
			                            distance_to_centre * sin_theta,
			                            0.0f);

			// texture coordinates
			texcoords[index] = glm::vec3(static_cast<float>(j) / (static_cast<float>(spread_slice_vertices_count)),
			                             static_cast<float>(i) / (static_cast<float>(circle_slice_vertices_count)),
			                             0.0f);

			// tangent
			auto const t = glm::vec3(cos_theta, sin_theta, 0.0f);
			tangents[index] = t;

			// binormal
			auto const b = glm::vec3(-sin_theta, cos_theta, 0.0f);
			binormals[index] = b;

			// normal
			auto const n = glm::cross(t, b);
			normals[index] = n;

			distance_to_centre += d_spread;
			++index;
		}

		theta += d_theta;
	}

	// create index array
	auto index_sets = std::vector<glm::uvec3>(2u * circle_slice_edges_count * spread_slice_edges_count);

	// generate indices iteratively
	index = 0u;
	for (unsigned int i = 0u; i < circle_slice_edges_count; ++i)
	{
		for (unsigned int j = 0u; j < spread_slice_edges_count; ++j)
		{
			index_sets[index] = glm::uvec3(spread_slice_vertices_count * (i + 0u) + (j + 0u),
			                               spread_slice_vertices_count * (i + 0u) + (j + 1u),
			                               spread_slice_vertices_count * (i + 1u) + (j + 1u));
			++index;

			index_sets[index] = glm::uvec3(spread_slice_vertices_count * (i + 0u) + (j + 0u),
			                               spread_slice_vertices_count * (i + 1u) + (j + 1u),
			                               spread_slice_vertices_count * (i + 1u) + (j + 0u));
			++index;
		}
	}

	bonobo::mesh_data data;
	glGenVertexArrays(1, &data.vao);
	assert(data.vao != 0u);
	glBindVertexArray(data.vao);

	auto const vertices_offset = 0u;
	auto const vertices_size = static_cast<GLsizeiptr>(vertices.size() * sizeof(glm::vec3));
	auto const normals_offset = vertices_size;
	auto const normals_size = static_cast<GLsizeiptr>(normals.size() * sizeof(glm::vec3));
	auto const texcoords_offset = normals_offset + normals_size;
	auto const texcoords_size = static_cast<GLsizeiptr>(texcoords.size() * sizeof(glm::vec3));
	auto const tangents_offset = texcoords_offset + texcoords_size;
	auto const tangents_size = static_cast<GLsizeiptr>(tangents.size() * sizeof(glm::vec3));
	auto const binormals_offset = tangents_offset + tangents_size;
	auto const binormals_size = static_cast<GLsizeiptr>(binormals.size() * sizeof(glm::vec3));
	auto const bo_size = static_cast<GLsizeiptr>(vertices_size
	                                            +normals_size
	                                            +texcoords_size
	                                            +tangents_size
	                                            +binormals_size
	                                            );
	glGenBuffers(1, &data.bo);
	assert(data.bo != 0u);
	glBindBuffer(GL_ARRAY_BUFFER, data.bo);
	glBufferData(GL_ARRAY_BUFFER, bo_size, nullptr, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, vertices_offset, vertices_size, static_cast<GLvoid const*>(vertices.data()));
	glEnableVertexAttribArray(static_cast<unsigned int>(bonobo::shader_bindings::vertices));
	glVertexAttribPointer(static_cast<unsigned int>(bonobo::shader_bindings::vertices), 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<GLvoid const*>(0x0));

	glBufferSubData(GL_ARRAY_BUFFER, normals_offset, normals_size, static_cast<GLvoid const*>(normals.data()));
	glEnableVertexAttribArray(static_cast<unsigned int>(bonobo::shader_bindings::normals));
	glVertexAttribPointer(static_cast<unsigned int>(bonobo::shader_bindings::normals), 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<GLvoid const*>(normals_offset));

	glBufferSubData(GL_ARRAY_BUFFER, texcoords_offset, texcoords_size, static_cast<GLvoid const*>(texcoords.data()));
	glEnableVertexAttribArray(static_cast<unsigned int>(bonobo::shader_bindings::texcoords));
	glVertexAttribPointer(static_cast<unsigned int>(bonobo::shader_bindings::texcoords), 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<GLvoid const*>(texcoords_offset));

	glBufferSubData(GL_ARRAY_BUFFER, tangents_offset, tangents_size, static_cast<GLvoid const*>(tangents.data()));
	glEnableVertexAttribArray(static_cast<unsigned int>(bonobo::shader_bindings::tangents));
	glVertexAttribPointer(static_cast<unsigned int>(bonobo::shader_bindings::tangents), 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<GLvoid const*>(tangents_offset));

	glBufferSubData(GL_ARRAY_BUFFER, binormals_offset, binormals_size, static_cast<GLvoid const*>(binormals.data()));
	glEnableVertexAttribArray(static_cast<unsigned int>(bonobo::shader_bindings::binormals));
	glVertexAttribPointer(static_cast<unsigned int>(bonobo::shader_bindings::binormals), 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<GLvoid const*>(binormals_offset));

	glBindBuffer(GL_ARRAY_BUFFER, 0u);

	data.indices_nb = static_cast<GLsizei>(index_sets.size() * 3u);
	glGenBuffers(1, &data.ibo);
	assert(data.ibo != 0u);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data.ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(index_sets.size() * sizeof(glm::uvec3)), reinterpret_cast<GLvoid const*>(index_sets.data()), GL_STATIC_DRAW);

	glBindVertexArray(0u);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);

	return data;
}

static size_t fix_idx(unsigned int idx, size_t n) {
  auto y = (size_t)glm::ceil(static_cast<float>(idx)/n);
  
  unsigned int ret = (idx - 1 -y*n+n)%n +y*n-n+1;
  printf(" ~%u~(%u->%u) ", (unsigned)y, idx, ret);
  return ret;
}


static glm::vec3 fix_vec(glm::vec3 vec, size_t n) {
  printf("(");
  for (int i = 0; i<vec.length(); ++i)
  {
    vec[i] = fix_idx(vec[i], n);
    printf("%d,",(unsigned) vec[i]);
  }
  printf(")\n");
  return vec;
}

bonobo::mesh_data
parametric_shapes::createSphere( const float radius,
                                 const unsigned int longitude_split_count,
                                 const unsigned int latitude_split_count)
{
    auto const n_meridians = longitude_split_count;
    auto const n_parallels = latitude_split_count -1;
	auto const n_vertex = 2 + n_parallels * n_meridians ;
    auto const n_triangles = (2u * (n_parallels-1) + 2u) * n_meridians;

	auto vertices  = std::vector<glm::vec3>(n_vertex);
	auto normals   = std::vector<glm::vec3>(n_vertex);
	auto texcoords = std::vector<glm::vec3>(n_vertex);
	auto tangents  = std::vector<glm::vec3>(n_vertex);
	auto binormals = std::vector<glm::vec3>(n_vertex);


   
    
	float const d_theta = glm::two_pi<float>() / (static_cast<float>(longitude_split_count));
	float const d_phi = glm::pi<float>() / (static_cast<float>(latitude_split_count));

    float const zero = 0.01f;
    
	// generate vertices iteratively
	size_t index = 0u;
	float theta = glm::two_pi<float>();
    float phi = glm::pi<float>();
    auto const r = radius;
    vertices[0] = glm::vec3(0, r, 0);
    vertices[n_vertex-1] = glm::vec3(0, -r, 0);
    tangents[0] = glm::vec3(zero, zero, -zero);
    tangents[n_vertex-1] = glm::vec3(zero, zero, zero);
    binormals[0] = glm::vec3( zero, zero, -r); //phi = pi, theta = two_pi
    binormals[n_vertex-1] = glm::vec3( zero, zero, r); //phi = 0; theta = 0;
    
    for (unsigned int i = 0u; i < n_parallels; ++i) {
        phi -= d_phi;
        
        float const cos_phi = std::cos(phi);
		float const sin_phi = std::sin(phi);
        
        for (unsigned int j = 0u; j < n_meridians; ++j) {
            float const cos_theta = std::cos(theta);
            float const sin_theta = std::sin(theta);

            // vertex

            vertices[++index] = glm::vec3( r * sin_theta * sin_phi,
                                           -r * cos_phi,
                                           r * cos_theta * sin_phi);

			// texture coordinates
			//texcoords[index] = glm::vec3(static_cast<float>(j) / (static_cast<float>(spread_slice_vertices_count)),
			//                             static_cast<float>(i) / (static_cast<float>(circle_slice_vertices_count)),
			//                             0.0f);

			// tangent
  			auto const t = glm::vec3( r * cos_theta * sin_phi, 0, -r * sin_theta * sin_phi );
            //auto const t = glm::vec3(0.2, -0.2, 0.2);
			tangents[index] = t;

			// binormal
            auto const b = glm::vec3( r * sin_theta * cos_phi, r * sin_phi, r * cos_theta * cos_phi);
            //auto const b = glm::vec3(-0.2, 0.2, -0.2);
            binormals[index] = b;

			// normal
			auto const n = glm::cross (t, b);
			normals[index] = n;
            theta -= d_theta;
			
		}

		
	}

	// create index array
	auto triangles = std::vector<glm::uvec3>( n_triangles );

	// generate indices iteratively

    for(int i=0; i < n_triangles; i++){
        triangles[i][0] = 0;
        triangles[i][1] = 0;
        triangles[i][2] = 0;
    }




    size_t n = n_meridians;
    
    for(int i=0; i < n - 1; i++){
        triangles[i][2] = 0;
        triangles[i][1] = i + 1;
        triangles[i][0] = i + 2;
        
        triangles[n_triangles - i - 1][2] = n_vertex - 1;
        triangles[n_triangles - i - 1][1] = n_vertex - i - 2;
        triangles[n_triangles - i - 1][0] = n_vertex - i - 3;
    }
    
    triangles[n - 1][2] = 0;
    triangles[n - 1][1] = n_meridians;
    triangles[n - 1][0] = 1;
    
    triangles[n_triangles - n][0] = n_vertex - 1;
    triangles[n_triangles - n][1] = n_vertex - 2;
    triangles[n_triangles - n][2] = n_vertex - n - 1;
    
    index = 0u;
    unsigned int triangle_index =  n;
	for (unsigned int i = 1u; i < n_vertex - n - 1; ++i)
	{
      
      std::cout<<triangle_index<<": ";
      if (i%n == 0){
        triangles[triangle_index++] = glm::vec3(i, i - n + 1, i+1);
        triangles[triangle_index++] = glm::vec3(i, i + 1, i+n);

      } else{
        triangles[triangle_index++] = glm::vec3(i, i + 1, i+n+1);
        triangles[triangle_index++] = glm::vec3(i, i + n + 1, i+n);      
      }
      std::cout<<triangles[triangle_index-2]<<std::endl
               <<triangle_index-1<<": "<<triangles[triangle_index-1]<<std::endl;      
      
	}
    
	bonobo::mesh_data data;
	glGenVertexArrays(1, &data.vao);
	assert(data.vao != 0u);
	glBindVertexArray(data.vao);

	auto const vertices_offset = 0u;
	auto const vertices_size = static_cast<GLsizeiptr>(vertices.size() * sizeof(glm::vec3));
	auto const normals_offset = vertices_size;
	auto const normals_size = static_cast<GLsizeiptr>(normals.size() * sizeof(glm::vec3));
	auto const texcoords_offset = normals_offset + normals_size;
	auto const texcoords_size = static_cast<GLsizeiptr>(texcoords.size() * sizeof(glm::vec3));
	auto const tangents_offset = texcoords_offset + texcoords_size;
	auto const tangents_size = static_cast<GLsizeiptr>(tangents.size() * sizeof(glm::vec3));
	auto const binormals_offset = tangents_offset + tangents_size;
	auto const binormals_size = static_cast<GLsizeiptr>(binormals.size() * sizeof(glm::vec3));
	auto const bo_size = static_cast<GLsizeiptr>(vertices_size
	                                            +normals_size
	                                            +texcoords_size
	                                            +tangents_size
	                                            +binormals_size
	                                            );
	glGenBuffers(1, &data.bo);
	assert(data.bo != 0u);
	glBindBuffer(GL_ARRAY_BUFFER, data.bo);
	glBufferData(GL_ARRAY_BUFFER, bo_size, nullptr, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, vertices_offset, vertices_size, static_cast<GLvoid const*>(vertices.data()));
	glEnableVertexAttribArray(static_cast<unsigned int>(bonobo::shader_bindings::vertices));
	glVertexAttribPointer(static_cast<unsigned int>(bonobo::shader_bindings::vertices), 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<GLvoid const*>(0x0));

	glBufferSubData(GL_ARRAY_BUFFER, normals_offset, normals_size, static_cast<GLvoid const*>(normals.data()));
	glEnableVertexAttribArray(static_cast<unsigned int>(bonobo::shader_bindings::normals));
	glVertexAttribPointer(static_cast<unsigned int>(bonobo::shader_bindings::normals), 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<GLvoid const*>(normals_offset));

	glBufferSubData(GL_ARRAY_BUFFER, texcoords_offset, texcoords_size, static_cast<GLvoid const*>(texcoords.data()));
	glEnableVertexAttribArray(static_cast<unsigned int>(bonobo::shader_bindings::texcoords));
	glVertexAttribPointer(static_cast<unsigned int>(bonobo::shader_bindings::texcoords), 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<GLvoid const*>(texcoords_offset));

	glBufferSubData(GL_ARRAY_BUFFER, tangents_offset, tangents_size, static_cast<GLvoid const*>(tangents.data()));
	glEnableVertexAttribArray(static_cast<unsigned int>(bonobo::shader_bindings::tangents));
	glVertexAttribPointer(static_cast<unsigned int>(bonobo::shader_bindings::tangents), 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<GLvoid const*>(tangents_offset));

	glBufferSubData(GL_ARRAY_BUFFER, binormals_offset, binormals_size, static_cast<GLvoid const*>(binormals.data()));
	glEnableVertexAttribArray(static_cast<unsigned int>(bonobo::shader_bindings::binormals));
	glVertexAttribPointer(static_cast<unsigned int>(bonobo::shader_bindings::binormals), 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<GLvoid const*>(binormals_offset));

	glBindBuffer(GL_ARRAY_BUFFER, 0u);

	data.indices_nb = static_cast<GLsizei>(triangles.size() * 3u);
	glGenBuffers(1, &data.ibo);
	assert(data.ibo != 0u);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data.ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(triangles.size() * sizeof(glm::uvec3)), reinterpret_cast<GLvoid const*>(triangles.data()), GL_STATIC_DRAW);

	glBindVertexArray(0u);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);

	return data;
}

