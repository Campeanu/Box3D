#include "Box3D/Renderer/OpenGLContext.hpp"

#include "Box3D/Core.hpp"
#include "Box3D/Log.hpp"

#include <GLFW/glfw3.h>
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif


namespace box3d {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		BOX3D_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		
        #if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
			bool err = gl3wInit() != 0;
		#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
			bool status = glewInit();
        #elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
            int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
            BOX3D_CORE_ASSERT(status, "Could not initializate GLAD!");
		#else
			bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
		#endif

		BOX3D_CORE_INFO("OpenGL Info:");
		BOX3D_CORE_INFO("Vendor:   {0}", glGetString(GL_VENDOR));
		BOX3D_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
		BOX3D_CORE_INFO("Version:  {0}", glGetString(GL_VERSION));

	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}
