//
// Created by Bryan on 07/08/2024.
//

#include "VertexArrayBuffer.h"


namespace Render::Buffers {

    VertexArrayBuffer::VertexArrayBuffer(): m_bufferID(0) {

        glGenVertexArrays(1, &m_bufferID);
        if (m_bufferID == 0) {
            throw std::runtime_error("Can Not Generate VertexArrays");
        }
        glBindVertexArray(m_bufferID);

    }

    VertexArrayBuffer::~VertexArrayBuffer() {

        glDeleteBuffers(1, &m_bufferID);

    }

    void VertexArrayBuffer::Bind() const {

        glBindVertexArray(m_bufferID);

    }

    void VertexArrayBuffer::Unbind() {

        glBindVertexArray(0);

    }

    GLuint VertexArrayBuffer::GetID() const {
        return m_bufferID;
    }

}