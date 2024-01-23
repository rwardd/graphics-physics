#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
 
#include <linmath.h>
#include <stdlib.h>
#include <stdio.h>

#include <Shader.h>
 
static const struct
{
    float x, y, z;
    float r, g, b;
} vertices[4] =
{
    { -0.6f, -0.4f, 0.f,    1.f, 0.f, 0.f },
    {  0.6f, -0.4f, 0.f,    0.f, 1.f, 0.f },
    {  0.f,   0.6f, 0.f,    0.f, 0.f, 1.f },
    { -0.6f, -0.6f, 0.6f,   0.f, 0.f, 1.f }
};
 
static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}
 
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}
 
int main(void)
{
    GLFWwindow* window;
    GLuint vertex_buffer, vertex_shader, fragment_shader, program;
    GLint mvp_location, vpos_location, vcol_location;
    glfwSetErrorCallback(error_callback);
 
    if (!glfwInit())
        exit(EXIT_FAILURE);
 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
 
    window = glfwCreateWindow(640, 480, "Physics Engine", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
 
    glfwSetKeyCallback(window, key_callback);
 
    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);
 
    // NOTE: OpenGL error checks have been omitted for brevity
 
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create and load some shaders
    auto vertex_shader_instance = new Shader {"/home/rward/graphics-physics/src/shaders/vertex.glsl", GL_VERTEX_SHADER};
    auto fragment_shader_instance = new Shader {"/home/rward/graphics-physics/src/shaders/fragment.glsl", GL_FRAGMENT_SHADER};

    // Get their shader IDs
    vertex_shader = vertex_shader_instance->get_shader();
    fragment_shader = fragment_shader_instance->get_shader();

    // Error Checking
    if (vertex_shader < 0 || fragment_shader < 0) {
        glfwDestroyWindow(window);
 
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Create the program, and link shaders
    program = glCreateProgram();
    glAttachShader(program, vertex_shader_instance->get_shader());
    glAttachShader(program, fragment_shader_instance->get_shader());
    glLinkProgram(program);

    // Free memory that is no longer needed
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    delete vertex_shader_instance;
    delete fragment_shader_instance;

    mvp_location = glGetUniformLocation(program, "MVP");
    vpos_location = glGetAttribLocation(program, "vPos");
    vcol_location = glGetAttribLocation(program, "vCol");

    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE,
                          sizeof(vertices[0]), (void*) 0);

    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
                          sizeof(vertices[0]), (void*) (sizeof(float) * 3));

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        mat4x4 m, p, mvp;
 
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
 
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
 
        mat4x4_identity(m);
        mat4x4_rotate_Z(m, m, (float) glfwGetTime());
        mat4x4_rotate_X(m, m, (float) glfwGetTime());
        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        mat4x4_mul(mvp, p, m);

        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
 
    glfwDestroyWindow(window);
 
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
