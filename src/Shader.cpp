#include <Shader.h>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

Shader::Shader(const char* path, ShaderType shader_type_)
    : shader_type {shader_type_}
{
    std::string shader_code;
    std::ifstream shaderFile;

    shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    
    try {
        shaderFile.open(path);
        std::stringstream shader_stream;
        shader_stream << shaderFile.rdbuf();
        shaderFile.close();
    }
    catch(std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n";
    }
}
