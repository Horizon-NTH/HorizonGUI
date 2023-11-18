#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Shape.h"

namespace hgui::kernel::shape
{
	class Triangle final : public Shape
	{
	public:
		Triangle(const point& firstVertex, const point& secondVertex, const point& thirdVertex, const color& color, bool fill,
		         float thickness);
		~Triangle() override = default;

		Triangle(const Triangle& triangle) = default;
		Triangle(Triangle&& triangle) = default;

		Triangle& operator=(const Triangle& triangle) = default;
		Triangle& operator=(Triangle&& triangle) = default;

		void draw(const hgui::point& canvasPosition, const hgui::size& canvasSize) const override;

	private:
		static std::shared_ptr<Shader> m_shader;
	};
}
