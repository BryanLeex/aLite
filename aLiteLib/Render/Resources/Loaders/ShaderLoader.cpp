//
// Created by Bryan on 07/08/2024.
//

#include "ShaderLoader.h"

namespace Render::Resources::Loaders {

    GLuint ShaderLoader::Create(const std::string &p_filePath) {

        const auto sources = ParseShader(p_filePath);

        aLog("Loader")->debug("Vert Code: \n{}", sources.first);
        aLog("Loader")->debug("Frag Code: \n{}", sources.second);

        GLuint ProgID = CreateProgram(sources.first, sources.second);

        if (ProgID)
            return ProgID;

        throw std::runtime_error("Can Not Create Shader");

    }

    void ShaderLoader::Destroy(const GLuint p_progID) {

        glDeleteProgram(p_progID);

    }

    GLuint ShaderLoader::Compile(GLuint p_type, const std::string& p_source) {

        const GLuint id = glCreateShader(p_type);

        const char* src = p_source.c_str();

        glShaderSource(id, 1, &src, nullptr);

        glCompileShader(id);

        GLint ret_code;

        glGetShaderiv(id, GL_COMPILE_STATUS, &ret_code);

        if (!ret_code) {

            GLint info_len;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &info_len);

            char *info = new char[info_len];

            glGetShaderInfoLog(id, info_len, &info_len, info);

            aLog("Loader")->error("Compile Error: {}", info);

            glDeleteShader(id);

            return 0;
        }

        return id;

    }

    std::pair<std::string, std::string> ShaderLoader::ParseShader(const std::string &p_filePath) {

        std::string VertCode;
        std::string FragCode;

        if (!std::filesystem::exists(p_filePath)) {
            throw std::runtime_error("Folder Not Excits.");
        }

        std::filesystem::directory_iterator list(p_filePath);

        for (const auto &item : list) {

            aLog("Loader")->info("File Name: {}", item.path().filename().string());

            std::ifstream file (item.path());
            if (!file.is_open()) {
                throw std::runtime_error("Can Not Open File: " + item.path().string());
            }
            std::stringstream ss;

            std::string ext = item.path().extension().string();

            ss.clear();
            ss << file.rdbuf();

            if (ext == ".frag") {
                FragCode = ss.str();
            }
            else if (ext == ".vert") {
                VertCode = ss.str();
            }
            else {
                aLog("Loader")->warn("Unknow Extension: {}", ext);
            }

        }

        return {VertCode, FragCode};
    }

    GLuint ShaderLoader::CreateProgram(const std::string& p_vertexShader, const std::string& p_fragmentShader) {

        const GLuint program = glCreateProgram();

        const GLuint vs = Compile(GL_VERTEX_SHADER, p_vertexShader);
        const GLuint fs = Compile(GL_FRAGMENT_SHADER, p_fragmentShader);

        if (!(vs && fs)) {
            throw std::runtime_error("Shader Error, Can not create program.");
        }

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);

        GLint ret_code;

        glGetProgramiv(program, GL_LINK_STATUS, &ret_code);

        if (!ret_code) {

            GLint info_len;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_len);

            char *info = new char[info_len];

            glGetProgramInfoLog(program, info_len, &info_len, info);

            aLog("Loader")->error("Linking Error: {}", info);

            glDeleteProgram(program);

            return 0;
        }

        glValidateProgram(program);
        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }

}