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
            "}\n\0";

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
        

        // screen quad VAO
        // glGenVertexArrays(1, &quadVAO);
        // glGenBuffers(1, &quadVBO);
        // glBindVertexArray(quadVAO);
        // glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        // glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        // glEnableVertexAttribArray(0);
        // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        // glEnableVertexAttribArray(1);
        // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

        // Framebuffer configuration.
        // --------------------------
        glGenFramebuffers(1, &framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

        // Create a color attachment texture
        // ---------------------------------
        glGenTextures(1, &textureColorbuffer);
        glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, app.GetWindow().GetWidth(), app.GetWindow().GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

        // Create a renderbuffer object for depth and stencil attachment (we won't be sampling these).
        // -------------------------------------------------------------------------------------------
        unsigned int rbo;
        glGenRenderbuffers(1, &rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);

        // Use a single renderbuffer object for both a depth AND stencil buffer.
        // ---------------------------------------------------------------------
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

        // Now actually attach it.
        // -----------------------
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

        // Now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now.
        // -----------------------------------------------------------------------------------------------------------------------
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // Draw as wireframe.
        // ------------------
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // ------------------------------------------
    }

    ~ApplicationLayer()
    {
        delete this->shader;
        delete this->vao;
        delete this->vbo;
        delete this->ebo;
        delete this->layout;

        delete this->shaderScreen;
        delete this->quadvao;
        delete this->quadvbo;
        delete this->quadlayout;
    }

    void OnUpdate(box3d::Timestep ts) override
    {
        // !!!!!!!!!
        glViewport(0, 0, 1920, 1080);
        // !!!!!!!!!

        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

        // Enable depth testing (is disabled for rendering screen-space quad).
        // -------------------------------------------------------------------
        glEnable(GL_DEPTH_TEST);

        // Make sure we clear the framebuffer's content.
        // ---------------------------------------------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw our first triangle.
        // ------------------------
        this->shader->bind();

        // Seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized.
        // -------------------------------------------------------------------------------------------------------------------------------
        this->vao->bind();

        // glDrawArrays(GL_TRIANGLES, 0, 6);
        // ---------------------------------

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // No need to unbind glBindVertexArray(0) every time.
        // --------------------------------------------------

        // !!!!!!!!!
        glViewport(0, 0, app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
        // !!!!!!!!!

        // Now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture.
        // -------------------------------------------------------------------------------------------------------
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // Disable depth test so screen-space quad isn't discarded due to depth test.
        // --------------------------------------------------------------------------
        glDisable(GL_DEPTH_TEST); 

        // Clear all relevant buffers.
        // ---------------------------
        // Set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways).
        // ----------------------------------------------------------------------------------------------------------------
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the color attachment texture as the texture of the quad plane.
        // ------------------------------------------------------------------
        this->shaderScreen->bind();
        this->quadvao->bind();
        glBindTexture (GL_TEXTURE_2D, textureColorbuffer);
        glDrawArrays  (GL_TRIANGLES, 0, 6);

        // BOX3D_INFO("ExampleLayer::Update");
        // -----------------------------------
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
        BOX3D_TRACE("{0}", event);
    }

private:
    void DrawMainScene()
    {

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

        // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked).
        // ------------------------------------------------------------------------------------------------------------------
        ImGui::Begin("Scene", NULL);

        // ImGui::Image((void*)(intptr_t)textureColorbuffer, ImVec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight()));
        // -----------------------------------------------------------------------------------------------------------------------

        ImVec2 pos = ImGui::GetCursorScreenPos();

        ImGui::GetWindowDrawList()->AddImage (
            (void*)(intptr_t)textureColorbuffer, ImVec2(ImGui::GetCursorScreenPos()),
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

    // Darw data
private:

    // Triangle properties.
    // --------------------
    box3d::Shader* shader;
    box3d::VertexArray*  vao;
    box3d::IndexBuffer*  ebo;
    box3d::VertexBuffer* vbo;
    box3d::VertexBufferLayout* layout;

    // Frame buffer proiperties.
    // -------------------------
    box3d::Shader* shaderScreen;
    box3d::VertexArray*  quadvao;
    box3d::VertexBuffer* quadvbo;
    box3d::VertexBufferLayout* quadlayout;

    // unsigned int quadVAO, quadVBO;
    unsigned int framebuffer;
    unsigned int textureColorbuffer;

    // ImGui properties.
    // -----------------
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
