#pragma once

#include "Include.h"

namespace hgui::kernel
{
	class RenderBuffer
	{
	public:
		RenderBuffer() noexcept;
		RenderBuffer(const RenderBuffer& renderBuffer) noexcept = delete;
		RenderBuffer(RenderBuffer&& renderBuffer) noexcept = delete;

		~RenderBuffer() noexcept;

		RenderBuffer& operator=(const RenderBuffer& renderBuffer) noexcept = delete;
		RenderBuffer& operator=(RenderBuffer&& renderBuffer) noexcept = delete;

		void bind() const noexcept;
		void unbind() const noexcept;

		void create_depth_stencil() const;

		[[nodiscard]] GLuint get_id() const noexcept;

	private:
		GLuint m_id;
	};
}