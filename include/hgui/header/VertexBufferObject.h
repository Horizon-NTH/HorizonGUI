#pragma once

#include "Include.h"

namespace hgui::kernel
{
	class VertexBufferObject
	{
	public:
		VertexBufferObject();
		~VertexBufferObject();

		void bind() const;

		static void unbind();
		void set_data(const void* data, int size, bool dynamic = false) const;
		void set_sub_data(const void* data, int size, int offset) const;

	private:
		GLuint m_id;
	};
}
