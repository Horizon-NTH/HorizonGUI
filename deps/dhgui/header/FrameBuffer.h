#pragma once

#include "Include.h"
#include "Texture.h"
#include "RenderBuffer.h"

namespace hgui
{
	namespace kernel
	{
		class FrameBuffer
		{
		public:
			FrameBuffer();
			~FrameBuffer();

			void bind() const;
			void unbind() const;
			void clear();
			GLuint get_id() const;
			bool is_complete() const;
			void attach_texture(const std::shared_ptr<Texture>& texture);
			void attach_render_buffer(const std::shared_ptr<RenderBuffer>& renderBuffer);

		private:
			GLuint m_id;
		};
	}
}

