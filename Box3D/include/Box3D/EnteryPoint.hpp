#ifndef __ENTRYPOINT_HPP_INCLUDED__
#define __ENTRYPOINT_HPP_INCLUDED__

    extern box3d::Application* box3d::CreateApplication();

    #ifdef BOX3D_PLATFORM_WINDOW
        
        int main(int argc, char** argv)
        {

            box3d::Log::Init();

            /**
             *  BOX3D_CORE_WARN ("Initializate core   log! Test warn log.");
             *  BOX3D_INFO      ("Initializate client log! Test info log.");
             */

            auto app = box3d::CreateApplication();
            app->Run();
            delete app;
        }

    #endif // WINDOW_PLATFORM_SELECTED

#endif // !__ENTRYPOINT_HPP_INCLUDED_
