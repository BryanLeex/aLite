//
// Created by Bryan on 07/08/2024.
//

#ifndef ALITE_VERTEXBUFFER_H
#define ALITE_VERTEXBUFFER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <stdexcept>

namespace Render::Buffers {

    template<class T>
    class VertexBuffer {

    public:

        VertexBuffer(T* p_data, size_t p_size);
        explicit VertexBuffer(std::vector<T> &p_data);

        ~VertexBuffer();

        void Bind() const;
        void Unbind() const;

        [[nodiscard]] GLuint GetID();

    private:
        GLuint m_bufferID;

    };
}

#include "VertexBuffer.inl"

#endif //ALITE_VERTEXBUFFER_H
