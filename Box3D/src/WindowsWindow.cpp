#include <Platform/Windows/WindowsWindow.hpp>

#include "Box3D/Events/ApplicationEvent.hpp"
#include "Box3D/Events/KeyEvent.hpp"
#include "Box3D/Events/MouseEvent.hpp"

namespace box3d {

	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		BOX3D_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }


    Json::Value WindowsWindow::getWindowSettings()
    {
        Json::Value configuration(Json::Value::Type::Object);

        const auto configFile = std::shared_ptr<FILE>(
            fopen(
            (SystemAbstractions::File::GetExeParentDirectory() + "/Settings/windowprops.json").c_str(),
                "rb"
            ),
            [](FILE* f) {
                if (f != NULL) {
                    (void)fclose(f);
                }
            }
        );

        if (configFile == NULL) {
            return configuration;
        }

        if (fseek(configFile.get(), 0, SEEK_END)) {
            fprintf(stderr, "error: unable to open configuration file\n");
            return configuration;
        }

        const auto configSize = ftell(configFile.get());
        if (configSize == EOF) {
            fprintf(stderr, "error: unable to determen end of configuration file\n");
            return configuration;
        }

        if (fseek(configFile.get(), 0, SEEK_SET) != 0) {
            fprintf(stderr, "error: unable to seek to begining of configuration file\n");
            return configuration;
        }

        const __int64 y = (__int64)configSize + 1;
        std::vector<char> encodedConfig(y);

        const auto readResult = fread(encodedConfig.data(), configSize, 1, configFile.get());

        if (readResult != 1) {
            fprintf(stderr, "error: unable read configuration file\n");
            return configuration;
        }

        configuration = Json::Value::FromEncoding(encodedConfig.data());

        return configuration;
    }

    void WindowsWindow::initWindowSettings()
    {
        const auto configurations = this->getWindowSettings();

        if (configurations.Has("isfullscreen")) {
            this->isfullscreen = (bool)configurations["isfullscreen"];
        }
    }

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
        this->initWindowSettings();
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		BOX3D_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			BOX3D_CORE_ASSERT(success, "Could not intialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

        glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
        if(this->isfullscreen)
            glfwMaximizeWindow(m_Window);

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
        m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

}
