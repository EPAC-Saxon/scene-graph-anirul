#pragma once

#include <memory>
#include <map>
#include <array>
#include <functional>
#include <optional>
#include <SDL2/SDL.h>
#include "Program.h"
#include "Texture.h"
#include "../ShaderGLLib/Buffer.h"
#include "../ShaderGLLib/Vector.h"
#include "../ShaderGLLib/Mesh.h"
#include "../ShaderGLLib/Scene.h"
#include "../ShaderGLLib/Camera.h"

namespace sgl {

	class Device
	{
	public:
		// This will initialize the GL context and make the GLEW init.
		Device(SDL_Window* sdl_window);
		virtual ~Device() = default;

	public:
		// Startup the scene. Throw errors in case there is any.
		void Startup(std::pair<int, int> size);
		// Draw what is on the scene.
		// Take the total time from the beginning of the program to now as a
		// const double parameter.
		void Draw(const double dt);
		// Get the scene description.
		void SetSceneTree(const sgl::SceneTree& scene_tree)
		{
			scene_tree_ = scene_tree;
		}
		// Get texture manager this is made to share texture between the scene
		// and the device.
		void SetTextureManager(const sgl::TextureManager& texture_manager)
		{
			texture_manager_ = texture_manager;
		}
		// Set the camera.
		void SetCamera(const sgl::Camera& camera)
		{
			camera_ = camera;
		}

	public:
		// Get the GL version.
		std::pair<int, int> GetGLVersion() const
		{
			return std::make_pair(major_version_, minor_version_);
		}

	public:
		// This is here for testing purpose!
		SDL_GLContext GetGLContext() const
		{
			return sdl_gl_context_;
		}
		const SceneTree& GetSceneTree() const
		{
			return scene_tree_;
		}
		const TextureManager& GetTextureManager() const
		{
			return texture_manager_;
		}
		const std::shared_ptr<Program>& GetProgram() const
		{
			return program_;
		}

	private:
		// Has to be a shared ptr as the program has to be created after the
		// window is present and the GLEW init is done.
		std::shared_ptr<Program> program_ = nullptr;
		sgl::SceneTree scene_tree_ = {};
		sgl::TextureManager texture_manager_ = {};
		sgl::Camera camera_ = sgl::Camera({ 0.f, 0.f, -4.f });
		SDL_GLContext sdl_gl_context_ = nullptr;
		int major_version_ = 0;
		int minor_version_ = 0;
	};

} // End namespace sgl.
