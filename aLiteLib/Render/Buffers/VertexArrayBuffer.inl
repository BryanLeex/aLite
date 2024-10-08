//
// Created by Bryan on 07/08/2024.
//

#include "VertexArrayBuffer.h"

#pragma once

namespace Render::Buffers {

    template<class T>
    void VertexArrayBuffer::BindAttribute(
            uint32_t p_attribute,
            VertexBuffer<T> &p_vertexBuffer,
            Setting::EDataType p_type,
            uint64_t p_size,
            uint64_t p_stride,
            void *p_ptr
    ) const {

        Bind();                 // bind vertex array
        p_vertexBuffer.Bind();  // bind vertex data

        glEnableVertexAttribArray(p_attribute);
        glVertexAttribPointer(
                static_cast<GLuint>(p_attribute),
                static_cast<GLint>(p_size),
                static_cast<GLenum>(p_type),
                GL_FALSE,
                static_cast<GLsizei>(p_stride),
                p_ptr);

    }

}