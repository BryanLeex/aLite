//
// Created by Bryan on 07/08/2024.
//

#ifndef ALITE_SHADERLOADER_H
#define ALITE_SHADERLOADER_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <stdexcept>
#include <fstream>
#include <filesystem>

#include "Context/Device/Device.h"

namespace Render::Resources::Loaders {

    class ShaderLoader {

    public:
        ShaderLoader() = delete;
        ~ShaderLoader() = delete;

        static GLuint Create(const std::string& p_filePath);

        static std::pair<std::string, std::string> ParseShader(const std::string& p_filePath);

        static GLuint CreateProgram(const std::string& p_vertexShader, const std::string& p_fragmentShader);

        static GLuint Compile(GLuint p_type, const std::string& p_source);

        static void Destroy(const GLuint p_progID);

    };

}

#endif //ALITE_SHADERLOADER_H
