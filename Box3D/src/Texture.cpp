#include <Box3D/Renderer/Texture.hpp>

namespace box3d {

    Texture::Texture(std::string path)
        : path { path }
    {
        glGenTextures(1, &this->m_rendererID);
        glBindTexture(GL_TEXTURE_2D, this->m_rendererID);

        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        stbi_set_flip_vertically_on_load(true);

        this->data = stbi_load(this->path.c_str(), &this->width, &this->height, &this->nrChannels, 0);
    }

    Texture::~Texture()
    {
    }

    void Texture::bind() const
    {
        glBindTexture(GL_TEXTURE_2D, this->m_rendererID);
    }

    void Texture::unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::createTexture(bool typeformat)
    {
        if (this->data)
        {
            if(typeformat == true)
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->data);
            else
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,  this->width, this->height, 0, GL_RGB,  GL_UNSIGNED_BYTE, this->data);

            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }

        stbi_image_free(this->data);
    }

}
