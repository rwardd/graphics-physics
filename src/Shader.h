#pragma once
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
 
#include <stdlib.h>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

class Shader
{
public:

    enum class ShaderType {
        Vertex,
        Fragment,
    };

    // Check and load a shader
    Shader(const char* path, uint shader_type_);

    // Get the initialised shader
    uint get_shader();

private:
    int check_compile_errors(uint shader, uint shader_type);

    uint const shader_type;
    uint initialised_shader;

};
