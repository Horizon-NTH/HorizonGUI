#include "../include/PyShape.h"

void PyShape::draw(const hgui::point& canvasPosition, const hgui::size& canvasSize) const
{
	PYBIND11_OVERRIDE_PURE(void, Shape, draw, canvasPosition, canvasSize);
}

void init_shapes(const py::module& kernel)
{
	using shape = hgui::kernel::shape::Shape;
	py::class_<shape, PyShape, std::shared_ptr<shape>>(kernel, "Shape",
				"A base class used to create different geometric shapes.")
			.def(py::init<bool, float, const hgui::color&, hgui::kernel::shape::ShapeData>(), "fill"_a, "thickness"_a, "color"_a, "data"_a,
				"Constructs a Shape object with the specified fill mode, thickness, color and ShapeData.")
			.def("draw", &shape::draw, "canvas_position"_a, "canvas_size"_a,
				"A pure virtual function that must be implemented by derived shape classes. It defines how the shape is rendered and need the position and size of the canvas area.")
			.def_property_readonly("thickness", &shape::get_thickness,
				"Retrieves the thickness of the shape's lines.")
			.def("is_fill", &shape::is_fill,
				"Checks whether the shape is filled or not.")
			.def_property("color", py::cpp_function(&shape::get_color, py::return_value_policy::reference_internal), py::cpp_function(&shape::set_color),
				"Retrieves the color of the shape.")
			.def_property_readonly("data", &shape::get_data,
				"Retrieves the ShapeData of the shape.");

	using circle = hgui::kernel::shape::Circle;
	py::class_<circle, shape, std::shared_ptr<circle>>(kernel, "Circle",
				"A circle shape.")
			.def(py::init<const hgui::point&, float, const hgui::color&, bool, float>(), "center_position"_a, "radius"_a, "color"_a, "fill"_a, "thickness"_a,
				"Constructs a Circle object with the specified center position, radius, color, fill mode, and thickness.");

	using rectangle = hgui::kernel::shape::Rectangle;
	py::class_<rectangle, shape, std::shared_ptr<rectangle>>(kernel, "Rectangle",
				"A rectangle shape.")
			.def(py::init<const hgui::point&, const hgui::point&, const hgui::color&, bool, float>(), "top_left_vertex"_a, "bottom_right_vertex"_a, "color"_a, "fill"_a, "thickness"_a,
				"Constructs a Rectangle object with the specified top-left and bottom-right vertices, color, fill mode, and thickness.");

	using line = hgui::kernel::shape::StraightLine;
	py::class_<line, shape, std::shared_ptr<line>>(kernel, "StraightLine",
				"A straight line.")
			.def(py::init<const hgui::point&, const hgui::point&, const hgui::color&, float>(), "first_vertex"_a, "second_vertex"_a, "color"_a, "thickness"_a,
				"Constructs a Straight Line object with the specified first and second vertices, color, and thickness.");

	using triangle = hgui::kernel::shape::Triangle;
	py::class_<triangle, shape, std::shared_ptr<triangle>>(kernel, "Triangle",
				"A triangle shape.")
			.def(py::init<const hgui::point&, const hgui::point&, const hgui::point&, const hgui::color&, bool, float>(), "first_vertex"_a, "second_vertex"_a, "third_vertex"_a, "color"_a, "fill"_a, "thickness"_a,
				"Constructs a Triangle object with the specified vertices, color, fill mode, and thickness.");

	using drawer = hgui::kernel::Drawer;
	py::class_<drawer, std::shared_ptr<drawer>>(kernel, "Drawer",
				"The Drawer class provides a versatile tool for drawing shapes and lines in a graphical application.")
			.def(py::init<hgui::point, hgui::size>(), "position"_a, "size"_a,
				"Constructs a Drawer object with the position and size of the drawing area.")
			.def("draw_rectangle", [](const drawer& self, const hgui::point& topLeftVertex, const hgui::point& rightBottomVertex, const hgui::color& color, const bool fill, const float thickness, const std::string& id)
					{
						return self.draw_rectangle(topLeftVertex, rightBottomVertex, color, fill, thickness, id.empty() ? hgui::get_unique_id() : id);
					}, "top_left_vertex"_a, "right_bottom_vertex"_a, "color"_a, "fill"_a = true, "thickness"_a = 10.f, "id"_a = "",
				"Draws a rectangle with the specified vertices, color, fill mode, line thickness, and an optianal id.")
			.def("draw_triangle", [](const drawer& self, const hgui::point& firstVertex, const hgui::point& secondVertex, const hgui::point& thirdVertex, const hgui::color& color, const bool fill, const float thickness, const std::string& id)
					{
						return self.draw_triangle(firstVertex, secondVertex, thirdVertex, color, fill, thickness, id.empty() ? hgui::get_unique_id() : id);
					}, "first_vertex"_a, "second_vertex"_a, "third_vertex"_a, "color"_a, "fill"_a = true, "thickness"_a = 10.f, "id"_a = "",
				"Draws a triangle with the specified vertices, color, fill mode, line thickness, and an optianal id.")
			.def("draw_circle", [](const drawer& self, const hgui::point& center, const float radius, const hgui::color& color, const bool fill, const float thickness, const std::string& id)
					{
						return self.draw_circle(center, radius, color, fill, thickness, id.empty() ? hgui::get_unique_id() : id);
					}, "centerPosition"_a, "radius"_a, "color"_a, "fill"_a = true, "thickness"_a = 10.f, "id"_a = "",
				"Draws a circle with the specified center, radius, color, fill mode, line thickness, and an optianal id.")
			.def("draw_line", [](const drawer& self, const hgui::point& firstVertex, const hgui::point& secondVertex, const hgui::color& color, const float thickness, const std::string& id)
					{
						return self.draw_line(firstVertex, secondVertex, color, thickness, id.empty() ? hgui::get_unique_id() : id);
					},
				"first_vertex"_a, "second_vertex"_a, "color"_a, "thickness"_a = 10.f, "id"_a = "",
				"Draws a line between two specified vertices with the given color, thickness, and an optianal id."
			)
			.def_property("shapes", py::cpp_function([](const drawer& self) { return *self.get_shapes(); }, py::return_value_policy::reference_internal), py::cpp_function([](const drawer& self, const std::map<std::string, std::shared_ptr<shape>>& shapes)
					{
						*self.get_shapes() = shapes;
					}),
				"Property to access the collection of shapes drawn with the Drawer.")
			.def_property("placement", py::cpp_function(&drawer::get_placement, py::return_value_policy::copy), py::cpp_function([](drawer& self, const std::pair<hgui::point, hgui::size>& placement)
					{
						self.set_placement(placement.first, placement.second);
					}),
				"Property to access the placement of the Drawer.")
			.def("draw", &drawer::draw,
				"Renders all the shapes created with the Drawer.");
}
