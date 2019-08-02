#include <Box3D.hpp>

class Sandbox : public box3d::Application {
    // Public methods
public:
    Sandbox()
    {
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
