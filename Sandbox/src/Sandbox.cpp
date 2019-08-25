#include <Box3D.hpp>

#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

#include "imgui.h"

#include "Box3D/Events/ApplicationEvent.hpp"

#include <GLFW/glfw3.h>

#include "Box3D/Renderer/FrameBuffer.hpp"
#include "Box3D/Renderer/TextureBuffer.hpp"
#include "Box3D/Renderer/RenderBufferObject.hpp"

class ApplicationLayer : public box3d::Layer {
public:
    ApplicationLayer()
        : Layer("Example")
    {

        this->showScene = true;

        const char* vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "layout (location = 1) in vec3 aColor;\n"
            "out vec3 ourColor;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos, 1.0);\n"
            "   ourColor = aColor;\n"
            "}\0";

        const char* fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "in vec3 ourColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(ourColor, 1.0f);\n"
            "}\0\n";

        this->shader = new box3d::Shader(vertexShaderSource, fragmentShaderSource);
        this->shader->bind();

        // Set up vertex data (and buffer(s)) and configure vertex attributes.
        // -------------------------------------------------------------------
        float vertices[] {
            // positions         // colors
             0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
             0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top
        };

        unsigned int indices[] {
            0, 1 , 2
        };

        this->vao = new box3d::VertexArray();
        this->vbo = new box3d::VertexBuffer(vertices, 6 * 3 * sizeof(float));

        this->layout = new box3d::VertexBufferLayout();
        this->layout->push<float>(3);
        this->layout->push<float>(3);

        this->vao->AddBuffer(*this->vbo, *this->layout);

        this->ebo = new box3d::IndexBuffer(indices, 3);

        this->shader->unbind();
        this->vao->unbind();
        this->vbo->unbind();
        this->ebo->unbind();

        // --------------------------------------------------------------------------------------

        const char* vertexFrameBufferScreenShaderSource = "#version 330 core\n"
            "layout(location = 0) in vec2 aPos;\n"
            "layout(location = 1) in vec2 aTexCoords;\n"
            "out vec2 TexCoords;\n"
            "void main()\n"
            "{\n"
            "   TexCoords = aTexCoords;\n"
            "   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
            "}\0";

        const char* fragmentFrameBufferScreenShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "in vec2 TexCoords;\n"
            "uniform sampler2D screenTexture;\n"
            "void main()\n"
            "{\n"
            "   vec3 col = texture(screenTexture, TexCoords).rgb;\n"
            "   FragColor = vec4(col, 1.0);\n"
            "}\0\n";

        this->shaderScreen = new box3d::Shader(vertexFrameBufferScreenShaderSource, fragmentFrameBufferScreenShaderSource);
        this->shaderScreen->bind();
        this->shaderScreen->setInt("screenTexture", 0);

        // Vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // -------------------------------------------------------------------------------------------
        float quadVertices[] = {
            // positions   // texCoords
            -1.0f,  1.0f,  0.0f, 1.0f,
            -1.0f, -1.0f,  0.0f, 0.0f,
             1.0f, -1.0f,  1.0f, 0.0f,

            -1.0f,  1.0f,  0.0f, 1.0f,
             1.0f, -1.0f,  1.0f, 0.0f,
             1.0f,  1.0f,  1.0f, 1.0f
        };

        // QUAD buffers.
        // -------------
        this->quadvao = new box3d::VertexArray();
        this->quadvbo = new box3d::VertexBuffer(quadVertices, 4 * 6 * sizeof(float));

        this->quadlayout = new box3d::VertexBufferLayout();
        this->layout->push<float>(2);
        this->layout->push<float>(2);

        this->quadvao->AddBuffer(*this->quadvbo, *this->quadlayout);

        this->shaderScreen->unbind();
        this->quadvao->unbind();
        this->quadvbo->unbind();

        // --------------------------------
        // -- Framebuffer configuration. --
        // --------------------------------
        this->frameBuffer = new box3d::FrameBuffer();

        // -- Create a color attachment texture
        // ---------------------------------
        this->textureColorBuffer = new box3d::TextureBuffer();

        // Create a renderbuffer object for depth and stencil attachment (we won't be sampling these).
        // -------------------------------------------------------------------------------------------;
        this->rendererBufferObject = new box3d::RenderBufferObject();

        // ---------------------------------------------------------------------
        // -- frameBuffer->AddBuffer Steps
        // ---------------------------------------------------------------------
        // -- Use a single renderbuffer object for both a depth AND stencil buffer.
        // ---------------------------------------------------------------------
        // -- Now actually attach it.
        // -----------------------
        // -- Now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now.
        // -----------------------------------------------------------------------------------------------------------------------
        frameBuffer->AddBuffer(*this->rendererBufferObject, *this->textureColorBuffer, this->app);

        frameBuffer->unbind();
        textureColorBuffer->unbind();
        rendererBufferObject->unbind();

        // ---------------------
        // -- Draw as wireframe.
        // ---------------------
        // -- glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // ---------------------------------------------
    }

