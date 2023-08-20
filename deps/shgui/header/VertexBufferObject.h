#pragma once

#include "Include.h"

namespace hgui
{
    namespace kernel
    {
        class VertexBufferObject
        {
        public:
            VertexBufferObject();
            ~VertexBufferObject();

            void bind();
            void unbind();
            void set_data(const void* data, int size, bool dynamic = false);
            void set_sub_data(const void* data, int size, int offset);

        private:
            GLuint m_id;
        };
    }
}

