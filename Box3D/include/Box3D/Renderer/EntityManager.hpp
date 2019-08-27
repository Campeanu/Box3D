#ifndef __ENTITYMANAGER_HPP_INCLUDED__
#define __ENTITYMANAGER_HPP_INCLUDED__

#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

#include "Box3D/Renderer/Shader.hpp"
#include "Box3D/Renderer/IndexBuffer.hpp"
#include "Box3D/Renderer/VertexArray.hpp"
#include "Box3D/Renderer/VertexBuffer.hpp"
#include "Box3D/Renderer/VertexBufferLayout.hpp"

namespace box3d {

    class EntityManager
    {
    public:
        EntityManager();
        virtual ~EntityManager();
    private:
    };

} // namespace box3d

#endif // __ENTITYMANAGER_HPP_INCLUDED__
