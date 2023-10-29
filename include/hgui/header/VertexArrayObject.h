#pragma once

#include "Include.h"

namespace hgui::kernel
{
	class VertexArrayObject
	{
	public:
		VertexArrayObject();
		~VertexArrayObject();

		void bind() const;

		static void unbind();

	private:
		GLuint m_id;
	};
}
