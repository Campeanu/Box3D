#ifndef __WINDOW_HPP_INCLUDED__
#define __WINDOW_HPP_INCLUDED__

#include "Box3D/Core.hpp"
#include "Box3D/Events/Event.hpp"

#include "Box3D/Log.hpp"

namespace box3d {

    struct WindowProps {
        std::string  title;
        unsigned int width;
        unsigned int height;

        WindowProps(
            const std::string& title = "Box3D", 
            unsigned int width  = 1920,
            unsigned int height = 1080
        )
            : title{title}, width{width}, height{height}
        {

        }

    };

    class Window {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window()
        {

        }

        virtual void update() = 0;

        virtual unsigned int getWidth()  const = 0;
        virtual unsigned int getHeight() const = 0;

        // Window atributes
        virtual void setEventCallback(const EventCallbackFn& callback) = 0;
        virtual void setVSync(bool enabled) = 0;
        virtual bool isVSync() const = 0;

        static Window* create(const WindowProps& props = WindowProps());

    }; // Window

}

#endif // !__WINDOW_HPP_INCLUDED__