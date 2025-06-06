#pragma once
#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    unsigned int m_id;
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(const char* vertex_path, const char* fragment_path) {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertex_code;
        std::string fragment_code;
        std::ifstream v_shader_file;
        std::ifstream f_shader_file;
        // ensure ifstream objects can throw exceptions:
        v_shader_file.exceptions(std::ifstream::failbit |
                                 std::ifstream::badbit);
        f_shader_file.exceptions(std::ifstream::failbit |
                                 std::ifstream::badbit);
        try {
            // open files
            v_shader_file.open(vertex_path);
            f_shader_file.open(fragment_path);
            std::stringstream v_shader_stream, f_shader_stream;
            // read file's buffer contents into streams
            v_shader_stream << v_shader_file.rdbuf();
            f_shader_stream << f_shader_file.rdbuf();
            // close file handlers
            v_shader_file.close();
            f_shader_file.close();
            // convert stream into string
            vertex_code = v_shader_stream.str();
            fragment_code = f_shader_stream.str();
        } catch(std::ifstream::failure& e) {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: "
                      << e.what() << std::endl;
        }
        const char* v_shader_code = vertex_code.c_str();
        const char* f_shader_code = fragment_code.c_str();
        // 2. compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &v_shader_code, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &f_shader_code, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        // shader Program
        m_id = glCreateProgram();
        glAttachShader(m_id, vertex);
        glAttachShader(m_id, fragment);
        glLinkProgram(m_id);
        checkCompileErrors(m_id, "PROGRAM");
        // delete the shaders as they're linked into our program now and no
        // longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
    // activate the shader
    // ------------------------------------------------------------------------
    void use() { glUseProgram(m_id); }
    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string& name, bool value) const {
        glUniform1i(glGetUniformLocation(m_id, name.c_str()),
                    static_cast<int>(value));
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string& name, int value) const {
        glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string& name, float value) const {
        glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
    }

private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(unsigned int shader, std::string type) {
        int success;
        char info_log[1024];
        if(type != "PROGRAM") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if(!success) {
                glGetShaderInfoLog(shader, 1024, NULL, info_log);
                std::cout
                    << "ERROR::SHADER_COMPILATION_ERROR of type: " << type
                    << "\n"
                    << info_log
                    << "\n -- "
                       "--------------------------------------------------- -- "
                    << std::endl;
            }
        } else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if(!success) {
                glGetProgramInfoLog(shader, 1024, NULL, info_log);
                std::cout
                    << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                    << info_log
                    << "\n -- "
                       "--------------------------------------------------- -- "
                    << std::endl;
            }
        }
    }
};