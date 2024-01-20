#pragma once

#include "Include.h"

namespace hgui::kernel
{
	class VertexBufferObject;
	class VertexArrayObject;
	class RenderBuffer;
	class FrameBuffer;
	class Shader;
	class Texture;

	class Buffer
	{
	public:
		Buffer(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture);
		Buffer(const Buffer& buffer) = delete;
		Buffer(Buffer&& buffer) = default;

		~Buffer() = default;

		Buffer& operator=(const Buffer& buffer) = delete;
		Buffer& operator=(Buffer&& buffer) = default;

		void bind() const;
		void unbind() const;
		void show() const;
		void clear() const;

	private:
		std::shared_ptr<Shader> m_shader;
		std::shared_ptr<FrameBuffer> m_frameBuffer;
		std::shared_ptr<RenderBuffer> m_renderBuffer;
		std::shared_ptr<Texture> m_texture;
		std::shared_ptr<VertexArrayObject> m_VAO;
		std::shared_ptr<VertexBufferObject> m_VBO;

		void init_data() const;
	};
}
