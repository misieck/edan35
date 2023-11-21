#include "assignment5.hpp"

#include "config.hpp"
#include "core/Bonobo.h"
#include "core/FPSCamera.h"
#include "core/helpers.hpp"
#include "core/ShaderProgramManager.hpp"

#include <chrono>
#include <glm/fwd.hpp>
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <tinyfiledialogs.h>

#include <clocale>
#include <stdexcept>
#include <vector>
#include "core/node.hpp"
#include "asteroid.hpp"

using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::microseconds;
using std::chrono::milliseconds;
using std::chrono::time_point;
using std::literals::chrono_literals::operator""ms;

bool  collision(const asteroid& a, const asteroid& b){
    return false;
}
  


edaf80::Assignment5::Assignment5(WindowManager& windowManager) :
	mCamera(0.5f * glm::half_pi<float>(),
	        static_cast<float>(config::resolution_x) / static_cast<float>(config::resolution_y),
	        0.01f, 1000.0f),
	inputHandler(), mWindowManager(windowManager), window(nullptr)
{
	WindowManager::WindowDatum window_datum{ inputHandler, mCamera, config::resolution_x, config::resolution_y, 0, 0, 0, 0};

	window = mWindowManager.CreateGLFWWindow("EDAF80: Assignment 5", window_datum, config::msaa_rate);
	if (window == nullptr) {
		throw std::runtime_error("Failed to get a window: aborting!");
	}

	bonobo::init();
}

edaf80::Assignment5::~Assignment5()
{
	bonobo::deinit();
}

