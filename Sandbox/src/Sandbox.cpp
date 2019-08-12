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
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";

        const char* fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
            "}\n\0";

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

        // Set up vertex data (and buffer(s)) and configure vertex attributes.
        // -------------------------------------------------------------------
        float vertices[] = {
             0.5f,  0.5f, 0.0f,  // top right
             0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left 
        };

        unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,                // first Triangle
            1, 2, 3                 // second Triangle
        };

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

        shader = new box3d::Shader(vertexShaderSource, fragmentShaderSource);
        shaderScreen = new box3d::Shader(vertexFrameBufferScreenShaderSource, fragmentFrameBufferScreenShaderSource);

        unsigned int VBO, EBO;

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        // Bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        // ----------------------------------------------------------------------------------------------------------------
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind.
        // --------------------------------------------------------------------------------------------------------------------------------------------------------------------
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
        // ----------------------------------------------------------------------------------------------------------------------------------
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        // -----------------------------------------

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        // ----------------------------------------------------------------------------------------------------------------------------------

        // screen quad VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

        glBindVertexArray(0);


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
        shader->bind();

        // Seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized.
        // -------------------------------------------------------------------------------------------------------------------------------
        glBindVertexArray(VAO);

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
        shaderScreen->bind();
        glBindVertexArray(quadVAO);
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
        ImGui::Begin("Scene", NULL);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Image((void*)(intptr_t)textureColorbuffer, ImVec2(ImGui::GetWindowWidth() - 15, ImGui::GetWindowHeight() - 35));
        ImGui::End();
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
private:

    bool showScene;

    box3d::Shader* shader;
    box3d::Shader* shaderScreen;

    unsigned int  VAO;

    unsigned int framebuffer;
    unsigned int textureColorbuffer;
    unsigned int quadVAO, quadVBO;

    box3d::Application& app = box3d::Application::Get();
    GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

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
