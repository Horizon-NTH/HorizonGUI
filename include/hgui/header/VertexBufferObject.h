#pragma once

#include "Include.h"

namespace hgui::kernel
{
	class VertexBufferObject
	{
	public:
		VertexBufferObject() noexcept;
		VertexBufferObject(const VertexBufferObject& vertexBufferObject) noexcept = delete;
		VertexBufferObject(VertexBufferObject&& vertexBufferObject) noexcept = delete;

		~VertexBufferObject() noexcept;

		VertexBufferObject& operator=(const VertexBufferObject& vertexBufferObject) noexcept = delete;
		VertexBufferObject& operator=(VertexBufferObject&& vertexBufferObject) noexcept = delete;

		void bind() const noexcept;
		void unbind() const noexcept;

		void set_data(const void* data, int size, bool dynamic = false) const noexcept;
		void set_sub_data(const void* data, int size, int offset) const noexcept;

	private:
		GLuint m_id;
	};
}