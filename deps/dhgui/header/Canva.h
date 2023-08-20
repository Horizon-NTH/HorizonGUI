#pragma once

#include "Include.h"
#include "Define.h"
#include "Maths.hpp"
#include "Widget.h"
#include "Drawer.h"

namespace hgui
{
	namespace kernel
	{
		class Canva : public Widget
		{
		public:
			Canva(const std::shared_ptr<Shader>& shader, const size& size, const point& position, const color& color, float angularRotation);

			void draw() const override;
			void set_position(const point& newPosition);
			const std::shared_ptr<kernel::Drawer>& get_drawer() const;

		private:
			glm::mat4 m_modelMatrix;
			float m_angularRoation;
			std::shared_ptr<kernel::Drawer> m_drawer;

			void init_data();
		};
	}
}