#pragma once

#include "Include.h"
#include "FrameBuffer.h"
#include "RenderBuffer.h"
#include "Texture.h"
#include "Shader.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"

namespace hgui
{
	namespace kernel
	{
		class Buffer
		{
		public:
			Buffer(const std::shared_ptr<Shader>& shader, const std::shared_ptr<kernel::Texture>& texture);

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

			void init_data();
		};
	}
}

