#pragma once

#include "Include.h"
#include "Widget.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Shader.h"
#include "RenderManager.h"
#include "TextArea.h"


namespace hgui
{
	namespace kernel
	{
		enum ButtonState
		{
			NORMAL = 0,
			HOVER = 1,
			PRESS = 2
		};

		class TextArea;

		class Button : public Widget
		{
		public:
			Button(std::function<void()> function, const std::shared_ptr<Shader>& shader, glm::vec2 size, glm::vec2 position, const std::shared_ptr<TextArea>& text, glm::vec3 color, float angularRotation, float cornerAngularRadius, std::shared_ptr<Texture> = nullptr);
			~Button();

			void press() const;
			void draw() const override;

			void set_position(glm::vec2 newPosition) override;
			void set_state(ButtonState state);
			void set_textures(std::shared_ptr<Texture> texture);

		protected:
			ButtonState m_state;
			std::function<void()> m_function;
			std::shared_ptr<Texture> m_texture;
			std::shared_ptr<TextArea> m_text;
			float m_cornerAngularRadius;
			float m_angularRoation;
			glm::mat4 m_modelMatrix;

			void init_data();
		};
	}
}