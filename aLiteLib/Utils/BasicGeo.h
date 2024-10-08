//
// Created by Bryan on 11/08/2024.
//

#ifndef ALITE_BASICGEO_H
#define ALITE_BASICGEO_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Render/Buffers/VertexBuffer.h"
#include "Render/Buffers/VertexArrayBuffer.h"

namespace Utils {

    class BasicGeo {

    public:

        typedef float_t Data_t;

        BasicGeo() {

            std::vector<Data_t> vertices = {
                    1.f, 1.f, 0.0f, 1.f, 1.f,
                    1.f, -1.f, 0.0f, 1.f, 0.f,
                    -1.f, 1.f, 0.0f, 0.f, 1.f,
                    1.f, -1.f, 0.0f, 1.f, 0.f,
                    -1.f, 1.f, 0.0f, 0.f, 1.f,
                    -1.f, -1.f, 0.0f, 0.f, 0.f
            };

            m_vertexBuffer = new Render::Buffers::VertexBuffer(vertices);
            m_vertexArrayBuffer = new Render::Buffers::VertexArrayBuffer();

            m_vertexArrayBuffer->BindAttribute(0, *m_vertexBuffer,
                                               Render::Setting::EDataType::FLOAT, 3,
                                               5 * sizeof(float), (void *)(0 * sizeof(float)));

            m_vertexArrayBuffer->BindAttribute(1, *m_vertexBuffer,
                                               Render::Setting::EDataType::FLOAT, 2,
                                               5 * sizeof(float), (void *)(3 * sizeof(float)));

        }

        ~BasicGeo() {

            delete m_vertexBuffer;
            delete m_vertexArrayBuffer;

        }


        void Draw() {

            m_vertexArrayBuffer->Bind();
            glDrawArrays(GL_TRIANGLES, 0, 6);

        }

    private:

        Render::Buffers::VertexArrayBuffer* m_vertexArrayBuffer;
        Render::Buffers::VertexBuffer<Data_t>* m_vertexBuffer;

        glm::mat4 m_model;

    };

} // Utils

#endif //ALITE_BASICGEO_H
