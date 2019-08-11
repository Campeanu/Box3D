#ifndef __SHADER_HPP_INCLUDED__
#define __SHADER_HPP_INCLUDED__

#include <string>
#include <vector>

#include "Box3D/Core.hpp"
#include "Box3D/Log.hpp"

#include <glm/glm.hpp>

#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

/**
 * In the future we will add a shader class per Platform/Renderer so I thik that class need to be an interface. 
 * For now I will make this class only for OpenGL/Window platform (I don't have to mutch time now to implement this per platform).
 */

namespace box3d {

    class Shader {
    public:
        Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
        virtual ~Shader();
        void bind() const;
        void unbind() const;
        

        void setBool  (const std::string &name, bool  value) const;
        void setInt   (const std::string &name, int   value) const;
        void setFloat (const std::string &name, float value) const;
        
        void setVec2  (const std::string &name, const glm::vec2 &value) const;
        void setVec2  (const std::string &name, float x, float y) const;
        void setVec3  (const std::string &name, const glm::vec3 &value) const;
        void setVec3  (const std::string &name, float x, float y, float z) const;
        void setVec4  (const std::string &name, const glm::vec4 &value) const;
        void setVec4  (const std::string &name, float x, float y, float z, float w); 
        
        void setMat2  (const std::string &name, const glm::mat2 &mat) const;
        void setMat3  (const std::string &name, const glm::mat3 &mat) const;
        void setMat4  (const std::string &name, const glm::mat4 &mat) const;


    private:
        uint32_t m_rendererID;
    };

}

#endif // !__SHADER_HPP_INCLUDED__
