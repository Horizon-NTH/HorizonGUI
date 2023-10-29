#pragma once

#include "Include.h"
#include "Texture.h"
#include "RenderBuffer.h"

namespace hgui::kernel
{
	class FrameBuffer
	{
	public:
		FrameBuffer();
		~FrameBuffer();

		void bind() const;

		static void unbind();
		void clear() const;
		[[nodiscard]] GLuint get_id() const;
		[[nodiscard]] bool is_complete() const;
		void attach_texture(const std::shared_ptr<Texture>& texture) const;
		void attach_render_buffer(const std::shared_ptr<RenderBuffer>& renderBuffer) const;

	private:
		GLuint m_id;
	};
}
