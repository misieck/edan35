#include "assignment3.hpp"
#include "core/helpers.hpp"
#include "interpolation.hpp"
#include "parametric_shapes.hpp"

#include "config.hpp"
#include "core/Bonobo.h"
#include "core/FPSCamera.h"
#include "core/node.hpp"
#include "core/ShaderProgramManager.hpp"

#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <tinyfiledialogs.h>

#include <clocale>
#include <cstdlib>
#include <stdexcept>

edaf80::Assignment3::Assignment3(WindowManager& windowManager) :
	mCamera(0.5f * glm::half_pi<float>(),
	        static_cast<float>(config::resolution_x) / static_cast<float>(config::resolution_y),
	        0.01f, 1000.0f),
	inputHandler(), mWindowManager(windowManager), window(nullptr)
{
	WindowManager::WindowDatum window_datum{ inputHandler, mCamera, config::resolution_x, config::resolution_y, 0, 0, 0, 0};

	window = mWindowManager.CreateGLFWWindow("EDAF80: Assignment 3", window_datum, config::msaa_rate);
	if (window == nullptr) {
		throw std::runtime_error("Failed to get a window: aborting!");
	}

	bonobo::init();
}

edaf80::Assignment3::~Assignment3()
{
	bonobo::deinit();
}

void
edaf80::Assignment3::run()
{
	// Set up the camera
	mCamera.mWorld.SetTranslate(glm::vec3(0.0f, 0.0f, 26.0f));
	mCamera.mMouseSensitivity = glm::vec2(0.003f);
	mCamera.mMovementSpeed = glm::vec3(3.0f); // 3 m/s => 10.8 km/h

	// Create the shader programs
	ShaderProgramManager program_manager;

    GLuint skybox_shader = 0u;
	program_manager.CreateAndRegisterProgram("skybox",
	                                         { { ShaderType::vertex, "EDAF80/skybox.vert" },
	                                           { ShaderType::fragment, "EDAF80/skybox.frag" } },
	                                         skybox_shader);
	if (skybox_shader == 0u) {
		LogError("Failed to load skybox shader");
		return;
	}

    GLuint demo_shader = 0u;
	program_manager.CreateAndRegisterProgram("ass3",
	                                         { { ShaderType::vertex, "EDAF80/demo.vert" },
	                                           { ShaderType::fragment, "EDAF80/demo.frag" } },
	                                         demo_shader);
	if (demo_shader == 0u) {
		LogError("Failed to load ass3 shader");
		return;
	}
   

    
    GLuint fallback_shader = 0u;
	program_manager.CreateAndRegisterProgram("Fallback",
	                                         { { ShaderType::vertex, "common/fallback.vert" },
	                                           { ShaderType::fragment, "common/fallback.frag" } },
	                                         fallback_shader);
	if (fallback_shader == 0u) {
		LogError("Failed to load fallback shader");
		return;
	}

	GLuint diffuse_shader = 0u;
	program_manager.CreateAndRegisterProgram("Diffuse",
	                                         { { ShaderType::vertex, "EDAF80/diffuse.vert" },
	                                           { ShaderType::fragment, "EDAF80/diffuse.frag" } },
	                                         diffuse_shader);
	if (diffuse_shader == 0u)
		LogError("Failed to load diffuse shader");

	GLuint normal_shader = 0u;
	program_manager.CreateAndRegisterProgram("Normal",
	                                         { { ShaderType::vertex, "EDAF80/normal.vert" },
	                                           { ShaderType::fragment, "EDAF80/normal.frag" } },
	                                         normal_shader);
	if (normal_shader == 0u)
		LogError("Failed to load normal shader");

    GLuint game_shader = 0u;
	program_manager.CreateAndRegisterProgram("Game",
	                                         { { ShaderType::vertex, "EDAF80/game.vert" },
	                                           { ShaderType::fragment, "EDAF80/game.frag" }
},
	                                         game_shader);
	if (game_shader == 0u)
		LogError("Failed to load tangent shader");
GLuint bitangent_shader = 0u;
	program_manager.CreateAndRegisterProgram("BiTangent",
	                                         { { ShaderType::vertex, "EDAF80/binormal.vert" },
	                                           { ShaderType::fragment, "EDAF80/binormal.frag" } },
	                                         bitangent_shader);
	if (bitangent_shader == 0u)
		LogError("Failed to load tangent shader");

	GLuint texcoord_shader = 0u;
	program_manager.CreateAndRegisterProgram("Texture coords",
	                                         { { ShaderType::vertex, "EDAF80/texcoord.vert" },
	                                           { ShaderType::fragment, "EDAF80/texcoord.frag" } },
	                                         texcoord_shader);
	if (texcoord_shader == 0u)
		LogError("Failed to load texcoord shader");

	auto light_position = glm::vec3(-2.0f, 4.0f, 2.0f);
	auto const set_uniforms = [&light_position](GLuint program){
		glUniform3fv(glGetUniformLocation(program, "light_position"), 1, glm::value_ptr(light_position));
	};

	bool use_normal_mapping = false;
	auto camera_position = mCamera.mWorld.GetTranslation();
    float elapsed_time_s = 0.0f;
	auto const phong_set_uniforms = [&use_normal_mapping,&light_position,&camera_position, &elapsed_time_s](GLuint program){
		glUniform1i(glGetUniformLocation(program, "use_normal_mapping"), use_normal_mapping ? 1 : 0);
		glUniform3fv(glGetUniformLocation(program, "light_position"), 1, glm::value_ptr(light_position));
		glUniform3fv(glGetUniformLocation(program, "camera_position"), 1, glm::value_ptr(camera_position));
        glUniform1f(glGetUniformLocation(program, "elapsed_time_s"), elapsed_time_s);
	};

    
    GLuint cubemap = bonobo::loadTextureCubeMap(config::resources_path("cubemaps/Teide/posx.jpg"),
                                                config::resources_path("cubemaps/Teide/negx.jpg"),
                                                config::resources_path("cubemaps/Teide/posy.jpg"),
                                                config::resources_path("cubemaps/Teide/negy.jpg"),
                                                config::resources_path("cubemaps/Teide/posz.jpg"),
                                                config::resources_path("cubemaps/Teide/negz.jpg")
                                                );
    
    GLuint demoSpecTex = bonobo::loadTexture2D(config::resources_path("textures/cobblestone_floor_08_rough_2k.jpg"));
    GLuint demoDiffTex = bonobo::loadTexture2D(config::resources_path("textures/cobblestone_floor_08_diff_2k.jpg"));
    GLuint demoNormalTex = bonobo::loadTexture2D(config::resources_path("textures/cobblestone_floor_08_nor_2k.jpg"));

    //GLuint demoSpecTex = bonobo::loadTexture2D(config::resources_path("textures/leather_red_02_rough_2k.jpg"));
    //GLuint demoDiffTex = bonobo::loadTexture2D(config::resources_path("textures/leather_red_02_coll1_2k.jpg"));
    //GLuint demoNormalTex = bonobo::loadTexture2D(config::resources_path("textures/leather_red_02_nor_2k.jpg"));
   
	//
	// Set up the two spheres used.
	//
	auto skybox_shape = parametric_shapes::createSphere(800.0f, 4u, 3u);
	if (skybox_shape.vao == 0u) {
		LogError("Failed to retrieve the mesh for the skybox");
		return;
	}
    
	Node skybox;
	skybox.set_geometry(skybox_shape);
	skybox.set_program(&skybox_shader, set_uniforms);
    skybox.add_texture("cubemap", cubemap, GL_TEXTURE_CUBE_MAP);
        
    //	auto demo_shape = parametric_shapes::createQuad(0.4f, 0.4f, 2u, 2u);
    auto demo_shape = parametric_shapes::createSphere(10.5f, 80u, 80u);
    if (demo_shape.vao == 0u) {
		LogError("Failed to retrieve the mesh for the demo sphere");
		return;
	}

	bonobo::material_data demo_material;
	demo_material.ambient = glm::vec3(0.1f, 0.1f, 0.1f);
	demo_material.diffuse = glm::vec3(0.7f, 0.2f, 0.4f);
	demo_material.specular = glm::vec3(1.0f, 1.0f, 1.0f);
	demo_material.shininess = 10.0f;

	Node demo_sphere;
    demo_sphere.add_texture("demoSpecTex", demoSpecTex, GL_TEXTURE_2D);
    demo_sphere.add_texture("demoDiffTex", demoDiffTex, GL_TEXTURE_2D);
    demo_sphere.add_texture("demoNormalTex", demoNormalTex, GL_TEXTURE_2D);
    demo_sphere.set_geometry(demo_shape);
	demo_sphere.set_material_constants(demo_material);
	demo_sphere.set_program(&demo_shader, phong_set_uniforms);




	glClearDepthf(1.0f);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);


	auto lastTime = std::chrono::high_resolution_clock::now();

	bool use_orbit_camera = false;
	std::int32_t demo_sphere_program_index = 0;
	auto cull_mode = bonobo::cull_mode_t::disabled;
	auto polygon_mode = bonobo::polygon_mode_t::fill;
	bool show_logs = true;
	bool show_gui = true;
	bool shader_reload_failed = false;
	bool show_basis = false;
	float basis_thickness_scale = 1.0f;
	float basis_length_scale = 1.0f;

	changeCullMode(cull_mode);

	while (!glfwWindowShouldClose(window)) {
		auto const nowTime = std::chrono::high_resolution_clock::now();
		auto const deltaTimeUs = std::chrono::duration_cast<std::chrono::microseconds>(nowTime - lastTime);
		lastTime = nowTime;
        elapsed_time_s += std::chrono::duration<float>(deltaTimeUs).count();

		auto& io = ImGui::GetIO();
		inputHandler.SetUICapture(io.WantCaptureMouse, io.WantCaptureKeyboard);

		glfwPollEvents();
		inputHandler.Advance();
		mCamera.Update(deltaTimeUs, inputHandler);
		if (use_orbit_camera) {
			mCamera.mWorld.LookAt(glm::vec3(0.0f));
		}
		camera_position = mCamera.mWorld.GetTranslation();
        skybox.get_transform().SetTranslate( camera_position);
		if (inputHandler.GetKeycodeState(GLFW_KEY_R) & JUST_PRESSED) {
			shader_reload_failed = !program_manager.ReloadAllPrograms();
			if (shader_reload_failed)
				tinyfd_notifyPopup("Shader Program Reload Error",
				                   "An error occurred while reloading shader programs; see the logs for details.\n"
				                   "Rendering is suspended until the issue is solved. Once fixed, just reload the shaders again.",
				                   "error");
		}
		if (inputHandler.GetKeycodeState(GLFW_KEY_F3) & JUST_RELEASED)
			show_logs = !show_logs;
		if (inputHandler.GetKeycodeState(GLFW_KEY_F2) & JUST_RELEASED)
			show_gui = !show_gui;
		if (inputHandler.GetKeycodeState(GLFW_KEY_F11) & JUST_RELEASED)
			mWindowManager.ToggleFullscreenStatusForWindow(window);


		// Retrieve the actual framebuffer size: for HiDPI monitors,
		// you might end up with a framebuffer larger than what you
		// actually asked for. For example, if you ask for a 1920x1080
		// framebuffer, you might get a 3840x2160 one instead.
		// Also it might change as the user drags the window between
		// monitors with different DPIs, or if the fullscreen status is
		// being toggled.
		int framebuffer_width, framebuffer_height;
		glfwGetFramebufferSize(window, &framebuffer_width, &framebuffer_height);
		glViewport(0, 0, framebuffer_width, framebuffer_height);


		mWindowManager.NewImGuiFrame();


		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		bonobo::changePolygonMode(polygon_mode);


		skybox.render(mCamera.GetWorldToClipMatrix());
		demo_sphere.render(mCamera.GetWorldToClipMatrix());


		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		bool opened = ImGui::Begin("Scene Control", nullptr, ImGuiWindowFlags_None);
		if (opened) {
			auto const cull_mode_changed = bonobo::uiSelectCullMode("Cull mode", cull_mode);
			if (cull_mode_changed) {
				changeCullMode(cull_mode);
			}
			bonobo::uiSelectPolygonMode("Polygon mode", polygon_mode);
			auto demo_sphere_selection_result = program_manager.SelectProgram("Demo sphere", demo_sphere_program_index);
			if (demo_sphere_selection_result.was_selection_changed) {
				demo_sphere.set_program(demo_sphere_selection_result.program, phong_set_uniforms);
			}
			ImGui::Separator();
			ImGui::Checkbox("Use normal mapping", &use_normal_mapping);
			ImGui::ColorEdit3("Ambient", glm::value_ptr(demo_material.ambient));
			ImGui::ColorEdit3("Diffuse", glm::value_ptr(demo_material.diffuse));
			ImGui::ColorEdit3("Specular", glm::value_ptr(demo_material.specular));
			ImGui::SliderFloat("Shininess", &demo_material.shininess, 1.0f, 1000.0f);
			ImGui::SliderFloat3("Light Position", glm::value_ptr(light_position), -20.0f, 20.0f);
			ImGui::Separator();
			ImGui::Checkbox("Use orbit camera", &use_orbit_camera);
			ImGui::Separator();
			ImGui::Checkbox("Show basis", &show_basis);
			ImGui::SliderFloat("Basis thickness scale", &basis_thickness_scale, 0.0f, 100.0f);
			ImGui::SliderFloat("Basis length scale", &basis_length_scale, 0.0f, 100.0f);
		}
		ImGui::End();

		demo_sphere.set_material_constants(demo_material);

		if (show_basis)
			bonobo::renderBasis(basis_thickness_scale, basis_length_scale, mCamera.GetWorldToClipMatrix());

		opened = ImGui::Begin("Render Time", nullptr, ImGuiWindowFlags_None);
		if (opened)
			ImGui::Text("%.3f ms", std::chrono::duration<float, std::milli>(deltaTimeUs).count());
		ImGui::End();

		if (show_logs)
			Log::View::Render();
		mWindowManager.RenderImGuiFrame(show_gui);

		glfwSwapBuffers(window);
	}
}

int main()
{
	std::setlocale(LC_ALL, "");

	Bonobo framework;

	try {
		edaf80::Assignment3 assignment3(framework.GetWindowManager());
		assignment3.run();
	} catch (std::runtime_error const& e) {
		LogError(e.what());
	}
}