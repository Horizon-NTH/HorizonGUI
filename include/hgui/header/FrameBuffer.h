#pragma once

#include "Include.h"
#include "Texture.h"
#include "RenderBuffer.h"

namespace hgui::kernel
{
	class FrameBuffer
	{
	public:
		FrameBuffer() noexcept;
		FrameBuffer(const FrameBuffer& frameBuffer) noexcept = delete;
		FrameBuffer(FrameBuffer&& frameBuffer) noexcept = delete;
		
		~FrameBuffer() noexcept;
		
		FrameBuffer& operator=(const FrameBuffer& frameBuffer) noexcept = delete;
		FrameBuffer& operator=(FrameBuffer&& frameBuffer) noexcept = delete;

		void bind() const noexcept;

		static void unbind() noexcept;
		void clear() const noexcept;
		[[nodiscard]] GLuint get_id() const noexcept;
		[[nodiscard]] bool is_complete() const noexcept;
		void attach_texture(const std::shared_ptr<Texture>& texture) const noexcept;
		void attach_render_buffer(const std::shared_ptr<RenderBuffer>& renderBuffer) const noexcept;

	private:
		GLuint m_id;
	};
}