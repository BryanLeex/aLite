//
// Created by Bryan on 07/08/2024.
//

#include "Shader.h"


namespace Render::Resources {

    Shader::Shader(std::string p_path) {

        try {
            m_progID = Loaders::ShaderLoader::Create(p_path);
        } catch (std::runtime_error &error) {
            aLog("Shader")->error(error.what());
        }


    }

    Shader::~Shader() {

        Loaders::ShaderLoader::Destroy(m_progID);

    }

    uint32_t Shader::GetUniformLocation(const std::string &name) {

        if (m_addrLocationCatch.find(name) != m_addrLocationCatch.end())
            return m_addrLocationCatch[name];

        const int32_t addr = glGetUniformLocation(m_progID, name.c_str());

        if (addr == -1) {
            throw std::runtime_error("Can Not Find Varible: " + name);
        }

        m_addrLocationCatch.insert({name, addr});

        return addr;

    }

    void Shader::Bind() const {

        glUseProgram(m_progID);

    }

    void Shader::Unbind() const {

        glUseProgram(0);

    }

}