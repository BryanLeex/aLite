//
// Created by Bryan on 07/08/2024.
//
#pragma once

#include "VertexBuffer.h"

namespace Render::Buffers {

    template<class T>
    inline VertexBuffer<T>::VertexBuffer(T *p_data, size_t p_size) : m_bufferID(0) {

        glGenBuffers(1, &m_bufferID);
        if (m_bufferID == 0) {
            throw std::runtime_error("Can Not Generate Buffer");
        }
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(p_size * sizeof(T)), p_data, GL_STATIC_DRAW);

    }

    template<class T>
    inline VertexBuffer<T>::VertexBuffer(std::vector<T> &p_data):
            VertexBuffer(p_data.data(), p_data.size()) {}

    template<class T>
    inline VertexBuffer<T>::~VertexBuffer() {

        glDeleteBuffers(1, &m_bufferID);

    }

    template<class T>
    inline void VertexBuffer<T>::Bind() const {

        glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);

    }

    template<class T>
    inline void VertexBuffer<T>::Unbind() const {

        glBindBuffer(GL_ARRAY_BUFFER, 0);

    }

    template<class T>
    GLuint VertexBuffer<T>::GetID() {
        return m_bufferID;
    }

}
