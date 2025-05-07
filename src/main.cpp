#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>

void keyCallback(
    GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/) {
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main(int /*argc*/, char* /*argv*/[]) {
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window =
        glfwCreateWindow(800, 600, "Hello OpenGL", nullptr, nullptr);
    if(window == nullptr) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Set the required callback functions
    glfwSetKeyCallback(window, keyCallback);

    // Set this to true so GLEW knows to use a modern approach to retrieving
    // function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if(glewInit() != GLEW_OK) {
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // Build and compile our shader program
    // Vertex shader
    const GLchar* vertex_shader_source =
        "#version 460 core\n"
        "layout (location = 0) in vec3 position;\n"
        "void main() {\n"
        "    gl_Position = vec4(position, 1.0);\n"
        "}\0";
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
    glCompileShader(vertex_shader);
    GLint success;
    GLchar info_log[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

    if(!success) {
        glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << info_log << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // Fragment shader
    const GLchar* fragment_shader_source =
        "#version 460 core\n"
        "out vec4 color;\n"
        "void main() {\n"
        "    color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragment_shader, 512, nullptr, info_log);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << info_log << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // Link shaders
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shader_program, 512, nullptr, info_log);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << info_log << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    glUseProgram(shader_program);

    // Delete the shaders as they're linked into our program now and no longer
    // needed
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // Set up vertex data (and buffer(s)) and attribute pointers
    // clang-format off
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
         0.5f, -0.5f, 0.0f, // right
         0.0f,  0.5f, 0.0f  // top
    };
    // clang-format on

    // Create a vertex buffer object (VBO)
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s)
    // and attribute pointer(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Set up vertex data (and buffer(s)) and configure vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                          static_cast<GLvoid*>(0));
    glEnableVertexAttribArray(0);

    // Note that this is allowed, the call to glVertexAttribPointer registered
    // VBO as the currently bound vertex buffer object so afterwards we can
    // safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any
                          // buffer/array to prevent strange bugs)
    while(!glfwWindowShouldClose(window)) {
        // Check if any events have been activiated (key pressed, mouse moved
        // etc.) and call corresponding response functions
        glfwPollEvents();
        // Render
        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the triangle
        glUseProgram(shader_program);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        // glBindVertexArray(0); // Unbind VAO
        glfwSwapBuffers(window);
    }
    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();

    return 0;
}