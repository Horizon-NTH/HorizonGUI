#include "../include/PyCoordinate.h"

void PyCoordinate::update()
{
	PYBIND11_OVERRIDE(void, Coordinate, update,);
}

void init_em(const py::module& hgui)
{
	using em = hgui::kernel::EM<float>;
	py::class_<em>(hgui, "em",
				"A class representing a responsive design units, based on a reference size.")
			.def(py::init(),
				"Default constructor for the em.")
			.def(py::init([](const float value) { return new em(value / 100.f); }), "value"_a,
				"Constructs the em with a value.")
			.def(py::init<const em&>(), "em"_a,
				"Copy constructor for the em.")
			.def("__copy__", [](const em& self) { return em(self); },
				"Copy constructor for the em.")
			.def("__deepcopy__", [](const em& self, py::dict) { return em(self); }, "memo"_a,
				"Deep copy constructor for the em.")
			.def(py::self + py::self, "em"_a,
				"Addition operator for ems.")
			.def(py::self += py::self, "em"_a,
				"In-place addition operator for ems.")
			.def(py::self - py::self, "em"_a,
				"Subtraction operator for ems.")
			.def(py::self -= py::self, "em"_a,
				"In-place subtraction operator for ems.")
			.def(py::self * py::self, "em"_a,
				"Multiplication operator for ems.")
			.def(py::self *= py::self, "em"_a,
				"In-place multiplicaiton operator for ems.")
			.def(py::self / py::self, "em"_a,
				"Division operator for ems.")
			.def(py::self /= py::self, "em"_a,
				"In-place division operator for ems.")
			.def(py::self + float(), "scalar"_a,
				"Addition operator for em and sclar.")
			.def(float() + py::self, "scalar"_a,
				"Addition operator (reversed) for em and sclar.")
			.def(py::self += float(), "scalar"_a,
				"In-place addition operator for em and scalar.")
			.def(py::self - float(), "scalar"_a,
				"Subtraction operator for em and scalar.")
			.def(float() - py::self, "scalar"_a,
				"Subtraction operator (reversed) for em and scalar.")
			.def(py::self -= float(), "scalar"_a,
				"In-place subtraction operator for em and scalar.")
			.def(py::self * float(), "scalar"_a,
				"Multiplication operator for em and scalar.")
			.def(float() * py::self, "scalar"_a,
				"Multiplication operator (reversed) for em and scalar.")
			.def(py::self *= float(), "scalar"_a,
				"In-place multiplicaiton operator for em and scalar.")
			.def(py::self / float(), "scalar"_a,
				"Division operator for em and scalar.")
			.def(py::self /= float(), "scalar"_a,
				"In-place division operator for em and scalar.")
			.def(-py::self,
				"Negation operator for ems.")
			.def("__str__", [](const em& self)
					{
						std::stringstream ss;
						ss << self;
						return ss.str();
					},
				"String representation of the em.")
			.def("get_width_value", &em::get_width_value,
				"Returns the em value relative to the width of the reference size.")
			.def("get_height_value", &em::get_height_value,
				"Returns the EM value relative to the height of the reference size.")
			.def_property("value", py::cpp_function(&em::get_base_value, py::return_value_policy::reference_internal), py::cpp_function(&em::set_base_value),
				"Property to access the base value of the em.")
			.def_property("reference", py::cpp_function(&em::get_reference, py::return_value_policy::reference_internal), py::cpp_function(&em::set_reference),
				"Property to access the reference of the em.");
}

