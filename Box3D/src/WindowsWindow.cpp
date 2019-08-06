#include <Platform/Windows/WindowsWindow.hpp>

#include "Box3D/Events/ApplicationEvent.hpp"
#include "Box3D/Events/KeyEvent.hpp"
#include "Box3D/Events/MouseEvent.hpp"

#include <GLAD/glad.h>

namespace box3d {

    static bool s_GLFWInitialized = false;

    static void GLFWErrorCallback(int error, const char* description)
    {
        BOX3D_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }

    Window* Window::create(const WindowProps& props)
    {
        return new WindowsWindow(props);
    }

    WindowsWindow::WindowsWindow(const WindowProps& props)
    {
        init(props);
    }

    WindowsWindow::~WindowsWindow()
    {
        shutDown();
    }

    void WindowsWindow::init(const WindowProps& props)
    {
        m_data.title  = props.title;
        m_data.width  = props.width;
        m_data.height = props.height; 

        BOX3D_CORE_INFO("Creating window {0} {1} {2}", props.title, props.width, props.height);


        if(!s_GLFWInitialized)
        {
            int success = glfwInit();
            BOX3D_CORE_ASSERT(success, "Could not initializate GLFW!");
            glfwSetErrorCallback(GLFWErrorCallback);
            s_GLFWInitialized = true;
        }
        
        m_window = glfwCreateWindow((int)props.width, (int)props.height, props.title.c_str(), nullptr, nullptr);
        glfwMaximizeWindow(m_window);
        glfwMakeContextCurrent(m_window);

        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        BOX3D_CORE_ASSERT(status, "Could not initializate GLAD!");

        glfwSetWindowUserPointer(m_window, &m_data);
        setVSync(true);

        // GLFW callbacks
        glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {

            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            data.width  = width;
            data.height = height;
            WindowResizeEvent event(width, height);
            data.EventCallback(event);

        });

        glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {

            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event);

        });

        glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int modes) {

            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
            }

        });

        glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {

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

        glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset) {

            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.EventCallback(event);

        });

        glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos) {

            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseMovedEvent event((float)xPos, (float)yPos);
            data.EventCallback(event);

        });

    }

    void WindowsWindow::shutDown()
    {
        glfwDestroyWindow(m_window);
    }

    void WindowsWindow::update()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }
    
    void WindowsWindow::setVSync(bool enabled)
    {
        if(enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
        m_data.VSync = enabled;
    }

    bool WindowsWindow::isVSync() const
    {
        return m_data.VSync;
    }

}
