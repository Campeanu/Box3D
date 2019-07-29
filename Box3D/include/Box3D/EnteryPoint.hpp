#ifndef __ENTRYPOINT_HPP_INCLUDED__
#define __ENTRYPOINT_HPP_INCLUDED__

    extern box3d::Application* box3d::CreateApplication();

    #ifdef BOX3D_PLATFORM_WINDOW

        int main(int argc, char** argv)
        {
            auto app = box3d::CreateApplication();
            app->run();
            delete app;
        }

    #endif // WINDOW_PLATFORM_SELECTED

#endif // !__ENTRYPOINT_HPP_INCLUDED_
