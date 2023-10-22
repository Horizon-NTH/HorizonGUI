#pragma once

#include "Include.h"

namespace hgui
{
    namespace kernel
    {
        class VertexArrayObject
        {
        public:
            VertexArrayObject();
            ~VertexArrayObject();

            void bind();
            void unbind();

        private:
            GLuint m_id;
        };
    }
}