void
edaf80::Assignment5::run()
{
	// Set up the camera
	mCamera.mWorld.SetTranslate(glm::vec3(0.0f, 0.0f, 0.0f));
	mCamera.mMouseSensitivity = glm::vec2(0.003f);
	mCamera.mMovementSpeed = glm::vec3(3.0f); // 3 m/s => 10.8 km/h
    mCamera.mWorld.LookTowards(glm::vec3(1,0,0));

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

    GLuint game_shader = 0u;
	program_manager.CreateAndRegisterProgram("game",
	                                         { { ShaderType::vertex, "EDAF80/game.vert" },
	                                           { ShaderType::fragment, "EDAF80/game.frag" } },
	                                         game_shader);
	if (game_shader == 0u) {
		LogError("Failed to load game shader");
		return;
	}

    GLuint bullet_shader = 0u;
	program_manager.CreateAndRegisterProgram("bullet",
	                                         { { ShaderType::vertex, "EDAF80/bullet.vert" },
	                                           { ShaderType::fragment, "EDAF80/bullet.frag" } },
	                                         bullet_shader);
	if (bullet_shader == 0u) {
		LogError("Failed to load game shader");
		return;
	}


    auto light_position = glm::vec3(-2.0f, 20.0f, 2.0f);
    auto camera_position = mCamera.mWorld.GetTranslation();
    float elapsed_time_s = 0.0f;
    
    auto const set_uniforms = [&light_position,&camera_position, &elapsed_time_s](GLuint program){
        glUniform3fv(glGetUniformLocation(program, "light_position"), 1, glm::value_ptr(light_position));
        glUniform3fv(glGetUniformLocation(program, "camera_position"), 1, glm::value_ptr(camera_position));
        glUniform1f(glGetUniformLocation(program, "elapsed_time_s"), elapsed_time_s);
	};

    GLuint specTex = bonobo::loadTexture2D(config::resources_path("textures/cobblestone_floor_08_rough_2k.jpg"));
    GLuint diffTex = bonobo::loadTexture2D(config::resources_path("textures/cobblestone_floor_08_diff_2k.jpg"));
    GLuint normalTex = bonobo::loadTexture2D(config::resources_path("textures/cobblestone_floor_08_nor_2k.jpg"));


    GLuint bulletSpecTex = bonobo::loadTexture2D(config::resources_path("textures/cobblestone_floor_08_rough_2k.jpg"));
    GLuint bulletDiffTex = bonobo::loadTexture2D(config::resources_path("textures/leather_red_02_rough_2k.jpg"));

    
    std::vector<asteroid> asteroids;
    std::vector<bullet> bullets;
    std::vector<time_point<high_resolution_clock>> collisions;
    
    
    const unsigned int N = 10;
    for (int i = 0; i<N; i++){
        auto as = generate_asteroid();// asteroid( {1.f-i, 1.f+i, 0.f}, 0.5f+ static_cast<float>(i)/10);
        as.node.set_program(&game_shader, set_uniforms);
        bonobo::material_data demo_material;
        demo_material.ambient = glm::vec3(0.1f, 0.1f, 0.1f);
        demo_material.diffuse = glm::vec3(0.7f, 0.2f, 0.4f);
        demo_material.specular = glm::vec3(1.0f, 1.0f, 1.0f);
        demo_material.shininess = 10.0f;
        as.node.set_material_constants(demo_material);
        as.node.add_texture("specTex", specTex, GL_TEXTURE_2D);
        as.node.add_texture("diffTex", diffTex, GL_TEXTURE_2D);
        as.node.add_texture("normalTex", normalTex, GL_TEXTURE_2D);
        asteroids.push_back(as);
        collisions.push_back( high_resolution_clock::now() );
      
    }
        

    //
	// Todo: Insert the creation of other shader programs.
	//       (Check how it was done in assignment 3.)
	//

	//
	// Todo: Load your geometry
	//

	glClearDepthf(1.0f);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);


	auto lastTime = std::chrono::high_resolution_clock::now();

	bool show_logs = true;
	bool show_gui = true;
	bool shader_reload_failed = false;
	bool show_basis = false;
    auto polygon_mode = bonobo::polygon_mode_t::fill;
	float basis_thickness_scale = 1.0f;
	float basis_length_scale = 1.0f;
    int count =0;

    glm::vec3 our_position;
    glm::vec3 gun_direction;

    while (!glfwWindowShouldClose(window)) {
		auto const nowTime = std::chrono::high_resolution_clock::now();
		auto const deltaTimeUs = duration_cast<microseconds>(nowTime - lastTime);
        float const deltaTime = std::chrono::duration<float>(deltaTimeUs).count();
		lastTime = nowTime;
        elapsed_time_s += std::chrono::duration<float>(deltaTimeUs).count();
                
		auto& io = ImGui::GetIO();
		inputHandler.SetUICapture(io.WantCaptureMouse, io.WantCaptureKeyboard);

		glfwPollEvents();
		inputHandler.Advance();
		mCamera.Update_Ass5(deltaTimeUs, inputHandler);
		our_position = mCamera.mWorld.GetTranslation();//
        gun_direction = mCamera.mWorld.GetMatrix() * glm::vec4(.0f,.0f,-1.0f,1.f);

        for (int i = 0; i<N; i++){
            asteroids[i].update_pos(deltaTime);
        }

        for (auto& bullet: bullets){
            bullet.update_pos(deltaTime);
        }

        for (int i = 0; i<N-1; i++){
            for (int j = i + 1; j<N; j++){
                auto collision = test_collision(asteroids[i], asteroids[j]);
                if (collision){
                    auto last_collision = collisions[i];
                    auto now = high_resolution_clock::now();
                    if (duration_cast<milliseconds>(now - last_collision) > 500ms){
                        std::cout<<"("<<count++<<") Collision detected between "<<i<<" and "<<j<<std::endl;
                        collisions[i] = now;
                        asteroids[i].collision( asteroids[j] );
                        asteroids[j].collision( asteroids[i] );
                    }
                  
                }
            }
        }
        

		if (inputHandler.GetKeycodeState(GLFW_KEY_R) & JUST_PRESSED) {
			shader_reload_failed = !program_manager.ReloadAllPrograms();
			if (shader_reload_failed)
				tinyfd_notifyPopup("Shader Program Reload Error",
				                   "An error occurred while reloading shader programs; see the logs for details.\n"
				                   "Rendering is suspended until the issue is solved. Once fixed, just reload the shaders again.",
				                   "error");
		}

        if (inputHandler.GetKeycodeState(GLFW_KEY_SPACE) & JUST_PRESSED){
            bullet bul = generate_bullet(our_position, gun_direction);
            bul.node.set_program(&bullet_shader, set_uniforms);
            bonobo::material_data demo_material;
            demo_material.ambient = glm::vec3(0.1f, 0.1f, 0.1f);
            demo_material.diffuse = glm::vec3(0.7f, 0.7f, 0.0f);
            demo_material.specular = glm::vec3(.5f, 1.0f, 1.0f);
            demo_material.shininess = 10.0f;
            bul.node.set_material_constants(demo_material);
            bul.node.add_texture("bulletSpecTex", bulletSpecTex, GL_TEXTURE_2D);
            bul.node.add_texture("bulletDiffTex", bulletDiffTex, GL_TEXTURE_2D);
            bullets.push_back(bul );
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
            for (int i = 0; i<N; i++){
                
                asteroids[i].node.render(mCamera.GetWorldToClipMatrix());
            }

            for (auto bullet: bullets){
                bullet.node.render(mCamera.GetWorldToClipMatrix());
            }
    
          //
			// Todo: Render all your geometry here.
			//
		}


		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        

		//
		// Todo: If you want a custom ImGUI window, you can set it up
		//       here
		//
		bool const opened = ImGui::Begin("Scene Controls", nullptr, ImGuiWindowFlags_None);
		if (opened) {
			ImGui::Checkbox("Show basis", &show_basis);
            bonobo::uiSelectPolygonMode("Polygon mode", polygon_mode);
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
		edaf80::Assignment5 assignment5(framework.GetWindowManager());
		assignment5.run();
	} catch (std::runtime_error const& e) {
		LogError(e.what());
	}



}
