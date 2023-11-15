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

		void draw(const std::pair<std::shared_ptr<Shader>, std::shared_ptr<Shader>>& shaders) const override;
	};
}
