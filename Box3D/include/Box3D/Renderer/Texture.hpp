#ifndef __TEXTURE_HPP_INCLUDED__
#define __TEXTURE_HPP_INCLUDED__

#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
    #include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
    #include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
    #include <glad/glad.h>  // Initialize with gladLoadGL()
#else
    #include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

#include <string>
#include <iostream>

#include <Json/value.hpp>
#include <SystemAbstractions/File.hpp>
#include <SystemAbstractions/StringExtensions.hpp>

#include "Box3D/Renderer/stb_texture_loader/stb_image.h"

namespace box3d {

    class Texture
    {
    public:
        Texture(std::string path);
        virtual ~Texture();

        void bind() const;
        void unbind() const;

        void createTexture(bool typeformat);

        void setPath(std::string path) { this->path = path; }
        std::string setPath() { return this->path; }

        // Texture properties
    private:
        int width;
        int height;
        int nrChannels;
    private:
        unsigned int m_rendererID;
        unsigned char* data;

        std::string path;

    };

}; // box3d

#endif // !__TEXTURE_HPP_INCLUDED__
