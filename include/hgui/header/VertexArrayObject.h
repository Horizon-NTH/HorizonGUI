#pragma once

#include "Include.h"

namespace hgui::kernel
{
	class VertexArrayObject
	{
	public:
		VertexArrayObject() noexcept;
		VertexArrayObject(const VertexArrayObject& vertexArrayObject) noexcept = delete;
		VertexArrayObject(VertexArrayObject&& vertexArrayObject) noexcept = delete;

		~VertexArrayObject() noexcept;

		VertexArrayObject& operator=(const VertexArrayObject& vertexArrayObject) noexcept = delete;
		VertexArrayObject& operator=(VertexArrayObject&& vertexArrayObject) noexcept = delete;

		void bind() const noexcept;
		void unbind() const noexcept;

	private:
		GLuint m_id;
	};
}