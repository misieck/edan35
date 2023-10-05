#include "assignment4.hpp"
#include "parametric_shapes.hpp"

#include "config.hpp"
#include "core/Bonobo.h"
#include "core/FPSCamera.h"
#include "core/helpers.hpp"
#include "core/node.hpp"
#include "core/ShaderProgramManager.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <tinyfiledialogs.h>

#include <clocale>
#include <stdexcept>

edaf80::Assignment4::Assignment4(WindowManager& windowManager) :
	mCamera(0.5f * glm::half_pi<float>(),
	        static_cast<float>(config::resolution_x) / static_cast<float>(config::resolution_y),
	        0.01f, 1000.0f),
	inputHandler(), mWindowManager(windowManager), window(nullptr)
{
	WindowManager::WindowDatum window_datum{ inputHandler, mCamera, config::resolution_x, config::resolution_y, 0, 0, 0, 0};

	window = mWindowManager.CreateGLFWWindow("EDAF80: Assignment 4", window_datum, config::msaa_rate);
	if (window == nullptr) {
		throw std::runtime_error("Failed to get a window: aborting!");
	}

	bonobo::init();
}

edaf80::Assignment4::~Assignment4()
{
	bonobo::deinit();
}

void
edaf80::Assignment4::run()
{
	// Set up the camera
	mCamera.mWorld.SetTranslate(glm::vec3(-40.0f, 14.0f, 6.0f));
	mCamera.mWorld.LookAt(glm::vec3(0.0f));
	mCamera.mMouseSensitivity = glm::vec2(0.003f);
	mCamera.mMovementSpeed = glm::vec3(5.0f); // 3 m/s => 10.8 km/h
    mCamera.SetFov(0.9f * glm::half_pi<float>());
	auto camera_position = mCamera.mWorld.GetTranslation();

	// Create the shader programs
	ShaderProgramManager program_manager;
	GLuint fallback_shader = 0u;
	program_manager.CreateAndRegisterProgram("Fallback",
	                                         { { ShaderType::vertex, "common/fallback.vert" },
	                                           { ShaderType::fragment, "common/fallback.frag" } },
	                                         fallback_shader);

	if (fallback_shader == 0u) {
		LogError("Failed to load fallback shader");
		return;
	}

    GLuint ocean_shader = 0u;
	program_manager.CreateAndRegisterProgram("Ocean",
	                                         { { ShaderType::vertex, "EDAF80/ocean.vert" },
	                                           { ShaderType::fragment, "EDAF80/ocean.frag" } },
	                                         ocean_shader);

	if (ocean_shader == 0u) {
		LogError("Failed to load ocean shader");
		return;
	}


	//////////////////////////skybox////////////////////////////////////

	GLuint skybox_shader = 0u;
	program_manager.CreateAndRegisterProgram("skybox",
	                                         { { ShaderType::vertex, "EDAF80/skybox.vert" },
	                                           { ShaderType::fragment, "EDAF80/skybox.frag" } },
	                                         skybox_shader);
	if (skybox_shader == 0u) {
		LogError("Failed to load skybox shader");
		return;
	}

	
	auto light_position = glm::vec3(-40.0f, 4.0f, 2.0f);
	auto const set_uniforms = [&light_position](GLuint program){
		glUniform3fv(glGetUniformLocation(program, "light_position"), 1, glm::value_ptr(light_position));
	};

	GLuint cubemap = bonobo::loadTextureCubeMap(config::resources_path("cubemaps/NissiBeach2/posx.jpg"),
                                                config::resources_path("cubemaps/NissiBeach2/negx.jpg"),
                                                config::resources_path("cubemaps/NissiBeach2/posy.jpg"),
                                                config::resources_path("cubemaps/NissiBeach2/negy.jpg"),
                                                config::resources_path("cubemaps/NissiBeach2/posz.jpg"),
                                                config::resources_path("cubemaps/NissiBeach2/negz.jpg")
                                                );

    GLuint wavesNormal = bonobo::loadTexture2D(config::resources_path("textures/waves.png") );
    
	auto skybox_shape = parametric_shapes::createSphere(800.0f, 8u, 8u);
	if (skybox_shape.vao == 0u) {
		LogError("Failed to retrieve the mesh for the skybox");
		return;
	}
    
	Node skybox;
	skybox.set_geometry(skybox_shape);
	skybox.set_program(&skybox_shader);
    skybox.add_texture("cubemap", cubemap, GL_TEXTURE_CUBE_MAP);
	
    //////////////////////////skybox////////////////////////////////////

	
	//
	// Todo: Insert the creation of other shader programs.
	//       (Check how it was done in assignment 3.)
	//

	float elapsed_time_s = 0.0f;
    float size = 100;
    bool use_normal_mapping = true;
    bool use_refractions = true;
    bool show_fresnel = false;
    bool show_only_color = false;
    
	//
	// Todo: Load your geometry
	//

	auto const ocean_set_uniforms =
      [&elapsed_time_s,
       &camera_position,
       &size,
       &use_normal_mapping,
       &use_refractions, &show_fresnel, &show_only_color] (GLuint program)
    {
        glUniform1f(glGetUniformLocation(program, "elapsed_time_s"), elapsed_time_s);
        glUniform1f(glGetUniformLocation(program, "size"), size);
        glUniform3fv(glGetUniformLocation(program, "camera_position"), 1, glm::value_ptr(camera_position));
        glUniform1i(glGetUniformLocation(program, "use_normal_mapping"), use_normal_mapping?1:0);
        glUniform1i(glGetUniformLocation(program, "use_refractions"), use_refractions?1:0);
        glUniform1i(glGetUniformLocation(program, "show_fresnel"), show_fresnel?1:0);
        glUniform1i(glGetUniformLocation(program, "show_only_color"), show_only_color?1:0);
         //		glUniform3fv(glGetUniformLocation(program, "light_position"), 1, glm::value_ptr(light_position));
        
	};


    
    auto quad_shape = parametric_shapes::createQuad(size,size, 500u, 500u);
	Node the_sea;
    the_sea.set_geometry(quad_shape);
    the_sea.set_program(&ocean_shader, ocean_set_uniforms);
    the_sea.add_texture("cubemap", cubemap, GL_TEXTURE_CUBE_MAP);
    the_sea.add_texture("wavesNormal", wavesNormal, GL_TEXTURE_2D);

    
	glClearDepthf(1.0f);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);


	auto lastTime = std::chrono::high_resolution_clock::now();
    
	bool pause_animation = true;
	bool use_orbit_camera = false;
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
		if (!pause_animation) {
			elapsed_time_s += std::chrono::duration<float>(deltaTimeUs).count();
		}

		auto& io = ImGui::GetIO();
		inputHandler.SetUICapture(io.WantCaptureMouse, io.WantCaptureKeyboard);

		glfwPollEvents();
		inputHandler.Advance();
		mCamera.Update(deltaTimeUs, inputHandler);
		if (use_orbit_camera) {
			mCamera.mWorld.LookAt(glm::vec3(0.0f));
		}
		camera_position = mCamera.mWorld.GetTranslation();

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

		//
		// Todo: If you need to handle inputs, you can do it here
		//
		

		mWindowManager.NewImGuiFrame();

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		bonobo::changePolygonMode(polygon_mode);


		if (!shader_reload_failed) {
			//
		  skybox.render(mCamera.GetWorldToClipMatrix());
			//
          the_sea.render(mCamera.GetWorldToClipMatrix());
		}


		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		//
		// Todo: If you want a custom ImGUI window, you can set it up
		//       here
		//


		bool opened = ImGui::Begin("Scene Control", nullptr, ImGuiWindowFlags_None);
		if (opened) {
			ImGui::Checkbox("Pause animation", &pause_animation);
			ImGui::Checkbox("Use orbit camera", &use_orbit_camera);
            ImGui::Checkbox("Use normal mapping", &use_normal_mapping);
            ImGui::Checkbox("Use refractions", &use_refractions);
            ImGui::Checkbox("Show fresnel", &show_fresnel);
            ImGui::Checkbox("Show only color", &show_only_color);
			ImGui::Separator();
			auto const cull_mode_changed = bonobo::uiSelectCullMode("Cull mode", cull_mode);
			if (cull_mode_changed) {
				changeCullMode(cull_mode);
			}
			bonobo::uiSelectPolygonMode("Polygon mode", polygon_mode);
			ImGui::Separator();
			ImGui::Checkbox("Show basis", &show_basis);
			ImGui::SliderFloat("Basis thickness scale", &basis_thickness_scale, 0.0f, 100.0f);
			ImGui::SliderFloat("Basis length scale", &basis_length_scale, 0.0f, 100.0f);
		}
		ImGui::End();

		if (show_basis)
			bonobo::renderBasis(basis_thickness_scale, basis_length_scale, mCamera.GetWorldToClipMatrix());
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
		edaf80::Assignment4 assignment4(framework.GetWindowManager());
		assignment4.run();
	} catch (std::runtime_error const& e) {
		LogError(e.what());
	}
}