void init_coordinate(const py::module& hgui)
{
	init_em(hgui);

	// Coordinate
	using coordinate = hgui::kernel::Coordinate<float>;
	using em = hgui::kernel::EM<float>;
	py::class_<coordinate, PyCoordinate>(hgui, "coordinate",
				"A generic class representing a used to represents coordinates in the application.")
			.def(py::init(),
				"Default constructor for the coordinate.")
			.def(py::init<const PyCoordinate&>(), "coordinate"_a,
				"Copy constructor for the coordinate.")
			.def(py::init<float>(), "value"_a,
				"Constructs the coordinate while initializing both coordinate with the same value.")
			.def(py::init<const em&>(), "em"_a,
				"Constructs the coordinate while initializing both coordinate with the same em.")
			.def(py::init<float, float>(), "x"_a, "y"_a,
				"Constructs the coordinate with the specified x and y as values.")
			.def(py::init<float, const em&>(), "x"_a, "y"_a,
				"Constructs the coordinate with the specified x as a value and y as an em.")
			.def(py::init<const em&, float>(), "x"_a, "y"_a,
				"Constructs the coordinate with the specified x as an em and y as a value.")
			.def(py::init<const em&, const em&>(), "x"_a, "y"_a,
				"Constructs the coordinate with the specified x and y as ems.")
			.def(py::init<const std::pair<em, em>&>(), "coordinate"_a,
				"Constructs the coordinate from a tuple of two ems.")
			.def(py::init([](const std::pair<float, float>& coord) { return new coordinate(coord.first, coord.second); }), "coordinate"_a,
				"Constructs the coordinate from a tuple of two values.")
			.def(py::init([](const std::pair<em, float>& coord) { return new coordinate(coord.first, coord.second); }), "coordinate"_a,
				"Constructs the coordinate from a tuple of an em and a value.")
			.def(py::init([](const std::pair<float, em>& coord) { return new coordinate(coord.first, coord.second); }), "coordinate"_a,
				"Constructs the coordinate from a tuple of an em and a value (reversed).")
			.def(py::init<const std::array<em, 2>&>(), "coordinate"_a,
				"Constructs the coordinate from a list of two ems.")
			.def(py::init([](const std::array<float, 2>& coord) { return new coordinate(coord[0], coord[1]); }), "coordinate"_a,
				"Constructs the coordinate from a list of two values.")
			.def(py::init<const hgui::kernel::Vector<float, 2>&>(), "coordinate"_a,
				"Constructs the coordinate from a vector.")
			.def(py::init<const hgui::kernel::GLSLvec2<float>&>(), "coordinate"_a,
				"Constructs the coordinate from a glsl vec2.")
			.def("__copy__", [](const coordinate& self) { return coordinate(self); },
				"Copy constructor for the coordinate.")
			.def("__deepcopy__", [](const coordinate& self, py::dict) { return coordinate(self); }, "memo"_a,
				"Deep copy constructor for the coordinate.")
			.def(py::self + py::self, "coordinate"_a,
				"Addition operator for coordinates.")
			.def(py::self + hgui::kernel::GLSLvec2<float>(), "vector"_a,
				"Addition operator for coordinates and glsl vec2.")
			.def(hgui::kernel::GLSLvec2<float>() + py::self, "vector"_a,
				"Addition operator (reversed) for coordinates and glsl vec2.")
			.def(py::self += py::self, "coordinate"_a,
				"In-place addition operator for coordinates.")
			.def(py::self += hgui::kernel::GLSLvec2<float>(), "vector"_a,
				"In-place addition operator for coordinates and glsl vec2.")
			.def(py::self - py::self, "coordinate"_a,
				"Subtraction operator for coordinates.")
			.def(py::self - hgui::kernel::GLSLvec2<float>(), "coordinate"_a,
				"Subtraction operator for coordinates and glsl vec2.")
			.def(hgui::kernel::GLSLvec2<float>() - py::self, "coordinate"_a,
				"Subtraction operator (reversed) for coordinates and glsl vec2.")
			.def(py::self -= py::self, "coordinate"_a,
				"In-place subtraction operator for coordinates.")
			.def(py::self -= hgui::kernel::GLSLvec2<float>(), "coordinate"_a,
				"In-place subtraction operator for coordinates and glsl vec2.")
			.def(py::self * float(), "scalar"_a,
				"Multiplication operator for coordinates with a scalar.")
			.def(float() * py::self, "scalar"_a,
				"Multiplication operator (reversed) for coordinates with a scalar.")
			.def(py::self *= float(), "scalar"_a,
				"In-place multiplicaiton operator for coordinates with a scalar.")
			.def(py::self / float(), "scalar"_a,
				"Division operator for coordinates with a scalar.")
			.def(py::self /= float(), "scalar"_a,
				"In-place division operator for coordinates with a scalar.")
			.def(-py::self,
				"Negation operator for coordinates.")
			.def("__str__", [](const coordinate& self)
					{
						std::stringstream ss;
						ss << self;
						return ss.str();
					},
				"String representation of the coordinate.")
			.def("set_reference", &coordinate::set_reference,
				"Set the reference of the coordinate.")
			.def("undo_responsivness", &coordinate::undo_responsivness,
				"Disable all the added responsiveness implemented thus far to improve efficiency.")
			.def("update", &coordinate::update,
				"Used to update coordinates so that they can be recalculated in the event of a change, for example in the size of the window, according to the values set with ems.")
			.def_property("first", py::cpp_function(&coordinate::get_first_coord, py::return_value_policy::reference_internal), py::cpp_function(&coordinate::set_first_coord),
				"Property to access the first component (type: em) of the coordinate.")
			.def_property("second", py::cpp_function(&coordinate::get_second_coord, py::return_value_policy::reference_internal), py::cpp_function(&coordinate::set_second_coord),
				"Property to access the second component (type: em) of the coordinate.");

	// Point
	using point = hgui::kernel::Point<float>;
	py::class_<point, coordinate>(hgui, "point", py::is_final(),
				"A generic class representing a used to represents points in the application.")
			.def(py::init(),
				"Default constructor for the point.")
			.def(py::init<const point&>(), "point"_a,
				"Copy constructor for the point.")
			.def(py::init<const coordinate&>(), "coordinate"_a,
				"Copy constructor for the point from the base class.")
			.def(py::init<float>(), "value"_a,
				"Constructs the point while initializing both coordinate with the same value.")
			.def(py::init<const em&>(), "em"_a,
				"Constructs the point while initializing both coordinate with the same em.")
			.def(py::init<float, float>(), "x"_a, "y"_a,
				"Constructs the point with the specified x and y as values.")
			.def(py::init<float, const em&>(), "x"_a, "y"_a,
				"Constructs the point with the specified x as a value and y as an em.")
			.def(py::init<const em&, float>(), "x"_a, "y"_a,
				"Constructs the point with the specified x as an em and y as a value.")
			.def(py::init<const em&, const em&>(), "x"_a, "y"_a,
				"Constructs the point with the specified x and y as ems.")
			.def(py::init([](const std::pair<em, em>& coord) { return new point(coordinate(coord.first, coord.second)); }), "point"_a,
				"Constructs the point from a tuple of two ems.")
			.def(py::init([](const std::pair<float, float>& coord) { return new point(coord.first, coord.second); }), "point"_a,
				"Constructs the point from a tuple of two values.")
			.def(py::init([](const std::pair<em, float>& coord) { return new point(coord.first, coord.second); }), "point"_a,
				"Constructs the point from a tuple of an em and a value.")
			.def(py::init([](const std::pair<float, em>& coord) { return new point(coord.first, coord.second); }), "point"_a,
				"Constructs the point from a tuple of an em and a value (reversed).")
			.def(py::init([](const std::array<em, 2>& coord) { return new point(coord[0], coord[1]); }), "point"_a,
				"Constructs the point from a list of two ems.")
			.def(py::init([](const std::array<float, 2>& coord) { return new point(coord[0], coord[1]); }), "point"_a,
				"Constructs the point from a list of two values.")
			.def(py::init<const hgui::kernel::Vector<float, 2>&>(), "point"_a,
				"Constructs the point from a vector.")
			.def(py::init<const hgui::kernel::GLSLvec2<float>&>(), "point"_a,
				"Constructs the point from a glsl vec2.")
			.def("__copy__", [](const point& self) { return point(self); },
				"Copy constructor for the point.")
			.def("__deepcopy__", [](const point& self, py::dict) { return point(self); }, "memo"_a,
				"Deep copy constructor for the point.")
			.def_static("is_in_rectangle", &point::is_in_rectangle, "A"_a, "B"_a, "D"_a, "point"_a,
				"Checks if a point is inside a rectangle defined by points A, B, and D.")
			.def_static("rotate", &point::rotate, "point"_a, "center"_a, "theta"_a,
				"Rotates a point around a center by a given angle (theta).")
			.def_static("normalize", &point::normalize, "point"_a,
				"Returns the normalized vector of the given point.")
			.def_static("distance", &point::distance, "point1"_a, "point2"_a,
				"Calculates the distance between two points.")
			.def_static("dot", &point::dot, "point1"_a, "point2"_a,
				"Calculates the dot product of two points.")
			.def("__add__", [](const point& self, const point& other) { return point(self + other); }, "point"_a,
				"Addition operator for points.")
			.def(py::self + coordinate(), "coordinate"_a,
				"Addition operator for points and coordinates.")
			.def("__add__", [](const point& self, const hgui::kernel::GLSLvec2<float>& vec) { return point(self + vec); }, "vector"_a,
				"Addition operator for points and glsl vec2.")
			.def("__radd__", [](const hgui::kernel::GLSLvec2<float>& vec, const point& self) { return point(vec + self); }, "vector"_a,
				"Addition operator (reversed) for points and glsl vec2.")
			.def(coordinate() + py::self, "coordinate"_a,
				"Addition operator (reversed) for points and coordinates.")
			.def("__iadd__", [](point& self, const point& other) { return point(self += other); }, "point"_a,
				"In-place addition operator for points.")
			.def(py::self += coordinate(), "coordinate"_a,
				"In-place addition operator for points and coordinates.")
			.def("__iadd__", [](point& self, const hgui::kernel::GLSLvec2<float>& vec) { return point(self += vec); }, "vector"_a,
				"In-place addition operator for points and glsl vec2.")
			.def("__sub__", [](const point& self, const point& other) { return point(self - other); }, "point"_a,
				"Subtraction operator for points.")
			.def(py::self - coordinate(), "coordinate"_a,
				"Subtraction operator for points and coordinates.")
			.def("__sub__", [](const point& self, const hgui::kernel::GLSLvec2<float>& vec) { return point(self - vec); }, "point"_a,
				"Subtraction operator for points and glsl vec2.")
			.def("__rsub__", [](const hgui::kernel::GLSLvec2<float>& vec, const point& self) { return point(vec - self); }, "point"_a,
				"Subtraction operator (reversed) for points and glsl vec2.")
			.def(coordinate() - py::self, "coordinate"_a,
				"Subtraction operator (reversed) for points and coordinates.")
			.def("__isub__", [](point& self, const point& other) { return point(self -= other); }, "point"_a,
				"In-place subtraction operator for points.")
			.def(py::self -= coordinate(), "coordinate"_a,
				"In-place subtraction operator for points and coordinates.")
			.def("__isub__", [](point& self, const hgui::kernel::GLSLvec2<float>& vec) { return point(self -= vec); }, "point"_a,
				"In-place subtraction operator for points and glsl vec2.")
			.def("__mul__", [](const point& self, const float scalar) { return point(self * scalar); }, "scalar"_a,
				"Multiplication operator for points with a scalar.")
			.def("__rmul__", [](const float scalar, const point& self) { return point(scalar * self); }, "scalar"_a,
				"Multiplication operator (reversed) for points with a scalar.")
			.def("__imul__", [](point& self, const float scalar) { return point(self *= scalar); }, "scalar"_a,
				"In-place multiplication operator for points with a scalar.")
			.def("__truediv__", [](const point& self, const float scalar) { return point(self / scalar); }, "scalar"_a,
				"Division operator for points with a scalar.")
			.def("__itruediv__", [](point& self, const float scalar) { return point(self /= scalar); }, "scalar"_a,
				"In-place division operator for points with a scalar.")
			.def("__neg__", [](const point& self) { return point(-self); },
				"Negation operator for points.")
			.def_property_readonly("x", [](const point& self) { return self.x; }, py::return_value_policy::reference_internal,
				"Return the x-component (type: float) of the point.")
			.def_property_readonly("y", [](const point& self) { return self.y; }, py::return_value_policy::reference_internal,
				"Return the y-component (type: float) of the point.")
			.def_property("em_x", py::cpp_function([](const point& self) { return self.em_x; }, py::return_value_policy::reference_internal), py::cpp_function([](const point& self, const em& em_x) { self.em_x = em_x; }),
				"Property to access the x-component (type: em) of the point.")
			.def_property("em_y", py::cpp_function([](const point& self) { return self.em_y; }, py::return_value_policy::reference_internal), py::cpp_function([](const point& self, const em& em_y) { self.em_y = em_y; }),
				"Property to access the y-component (type: em) of the point.");
	py::implicitly_convertible<coordinate, point>();

	// Size
	using size = hgui::kernel::Size<float>;
	py::class_<size, coordinate>(hgui, "size", py::is_final(),
				"A generic class representing a used to represents sizes in the application.")
			.def(py::init(),
				"Default constructor for the size.")
			.def(py::init<const size&>(), "size"_a,
				"Copy constructor for the size.")
			.def(py::init<const coordinate&>(), "coordinate"_a,
				"Copy constructor for the size from the base class.")
			.def(py::init<float>(), "value"_a,
				"Constructs the size while initializing both coordinate with the same value.")
			.def(py::init<const em&>(), "em"_a,
				"Constructs the size while initializing both coordinate with the same em.")
			.def(py::init<float, float>(), "x"_a, "y"_a,
				"Constructs the size with the specified x and y as values.")
			.def(py::init<float, const em&>(), "x"_a, "y"_a,
				"Constructs the size with the specified x as a value and y as an em.")
			.def(py::init<const em&, float>(), "x"_a, "y"_a,
				"Constructs the size with the specified x as an em and y as a value.")
			.def(py::init<const em&, const em&>(), "x"_a, "y"_a,
				"Constructs the size with the specified x and y as ems.")
			.def(py::init([](const std::pair<em, em>& coord) { return new size(coordinate(coord.first, coord.second)); }), "size"_a,
				"Constructs the size from a tuple of two ems.")
			.def(py::init([](const std::pair<float, float>& coord) { return new size(coord.first, coord.second); }), "size"_a,
				"Constructs the size from a tuple of two values.")
			.def(py::init([](const std::pair<em, float>& coord) { return new size(coord.first, coord.second); }), "size"_a,
				"Constructs the size from a tuple of an em and a value.")
			.def(py::init([](const std::pair<float, em>& coord) { return new size(coord.first, coord.second); }), "size"_a,
				"Constructs the size from a tuple of an em and a value (reversed).")
			.def(py::init([](const std::array<em, 2>& coord) { return new size(coord[0], coord[1]); }), "size"_a,
				"Constructs the size from a list of two ems.")
			.def(py::init([](const std::array<float, 2>& coord) { return new size(coord[0], coord[1]); }), "size"_a,
				"Constructs the size from a list of two values.")
			.def(py::init<const hgui::kernel::Vector<float, 2>&>(), "size"_a,
				"Constructs the size from a vector.")
			.def(py::init<const hgui::kernel::GLSLvec2<float>&>(), "size"_a,
				"Constructs the size from a glsl vec2.")
			.def("__copy__", [](const size& self) { return size(self); },
				"Copy constructor for the size.")
			.def("__deepcopy__", [](const size& self, py::dict) { return size(self); }, "memo"_a,
				"Deep copy constructor for the size.")
			.def("__add__", [](const size& self, const size& other) { return size(self + other); }, "size"_a,
				"Addition operator for sizes.")
			.def(py::self + coordinate(), "coordinate"_a,
				"Addition operator for sizes and coordinates.")
			.def("__add__", [](const size& self, const hgui::kernel::GLSLvec2<float>& vec) { return size(self + vec); }, "vector"_a,
				"Addition operator for sizes and glsl vec2.")
			.def("__radd__", [](const hgui::kernel::GLSLvec2<float>& vec, const size& self) { return size(vec + self); }, "vector"_a,
				"Addition operator (reversed) for sizes and glsl vec2.")
			.def(coordinate() + py::self, "coordinate"_a,
				"Addition operator (reversed) for sizes and coordinates.")
			.def("__iadd__", [](size& self, const size& other) { return size(self += other); }, "size"_a,
				"In-place addition operator for sizes.")
			.def(py::self += coordinate(), "coordinate"_a,
				"In-place addition operator for sizes and coordinates.")
			.def("__iadd__", [](size& self, const hgui::kernel::GLSLvec2<float>& vec) { return size(self += vec); }, "vector"_a,
				"In-place addition operator for sizes and glsl vec2.")
			.def("__sub__", [](const size& self, const size& other) { return size(self - other); }, "size"_a,
				"Subtraction operator for sizes.")
			.def(py::self - coordinate(), "coordinate"_a,
				"Subtraction operator for sizes and coordinates.")
			.def("__sub__", [](const size& self, const hgui::kernel::GLSLvec2<float>& vec) { return size(self - vec); }, "size"_a,
				"Subtraction operator for sizes and glsl vec2.")
			.def("__rsub__", [](const hgui::kernel::GLSLvec2<float>& vec, const size& self) { return size(vec - self); }, "size"_a,
				"Subtraction operator (reversed) for sizes and glsl vec2.")
			.def(coordinate() - py::self, "coordinate"_a,
				"Subtraction operator (reversed) for sizes and coordinates.")
			.def("__isub__", [](size& self, const size& other) { return size(self -= other); }, "size"_a,
				"In-place subtraction operator for sizes.")
			.def(py::self -= coordinate(), "coordinate"_a,
				"In-place subtraction operator for sizes and coordinates.")
			.def("__isub__", [](size& self, const hgui::kernel::GLSLvec2<float>& vec) { return size(self -= vec); }, "size"_a,
				"In-place subtraction operator for sizes and glsl vec2.")
			.def("__mul__", [](const size& self, const float scalar) { return size(self * scalar); }, "scalar"_a,
				"Multiplication operator for sizes with a scalar.")
			.def("__rmul__", [](const float scalar, const size& self) { return size(scalar * self); }, "scalar"_a,
				"Multiplication operator (reversed) for sizes with a scalar.")
			.def("__imul__", [](size& self, const float scalar) { return size(self *= scalar); }, "scalar"_a,
				"In-place multiplication operator for sizes with a scalar.")
			.def("__truediv__", [](const size& self, const float scalar) { return size(self / scalar); }, "scalar"_a,
				"Division operator for sizes with a scalar.")
			.def("__itruediv__", [](size& self, const float scalar) { return size(self /= scalar); }, "scalar"_a,
				"In-place division operator for sizes with a scalar.")
			.def("__neg__", [](const size& self) { return size(-self); },
				"Negation operator for sizes.")
			.def_property_readonly("width", [](const size& self) { return self.width; }, py::return_value_policy::reference_internal,
				"Return the width (type: float) of the size.")
			.def_property_readonly("height", [](const size& self) { return self.height; }, py::return_value_policy::reference_internal,
				"Return the height (type: float) of the size.")
			.def_property("em_width", py::cpp_function([](const size& self) { return self.em_width; }, py::return_value_policy::reference_internal), py::cpp_function([](const size& self, const em& em_width) { self.em_width = em_width; }),
				"Property to access the width (type: em) of the size.")
			.def_property("em_height", py::cpp_function([](const size& self) { return self.em_height; }, py::return_value_policy::reference_internal), py::cpp_function([](const size& self, const em& em_height) { self.em_height = em_height; }),
				"Property to access the height (type: em) of the size.");
	py::implicitly_convertible<coordinate, size>();
}
