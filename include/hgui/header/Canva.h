#pragma once

#include "Include.h"
#include "Widget.h"
#include "WindowManager.h"
#include "Drawer.h"
#include "ResourceManager.h"

namespace hgui
{
	namespace kernel
	{
		class Canva : public Widget
		{
		public:
			Canva(const std::shared_ptr<Shader>& shader, glm::vec2 size, glm::vec2 position, glm::vec3 color, float angularRotation);

			void draw() const override;
			void set_position(glm::vec2 newPosition);
			const std::shared_ptr<kernel::Drawer>& get_drawer() const;

		private:
			glm::mat4 m_modelMatrix;
			float m_angularRoation;
			std::shared_ptr<kernel::Drawer> m_drawer;

			void init_data();
		};
	}
}