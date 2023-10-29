#pragma once

#include "Include.h"

namespace hgui::kernel
{
	class RenderBuffer
	{
	public:
		RenderBuffer();
		~RenderBuffer();

		void bind() const;

		static void unbind();
		void create_depth_stencil() const;

		[[nodiscard]] GLuint get_id() const;

	private:
		GLuint m_id;
	};
}
