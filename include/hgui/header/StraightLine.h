#pragma once

#include "Shape.h"

namespace hgui::kernel
{
	class Shader;
}

namespace hgui::kernel::shape
{
	class StraightLine final : public Shape
	{
	public:
		StraightLine(const point& firstVertex, const point& secondVertex, const color& color, float thickness);
		~StraightLine() override = default;

		StraightLine(const StraightLine& straightLine) = default;
		StraightLine(StraightLine&& straightLine) = default;

		StraightLine& operator=(const StraightLine& straightLine) = default;
		StraightLine& operator=(StraightLine&& straightLine) = default;

		void draw(const point& canvasPosition, const size& canvasSize) const override;

	private:
		inline static std::shared_ptr<Shader> m_shader{};
	};
}
