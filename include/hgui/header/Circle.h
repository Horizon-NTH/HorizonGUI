#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Shape.h"

namespace hgui::kernel::shape
{
	class Circle final : public Shape
	{
	public:
		Circle(const point& centerPosition, float radius, const color& color, bool fill, float thickness);
		~Circle() override = default;

		Circle(const Circle& circle) = default;
		Circle(Circle&& circle) = default;

		Circle& operator=(const Circle& circle) = default;
		Circle& operator=(Circle&& circle) = default;

		void draw(const point& canvasPosition, const size& canvasSize, float canvasRotation) const override;

	private:
		static std::shared_ptr<Shader> m_shader;
	};
}
