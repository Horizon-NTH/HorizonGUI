#pragma once

#include "Coordinate.hpp"
#include "Tools.h"

namespace hgui::kernel
{
	namespace shape
	{
		class Shape;
	}

	class Canvas;

	class Drawer
	{
		friend class Canvas;

	public:
		Drawer(point position, size size);
		Drawer(const Drawer& drawer) = delete;
		Drawer(Drawer&& drawer) = default;

		~Drawer() = default;

		Drawer& operator=(const Drawer& drawer) = delete;
		Drawer& operator=(Drawer&& drawer) = default;

		const std::string& draw_rectangle(const point& topLeftVertex, const point& rightBottomVertex, const color& color, bool fill = true, float thickness = 10.0f, const std::string& id = get_unique_id()) const;
		const std::string& draw_triangle(const point& firstVertex, const point& secondVertex, const point& thirdVertex, const color& color, bool fill = true, float thickness = 10.0f, const std::string& id = get_unique_id()) const;
		const std::string& draw_circle(const point& centerPosition, float radius, const color& color, bool fill = true, float thickness = 10.0f, const std::string& id = get_unique_id()) const;
		const std::string& draw_line(const point& firstVertex, const point& secondVertex, const color& color, float thickness = 10.0f, const std::string& id = get_unique_id()) const;

		void draw() const;

		[[nodiscard]] const std::shared_ptr<std::map<std::string, std::shared_ptr<shape::Shape>>>& get_shapes() const;
		[[nodiscard]] std::pair<point, size> get_placement() const;

		void set_placement(const point& position, const size& size);

	private:
		point m_position;
		size m_size;
		std::shared_ptr<std::map<std::string, std::shared_ptr<shape::Shape>>> m_shapes;
		mutable std::vector<std::string> m_order;
	};
}
