#include "Box3D/Application.hpp"

#include "Box3D/Log.hpp"

#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

#include <GLFW/glfw3.h>

namespace box3d {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

    Json::Value Application::getProps()
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

    void Application::initProps()
    {
        const auto configurations = this->getProps();

        if (configurations.Has("title")) {
            this->title = (std::string)configurations["title"];
        }

        if (configurations.Has("width")) {
            this->width = (int)configurations["width"];
        }

        if (configurations.Has("height")) {
            this->height = (int)configurations["height"];
        }
    }

    Application::Application()
    {
        BOX3D_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        this->initProps();

        WindowProps windowprops(this->title, this->width,this->height);

        m_Window = std::unique_ptr<Window>(Window::Create(windowprops));
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushLayer(m_ImGuiLayer);
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer* layer)
    {
        m_LayerStack.PushOverlay(layer);
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            (*--it)->OnEvent(e);
            if (e.Handled)
                break;
        }
    }

    void Application::Run()
    {
        while (m_Running)
        {
            float time = (float)glfwGetTime();
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            for (Layer* layer : m_LayerStack)
                layer->OnUpdate(timestep);

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();

        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }
} // namespace box3d
