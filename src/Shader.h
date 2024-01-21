#pragma once

class Shader
{
public:

    enum class ShaderType {
        Vertex,
        Fragment,
    };

    Shader(const char* path, ShaderType shader_type_);

private:
    const ShaderType shader_type;

};
