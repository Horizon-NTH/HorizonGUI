#pragma once

#include "Shape.h"

namespace hgui::kernel
{
	class Shader;
}

namespace hgui::kernel::shape
{
	class Circle final : public Shape
	{
	public:
		Circle(const point& centerPosition, float radius, const color& color, bool fill, float thickness);
		~Circle() override = default;

		Circle(const Circle& circle) = delete;
		Circle(Circle&& circle) = delete;

		Circle& operator=(const Circle& circle) = delete;
		Circle& operator=(Circle&& circle) = delete;

		void draw(const point& canvasPosition, const size& canvasSize) const override;

	private:
		inline static std::shared_ptr<Shader> m_shader{};
	};
}
