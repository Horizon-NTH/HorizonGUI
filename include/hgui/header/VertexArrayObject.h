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

		void unbind() const;

	private:
		GLuint m_id;
	};
}
