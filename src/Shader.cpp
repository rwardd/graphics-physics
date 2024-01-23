#include <Shader.h>

Shader::Shader(const char* path, uint shader_type_)
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
        shader_code = shader_stream.str();
    }
    catch(std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << "\n";
    }

    const char* gl_shader_code = shader_code.c_str();

    uint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &gl_shader_code, NULL);
    glCompileShader(shader);
    int status = check_compile_errors(shader, shader_type);
    
    initialised_shader = status < 0 ? status : shader;
}

uint Shader::get_shader()
{
    return initialised_shader;
}

int Shader::check_compile_errors(uint shader, uint shader_type)
{
    char log[1024];
    int success = 0;
    if (shader_type != 0) { /* Shader */
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, log);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << shader_type << "\n" 
                << log << "\n -- --------------------------------------------------- -- \n";
            return -1;
        }
    }
    return 0;
}
