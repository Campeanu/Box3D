#include "Box3D/Renderer/Shader.hpp"

namespace box3d {

    Shader::Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
    {
        const char* source;
        int isCompiled = 0;


        // Build and compile our shader program.
        // -------------------------------------
       
        // Vertex shader.
        // --------------
        int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        source = vertexShaderSource.c_str();
        glShaderSource(vertexShader, 1, &source, 0);
        glCompileShader(vertexShader);

        // Check for shader compile errors.
        // --------------------------------
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character.
			// ------------------------------------------
            std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
            // ---------------------------------
			glDeleteShader(vertexShader);

			BOX3D_CORE_ERROR ("{0}", infoLog.data());
			BOX3D_CORE_ASSERT(false, "Vertex shader compilation failure!");
			
            return;
		}

        // Fragment shader.
        // ----------------
        int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); 
        source = fragmentShaderSource.c_str();
        glShaderSource(fragmentShader, 1, &source, 0);
        glCompileShader(fragmentShader);

        // Check for shader compile errors.
        // --------------------------------
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE)
        {
            int maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character.
            // ------------------------------------------
            std::vector<char> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

            // We don't need the shader anymore.
            // ---------------------------------
            glDeleteShader(fragmentShader);
            
			BOX3D_CORE_ERROR ("{0}", infoLog.data());
			BOX3D_CORE_ASSERT(false, "Fragment shader compilation failure!");
			
            return;
        }

        // Link shaders.
        // -------------

        // Vertex and fragment shaders are successfully compiled.
		// ------------------------------------------------------
        // Now time to link them together into a program.
        // ----------------------------------------------
		// Get a program object.
        // ---------------------

        this->m_rendererID = glCreateProgram();
        int program = this->m_rendererID; 

        // Attach shader to our program.
        // -----------------------------

        glAttachShader(program, vertexShader  );
        glAttachShader(program, fragmentShader);

        // Link our program.
        // -----------------
        glLinkProgram(program);
		
        int isLinked = 0;
        
        // Check for program link errors.
        // --------------------------------
        glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			// ----------------------------------
            glDeleteProgram(program);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			BOX3D_CORE_ERROR  ("{0}", infoLog.data());
			BOX3D_CORE_ASSERT (false, "Shader link failure!");
			return;
		}

        // Detach shaders after a successful link.
		// ---------------------------------------
        glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
    }
    
    Shader::~Shader()
    {
        glDeleteProgram(this->m_rendererID);       
    }
    
    void Shader::bind() const
    {
        glUseProgram(this->m_rendererID);
    }

    void Shader::unbind() const 
    {
        glUseProgram(0);
    }

    // Utility uniform functions.
  
    // --------------------------
    void Shader::setBool(const std::string &name, bool value) const
    {         
        glUniform1i(glGetUniformLocation(this->m_rendererID, name.c_str()), (int)value); 
    }
  
    // ------------------------------------------------------------------------
    void Shader::setInt(const std::string &name, int value) const
    { 
        glUniform1i(glGetUniformLocation(this->m_rendererID, name.c_str()), value); 
    }
  
    // ------------------------------------------------------------------------
    void Shader::setFloat(const std::string &name, float value) const
    { 
        glUniform1f(glGetUniformLocation(this->m_rendererID, name.c_str()), value); 
    }
  
    // ------------------------------------------------------------------------
    void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
    { 
        glUniform2fv(glGetUniformLocation(this->m_rendererID, name.c_str()), 1, &value[0]); 
    }
  
    void Shader::setVec2(const std::string &name, float x, float y) const
    { 
        glUniform2f(glGetUniformLocation(this->m_rendererID, name.c_str()), x, y); 
    }
  
    // ------------------------------------------------------------------------
    void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
    { 
        glUniform3fv(glGetUniformLocation(this->m_rendererID, name.c_str()), 1, &value[0]); 
    }
    void Shader::setVec3(const std::string &name, float x, float y, float z) const
    { 
        glUniform3f(glGetUniformLocation(this->m_rendererID, name.c_str()), x, y, z); 
    }
  
    // ------------------------------------------------------------------------
    void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
    { 
        glUniform4fv(glGetUniformLocation(this->m_rendererID, name.c_str()), 1, &value[0]); 
    }
    void Shader::setVec4(const std::string &name, float x, float y, float z, float w) 
    { 
        glUniform4f(glGetUniformLocation(this->m_rendererID, name.c_str()), x, y, z, w); 
    }
  
    // ------------------------------------------------------------------------
    void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(this->m_rendererID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
  
    // ------------------------------------------------------------------------
    void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(this->m_rendererID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
  
    // ------------------------------------------------------------------------
    void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(this->m_rendererID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

}