    ~ApplicationLayer()
    {
        delete this->shader;
        delete this->vao;
        delete this->vbo;
        delete this->ebo;
        delete this->layout;

        delete this->frameBuffer;
        delete this->textureColorBuffer;
        delete this->rendererBufferObject;

        delete this->shaderScreen;
        delete this->quadvao;
        delete this->quadvbo;
        delete this->quadlayout;
    }

    void OnUpdate(box3d::Timestep ts) override
    {
        // -----------------------------------------
        // -- DO NOT FOGOT TO SET THE glViewPort !!!
        // -----------------------------------------
        // -- Bind the frame buffers
        // -- Enable depth testing (is disabled for rendering screen-space quad).
        // -------------------------------------------------------------------
        // -- Make sure we clear the framebuffer's content.
        // ---------------------------------------------

        this->frameBuffer->setGLViewPort(1920, 1080);
        this->frameBuffer->bind();
        this->frameBuffer->glDepthTest(true);
        this->frameBuffer->clear(0.1f, 0.1f, 0.1f, 1.0f, true);


        // ---------------
        // -- DRAW AREA --
        // ---------------

        this->shader->bind();
        this->vao->bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        this->vao->unbind();

        // ---------------
        // -- DRAW AREA --
        // ---------------


        // -----------------------------------------
        // -- DO NOT FOGOT TO SET THE glViewPort WITH ACTUALIZED DATA OF WINDOW !!!
        // -- Now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture.
        // -------------------------------------------------------------------------------------------------------
        // -- Disable depth test so screen-space quad isn't discarded due to depth test.
        // --------------------------------------------------------------------------
        // -- Clear all relevant buffers.
        // ---------------------------
        // -- Set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways).
        // ----------------------------------------------------------------------------------------------------------------

        this->frameBuffer->setGLViewPort(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
        this->frameBuffer->unbind();
        this->frameBuffer->glDepthTest(false);
        this->frameBuffer->clear(1.0f, 1.0f, 1.0f, 1.0f, false);

        // Use the color attachment texture as the texture of the quad plane.
        // ------------------------------------------------------------------
        this->shaderScreen->bind();
        this->quadvao->bind();
        glBindTexture (GL_TEXTURE_2D, textureColorBuffer->getRendererID());

        glDrawArrays  (GL_TRIANGLES, 0, 6);

        this->quadvao->unbind();

    }

    virtual void OnImGuiRender() override
    {
        this->DrawMainScene();
        this->Hierarchy();
        this->Inspector();
        this->Project();
        this->Console();
    }

    void OnEvent(box3d::Event& event) override
    {
        // BOX3D_TRACE("{0}", event);
        // --------------------------
    }

private:
    void DrawMainScene()
    {

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

        // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked).
        // ------------------------------------------------------------------------------------------------------------------
        ImGui::Begin("Scene", NULL);

        // ImGui::Image((void*)(intptr_t)this->textureColorBuffer->getRendererID(), ImVec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight()));
        // -----------------------------------------------------------------------------------------------------------------------

        ImVec2 pos = ImGui::GetCursorScreenPos();

        ImGui::GetWindowDrawList()->AddImage (
            (void*)(intptr_t)this->textureColorBuffer->getRendererID(), ImVec2(ImGui::GetCursorScreenPos()),
            ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetWindowWidth(), ImGui::GetCursorScreenPos().y + ImGui::GetWindowHeight()),
            ImVec2(0, 1),
            ImVec2(1, 0)
        );

        ImGui::End();
        ImGui::PopStyleVar();

    }

    void Hierarchy()
    {
        ImGui::Begin("Hierarchy", NULL);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::End();
    }

    void Project()
    {
        ImGui::Begin("Project", NULL);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::End();
    }

    void Inspector()
    {
        ImGui::Begin("Inspector", NULL);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::End();
    }

    void Console()
    {
        ImGui::Begin("Console", NULL);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::End();
    }

    // Application properties.
    // -----------------------
private:
    box3d::Application& app = box3d::Application::Get();
    GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

    // -- Darw data
    // ------------
private:
    // Triangle properties.
    // --------------------
    box3d::Shader* shader;
    box3d::VertexArray*  vao;
    box3d::IndexBuffer*  ebo;
    box3d::VertexBuffer* vbo;
    box3d::VertexBufferLayout* layout;

    // Frame buffer.
    // -------------
    box3d::FrameBuffer* frameBuffer;
    box3d::TextureBuffer* textureColorBuffer;
    box3d::RenderBufferObject* rendererBufferObject;

    // -- Frame buffer proiperties.
    // ----------------------------
    box3d::Shader* shaderScreen;
    box3d::VertexArray*  quadvao;
    box3d::VertexBuffer* quadvbo;
    box3d::VertexBufferLayout* quadlayout;

    // -- ImGui properties.
    // --------------------
private:
    bool showScene;

};

class Sandbox : public box3d::Application {
    // Public methods
public:
    Sandbox()
    {
        PushOverlay(new ApplicationLayer());
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
