#include <Box3D.hpp>

class ExampleLayer : public box3d::Layer {
public:
    ExampleLayer()
        : Layer("Example")
    {

    }

    void OnUpdate() override
    {
        BOX3D_INFO("ExampleLayer::Update");
    }

    void OnEvent(box3d::Event& event) override
    {
        BOX3D_TRACE("{0}", event);
    }

};

class ExampleOverLayer : public box3d::Layer {
public:
    ExampleOverLayer()
        : Layer("ExampleOverLayer")
    {

    }

    void OnUpdate() override
    {
        BOX3D_INFO("ExampleOverLayer::Update");
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
        PushOverLayer(new ExampleOverLayer());
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
