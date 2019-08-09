#include <Box3D.hpp>

class ExampleLayer : public box3d::Layer {
public:
    ExampleLayer()
        : Layer("Example")
    {
        // system("explorer C:\\");
    }

    void OnUpdate(box3d::Timestep ts) override
    {
        BOX3D_INFO("ExampleLayer::Update");
    }

    void OnEvent(box3d::Event& event) override
    {
        BOX3D_TRACE("{0}", event);
    }

};

class Sandbox : public box3d::Application {
    // Public methods
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
    }

    virtual ~Sandbox()
    {
    }
private:
};

box3d::Application* box3d::CreateApplication()
{
    return new Sandbox();
}
