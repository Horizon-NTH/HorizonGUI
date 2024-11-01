#pragma once

#include "Shape.h"

namespace hgui::kernel
{
	class Shader;
}

namespace hgui::kernel::shape
{
	class Triangle final : public Shape
	{
	public:
		Triangle(const point& firstVertex, const point& secondVertex, const point& thirdVertex, const color& color, bool fill, float thickness);
		~Triangle() override = default;

		Triangle(const Triangle& triangle) = default;
		Triangle(Triangle&& triangle) = default;

		Triangle& operator=(const Triangle& triangle) = default;
		Triangle& operator=(Triangle&& triangle) = default;

		void draw(const point& canvasPosition, const size& canvasSize) const override;

	private:
		inline static std::shared_ptr<Shader> m_shader{};
	};
}
