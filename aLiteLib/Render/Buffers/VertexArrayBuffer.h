//
// Created by Bryan on 07/08/2024.
//

#ifndef ALITE_VERTEXARRAYBUFFER_H
#define ALITE_VERTEXARRAYBUFFER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdexcept>

#include "Render/Buffers/VertexBuffer.h"
#include "Render/Buffers/Settings.h"

namespace Render::Buffers {

    class VertexArrayBuffer {

    public:

        VertexArrayBuffer();
        ~VertexArrayBuffer();

        void Bind() const;
        static void Unbind();

        [[nodiscard]]
        GLuint GetID() const;

        template<class T>
        void BindAttribute(
                uint32_t p_attribute,
                VertexBuffer<T> &p_vertexBuffer,
                Setting::EDataType p_type,
                uint64_t p_size,
                uint64_t p_stride,
                void *p_ptr
        ) const;

    private:

        GLuint m_bufferID;

    };

}

#include "VertexArrayBuffer.inl"

#endif //ALITE_VERTEXARRAYBUFFER_H
