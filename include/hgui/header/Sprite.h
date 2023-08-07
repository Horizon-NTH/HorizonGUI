#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Widget.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "WindowManager.h"

namespace hgui
{
	namespace kernel
	{
		class Sprite : public Widget
		{
		public:
			Sprite(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture, const size& size, const point& position, const color& color, float angularRoation);
			~Sprite();

			void draw() const override;

			void set_position(const point& newPosition) override;

		private:
			std::shared_ptr<Texture> m_texture;
			float m_angularRotation;
			glm::mat4 m_modelMatrix;

			void init_data();
		};
	}
}

