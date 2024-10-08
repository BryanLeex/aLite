//
// Created by Bryan on 07/08/2024.
//

#ifndef ALITE_SHADER_H
#define ALITE_SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <stdexcept>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Context/Device/Device.h"

#include "Render/Resources/Loaders/ShaderLoader.h"

namespace Render::Resources {

    class Shader {

    public:

        Shader(std::string p_path);
        ~Shader();

        void Bind() const;

        void Unbind() const;

        uint32_t GetUniformLocation(const std::string &name);

        template<typename T>
        void SetValue(std::string name, T data) {

            aLog("Shader")->debug("Type: {}", typeid(T).name());

            try{

                if constexpr (std::is_integral_v<T>) {
                    // Deal Integral

                    glUniform1i(GetUniformLocation(name), data);

                }
                else if constexpr (std::is_floating_point_v<T>) {
                    // Deal Float point number

                    glUniform1f(GetUniformLocation(name), data);

                }

                // Deal Vector.
                else if constexpr (std::is_same_v<T, glm::vec1>) {

                    glUniform1f(GetUniformLocation(name), data.x);

                }
                else if constexpr (std::is_same_v<T, glm::vec2>) {

                    glUniform2f(GetUniformLocation(name), data.x, data.y);

                }
                else if constexpr (std::is_same_v<T, glm::vec3>) {

                    glUniform3f(GetUniformLocation(name), data.x, data.y, data.z);

                }
                else if constexpr (std::is_same_v<T, glm::vec4>) {

                    glUniform4f(GetUniformLocation(name), data.x, data.y, data.z, data.w);

                }

                // Deal Matrix.
                else if constexpr (std::is_same_v<T, glm::mat2>) {

                    glUniformMatrix2fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(data));

                }
                else if constexpr (std::is_same_v<T, glm::mat3>) {

                    glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(data));

                }
                else if constexpr (std::is_same_v<T, glm::mat4>) {

                    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(data));

                }
                else {

                    throw std::runtime_error("Unknown Type of data: " + std::string(typeid(T).name()));

                }

            } catch (std::exception &exception) {

                aLog("Shader")->error(exception.what());

            }

        }

    private:

        std::string m_sourcePath;
        uint32_t m_progID;

        std::unordered_map <std::string, GLuint> m_addrLocationCatch;

    };

}

#endif //ALITE_SHADER_H
