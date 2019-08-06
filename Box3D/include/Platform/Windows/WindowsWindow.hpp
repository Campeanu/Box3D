#ifndef __WINDOWSWINDOW_HPP_INCLUDED__
#define __WINDOWSWINDOW_HPP_INCLUDED__

#include "Box3D/Window.hpp"

#include <GLFW/glfw3.h>

namespace box3d {

    class WindowsWindow : public Window {
    public: 
        WindowsWindow(const WindowProps& props);
        virtual ~WindowsWindow();

        void update() override;

        inline unsigned int getWidth()  const override { return m_data.width;  };
        inline unsigned int getHeight() const override { return m_data.height; };
        
        inline void setEventCallback(const EventCallbackFn& callback) override { m_data.EventCallback = callback; }
        
        void setVSync(bool enabled) override;
        bool isVSync() const override;

    private:
        virtual void init(const WindowProps& props);
        virtual void shutDown();
    private:
        GLFWwindow* m_window;

        struct WindowData {
            std::string  title;
            unsigned int width, height;

            bool VSync;

            EventCallbackFn EventCallback;
        };

        WindowData m_data;

    };

}

#endif // !__WINDOWSWINDOW_HPP_INCLUDED__