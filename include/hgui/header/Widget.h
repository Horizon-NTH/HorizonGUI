#pragma once

#include "Include.h"
#include "Shader.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"

namespace hgui
{
	namespace kernel
	{
		class Shader;

		class Widget
		{
		public:
			Widget(const std::shared_ptr<Shader>& shader, glm::vec2 size, glm::vec2 position, glm::vec3 color);
			~Widget();

			glm::vec2 get_position() const;
			virtual void set_position(glm::vec2 newPosition);

			glm::vec2 get_size() const;

			virtual void draw() const = 0;

		protected:
			std::shared_ptr<Shader> m_shader;
			std::shared_ptr<VertexArrayObject> m_VAO;
			std::shared_ptr<VertexBufferObject> m_VBO;
			glm::vec2 m_size;
			glm::vec2 m_position;
			glm::vec3 m_color;
		};
	}
}

