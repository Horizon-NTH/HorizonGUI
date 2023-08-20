#pragma once

#include "Include.h"

namespace hgui
{
	namespace kernel
	{
		class RenderBuffer
		{
		public:
			RenderBuffer();
			~RenderBuffer();

			void bind();
			void unbind();

			void create_depth_stencil();
			GLuint get_id() const;

		private:
			GLuint m_id;
		};
	}
}

