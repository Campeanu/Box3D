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

        /*
         * ***************************************************
         */

        glShadeModel(GL_SMOOTH);                    // shading mathod: GL_SMOOTH or GL_FLAT
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      // 4-byte pixel alignment

        // enable /disable features
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
        glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);

        // track material ambient and diffuse from surface color, call it before glEnable(GL_COLOR_MATERIAL)
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL);

        glClearColor(0, 0, 0, 0);                   // background color
        glClearStencil(0);                          // clear stencil buffer
        glClearDepth(1.0f);                         // 0 is near, 1 is far
        glDepthFunc(GL_LEQUAL);

        /*
         * ***************************************************
         */


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
