#include "../include/Include.h"

template<typename T, std::size_t dimension>
void init_generic_vector(const py::module& m, const std::string& name)
{
	using vector = hgui::kernel::Vector<T, dimension>;
	auto vec = py::class_<vector>(m, name.c_str(),
		           "A generic mathematical vector class.")
	           .def(py::init(),
		           "Default constructor for the vector.")
	           .def(py::init<const T&>(), "initialization_value"_a,
		           "Constructs the vector with a single value.")
	           .def(py::init<const vector&>(), "vector"_a,
		           "Copy constructor for the vector.")
	           .def(py::init<const std::valarray<T>&>(), "list"_a,
		           "Constructs the vector from a list of values.")
	           .def("length", &vector::length,
		           "Compute the length of the vector.")
	           .def("normalize", &vector::normalize,
		           "Normalize the vector.")
	           .def("set", &vector::set, "list"_a = std::valarray<T>{},
		           "Set the vector values from a list of values.")
	           .def("__getitem__", py::overload_cast<int>(&vector::operator[], py::const_), py::return_value_policy::reference_internal, "index"_a,
		           "Get an element from the vector by index.")
	           .def("__setitem__", [](vector& self, int index, T value) { self[index] = value; }, "index"_a, "value"_a,
		           "Set an element in the vector by index.")
	           .def("__copy__", [](const vector& self) { return vector(self); },
		           "Copy constructor for the vector.")
	           .def("__deepcopy__", [](const vector& self, py::dict) { return vector(self); }, "memo"_a,
		           "Deep copy constructor for the vector.")
	           .def(py::self + py::self, "vector"_a,
		           "Addition operator for vectors.")
	           .def(py::self += py::self, "vector"_a,
		           "In-place addition operator for vectors.")
	           .def(py::self - py::self, "vector"_a,
		           "Subtraction operator for vectors.")
	           .def(py::self -= py::self, "vector"_a,
		           "In-place subtraction operator for vectors.")
	           .def(py::self * T(), "scalar"_a,
		           "Scalar multiplication operator for vectors.")
	           .def(py::self / T(), "scalar"_a,
		           "Scalar division operator for vectors.")
	           .def(T() * py::self, "scalar"_a,
		           "Scalar multiplication (reversed) operator for vectors.")
	           .def(py::self *= T(), "scalar"_a,
		           "In-place scalar multiplication operator for vectors.")
	           .def(py::self /= T(), "scalar"_a,
		           "In-place scalar division operator for vectors.")
	           .def(py::self == py::self, "vector"_a,
		           "Equality comparison operator for vectors.")
	           .def(py::self != py::self, "vector"_a,
		           "Inequality comparison operator for vectors.")
	           .def("__str__", [](const vector& self)
			           {
				           std::stringstream ss;
				           ss << self;
				           return ss.str();
			           },
		           "String representation of the vector.")
	           .def("__iter__", [](vector& self) { return py::make_iterator(self.begin(), self.end()); }, py::return_value_policy::reference_internal,
		           "Iterator support for the vector.")
	           .def_property("data", py::cpp_function(&vector::get_data, py::return_value_policy::reference_internal), py::cpp_function(&vector::set_data),
		           "Property to access the underlying data of the vector.");

	if constexpr (std::is_signed_v<T>)
	{
		vec.def(-py::self,
			"Negation operator for vectors.");
	}
}

void init_vector(const py::module& kernel)
{
	init_generic_vector<int, 1>(kernel, "Vector_1_int");
	init_generic_vector<int, 2>(kernel, "Vector_2_int");
	init_generic_vector<int, 3>(kernel, "Vector_3_int");
	init_generic_vector<int, 4>(kernel, "Vector_4_int");
	init_generic_vector<unsigned, 1>(kernel, "Vector_1_unsigned");
	init_generic_vector<unsigned, 2>(kernel, "Vector_2_unsigned");
	init_generic_vector<unsigned, 3>(kernel, "Vector_3_unsigned");
	init_generic_vector<unsigned, 4>(kernel, "Vector_4_unsigned");
	init_generic_vector<float, 1>(kernel, "Vector_1_float");
	init_generic_vector<float, 2>(kernel, "Vector_2_float");
	init_generic_vector<float, 3>(kernel, "Vector_3_float");
	init_generic_vector<float, 4>(kernel, "Vector_4_float");
	init_generic_vector<double, 1>(kernel, "Vector_1_double");
	init_generic_vector<double, 2>(kernel, "Vector_2_double");
	init_generic_vector<double, 3>(kernel, "Vector_3_double");
	init_generic_vector<double, 4>(kernel, "Vector_4_double");
}

template<typename T>
void init_generic_GLSLvec2(const py::module& m, const std::string& name)
{
	using vector = hgui::kernel::GLSLvec2<T>;
	using base = hgui::kernel::Vector<T, 2>;
	auto vec = py::class_<vector, base>(m, name.c_str(), py::is_final(),
		           "A generic 2-dimensional mathematical vector class inspired from GLSL.")
	           .def(py::init(),
		           "Default constructor for the vector.")
	           .def(py::init<T>(), "initialization_value"_a,
		           "Constructs the vector with a single value.")
	           .def(py::init<T, T>(), "x"_a, "y"_a,
		           "Constructs the vector with x-component and y-component.")
	           .def(py::init<const vector&>(), "vector"_a,
		           "Copy constructor for the vector.")
	           .def(py::init<const base&>(), "vector"_a,
		           "Constructs the vector from it's base class.")
	           .def(py::init([](const std::valarray<T>& valarray) { return new vector(base(valarray)); }), "list"_a,
		           "Constructs the vector from a list of values.")
	           .def("__getitem__", py::overload_cast<int>(&vector::operator[], py::const_), py::return_value_policy::reference_internal, "index"_a,
		           "Get an element from the vector by index.")
	           .def("__setitem__", [](vector& self, int index, T value) { self[index] = value; }, "index"_a, "value"_a,
		           "Set an element in the vector by index.")
	           .def("__copy__", [](const vector& self) { return vector(self); },
		           "Copy constructor for the vector.")
	           .def("__deepcopy__", [](const vector& self, py::dict) { return vector(self); }, "memo"_a,
		           "Deep copy constructor for the vector.")
	           .def("__add__", [](const vector& self, const vector& other) { return vector(self + other); }, "vector"_a,
		           "Addition operator for vectors.")
	           .def("__sub__", [](const vector& self, const vector& other) { return vector(self - other); }, "vector"_a,
		           "Subtraction operator for vectors.")
	           .def("__mul__", [](const vector& self, T scalar) { return vector(self * scalar); }, "scalar"_a,
		           "Scalar multiplication operator for vectors.")
	           .def("__rmul__", [](T scalar, const vector& self) { return vector(scalar * self); }, "scalar"_a,
		           "Scalar multiplication (reversed) operator for vectors.")
	           .def("__truediv__", [](const vector& self, T scalar) { return vector(self / scalar); }, "scalar"_a,
		           "Scalar division operator for vectors.")
	           .def("__str__", [](const vector& self)
			           {
				           std::stringstream ss;
				           ss << self;
				           return ss.str();
			           },
		           "String representation of the vector.")
	           .def("__iter__", [](vector& self) { return py::make_iterator(self.begin(), self.end()); }, py::return_value_policy::reference_internal,
		           "Iterator support for the vector.")
	           .def_property("x", py::cpp_function([](const vector& self) { return self.x; }, py::return_value_policy::reference_internal), py::cpp_function([](const vector& self, T value) { self.x = value; }),
		           "Property to access the x-component of the vector.")
	           .def_property("y", py::cpp_function([](const vector& self) { return self.y; }, py::return_value_policy::reference_internal), py::cpp_function([](const vector& self, T value) { self.y = value; }),
		           "Property to access the y-component of the vector.");

	if constexpr (std::is_signed_v<T>)
	{
		vec.def("__neg__", [](const vector& self) { return vector(-self); },
			"Negation operator for vectors.");
	}
}

template<typename T>
void init_generic_GLSLvec3(const py::module& m, const std::string& name)
{
	using vector = hgui::kernel::GLSLvec3<T>;
	using base = hgui::kernel::Vector<T, 3>;
	auto vec = py::class_<vector, base>(m, name.c_str(), py::is_final(),
		           "A generic 3-dimensional mathematical vector class inspired from GLSL.")
	           .def(py::init(),
		           "Default constructor for the vector.")
	           .def(py::init<T>(), "initialization_value"_a,
		           "Constructs the vector with a single value.")
	           .def(py::init<T, T, T>(), "x"_a, "y"_a, "z"_a,
		           "Constructs the vector with x-component, y-component and z-component.")
	           .def(py::init([](const hgui::kernel::GLSLvec2<T>& vec2, T z) { return new vector(vec2.x, vec2.y, z); }), "vec2"_a, "z"_a = T(),
		           "Constructs the vector with a vec2 and an optional z-component.")
	           .def(py::init<const vector&>(), "vector"_a,
		           "Copy constructor for the vector.")
	           .def(py::init<const base&>(), "vector"_a,
		           "Constructs the vector from it's base class.")
	           .def(py::init([](const std::valarray<T>& valarray) { return new vector(base(valarray)); }), "list"_a,
		           "Constructs the vector from a list of values.")
	           .def("__getitem__", py::overload_cast<int>(&vector::operator[], py::const_), py::return_value_policy::reference_internal, "index"_a,
		           "Get an element from the vector by index.")
	           .def("__setitem__", [](vector& self, int index, T value) { self[index] = value; }, "index"_a, "value"_a,
		           "Set an element in the vector by index.")
	           .def("__copy__", [](const vector& self) { return vector(self); },
		           "Copy constructor for the vector.")
	           .def("__deepcopy__", [](const vector& self, py::dict) { return vector(self); }, "memo"_a,
		           "Deep copy constructor for the vector.")
	           .def("__add__", [](const vector& self, const vector& other) { return vector(self + other); }, "vector"_a,
		           "Addition operator for vectors.")
	           .def("__sub__", [](const vector& self, const vector& other) { return vector(self - other); }, "vector"_a,
		           "Subtraction operator for vectors.")
	           .def("__mul__", [](const vector& self, T scalar) { return vector(self * scalar); }, "scalar"_a,
		           "Scalar multiplication operator for vectors.")
	           .def("__rmul__", [](T scalar, const vector& self) { return vector(scalar * self); }, "scalar"_a,
		           "Scalar multiplication (reversed) operator for vectors.")
	           .def("__truediv__", [](const vector& self, T scalar) { return vector(self / scalar); }, "scalar"_a,
		           "Scalar division operator for vectors.")
	           .def("__str__", [](const vector& self)
			           {
				           std::stringstream ss;
				           ss << self;
				           return ss.str();
			           },
		           "String representation of the vector.")
	           .def("__iter__", [](vector& self) { return py::make_iterator(self.begin(), self.end()); }, py::return_value_policy::reference_internal,
		           "Iterator support for the vector.")
	           .def_property("x", py::cpp_function([](const vector& self) { return self.x; }, py::return_value_policy::reference_internal), py::cpp_function([](const vector& self, T value) { self.x = value; }),
		           "Property to access the x-component of the vector.")
	           .def_property("y", py::cpp_function([](const vector& self) { return self.y; }, py::return_value_policy::reference_internal), py::cpp_function([](const vector& self, T value) { self.y = value; }),
		           "Property to access the y-component of the vector.")
	           .def_property("z", py::cpp_function([](const vector& self) { return self.z; }, py::return_value_policy::reference_internal), py::cpp_function([](const vector& self, T value) { self.z = value; }),
		           "Property to access the z-component of the vector.");

	if constexpr (std::is_signed_v<T>)
	{
		vec.def("__neg__", [](const vector& self) { return vector(-self); },
			"Negation operator for vectors.");
	}
}

template<typename T>
void init_generic_GLSLvec4(const py::module& m, const std::string& name)
{
	using vector = hgui::kernel::GLSLvec4<T>;
	using base = hgui::kernel::Vector<T, 4>;
	auto vec = py::class_<vector, base>(m, name.c_str(), py::is_final(),
		           "A generic 4-dimensional mathematical vector class inspired from GLSL.")
	           .def(py::init(),
		           "Default constructor for the vector.")
	           .def(py::init<T>(), "initialization_value"_a,
		           "Constructs the vector with a single value.")
	           .def(py::init<T, T, T, T>(), "x"_a, "y"_a, "z"_a, "w"_a,
		           "Constructs the vector with x-component, y-component, z-component and w-component.")
	           .def(py::init([](const hgui::kernel::GLSLvec2<T>& vec2, T z, T w) { return new vector(vec2.x, vec2.y, z, w); }), "vec2"_a, "z"_a = T(), "w"_a = T(),
		           "Constructs the vector with a vec2 and an optional z-component and w-component.")
	           .def(py::init([](const hgui::kernel::GLSLvec3<T>& vec3, T w) { return new vector(vec3.x, vec3.y, vec3.z, w); }), "vec3"_a, "w"_a = T(),
		           "Constructs the vector with a vec3 and an optional w-component.")
	           .def(py::init<const vector&>(), "vector"_a,
		           "Copy constructor for the vector.")
	           .def(py::init<const base&>(), "vector"_a,
		           "Constructs the vector from it's base class.")
	           .def(py::init([](const std::valarray<T>& valarray) { return new vector(base(valarray)); }), "list"_a,
		           "Constructs the vector from a list of values.")
	           .def("__getitem__", py::overload_cast<int>(&vector::operator[], py::const_), py::return_value_policy::reference_internal, "index"_a,
		           "Get an element from the vector by index.")
	           .def("__setitem__", [](vector& self, int index, T value) { self[index] = value; }, "index"_a, "value"_a,
		           "Set an element in the vector by index.")
	           .def("__copy__", [](const vector& self) { return vector(self); },
		           "Copy constructor for the vector.")
	           .def("__deepcopy__", [](const vector& self, py::dict) { return vector(self); }, "memo"_a,
		           "Deep copy constructor for the vector.")
	           .def("__add__", [](const vector& self, const vector& other) { return vector(self + other); }, "vector"_a,
		           "Addition operator for vectors.")
	           .def("__sub__", [](const vector& self, const vector& other) { return vector(self - other); }, "vector"_a,
		           "Subtraction operator for vectors.")
	           .def("__mul__", [](const vector& self, T scalar) { return vector(self * scalar); }, "scalar"_a,
		           "Scalar multiplication operator for vectors.")
	           .def("__rmul__", [](T scalar, const vector& self) { return vector(scalar * self); }, "scalar"_a,
		           "Scalar multiplication (reversed) operator for vectors.")
	           .def("__truediv__", [](const vector& self, T scalar) { return vector(self / scalar); }, "scalar"_a,
		           "Scalar division operator for vectors.")
	           .def("__str__", [](const vector& self)
			           {
				           std::stringstream ss;
				           ss << self;
				           return ss.str();
			           },
		           "String representation of the vector.")
	           .def("__iter__", [](vector& self) { return py::make_iterator(self.begin(), self.end()); }, py::return_value_policy::reference_internal,
		           "Iterator support for the vector.")
	           .def_property("x", py::cpp_function([](const vector& self) { return self.x; }, py::return_value_policy::reference_internal), py::cpp_function([](const vector& self, T value) { self.x = value; }),
		           "Property to access the x-component of the vector.")
	           .def_property("y", py::cpp_function([](const vector& self) { return self.y; }, py::return_value_policy::reference_internal), py::cpp_function([](const vector& self, T value) { self.y = value; }),
		           "Property to access the y-component of the vector.")
	           .def_property("z", py::cpp_function([](const vector& self) { return self.z; }, py::return_value_policy::reference_internal), py::cpp_function([](const vector& self, T value) { self.z = value; }),
		           "Property to access the z-component of the vector.")
	           .def_property("w", py::cpp_function([](const vector& self) { return self.w; }, py::return_value_policy::reference_internal), py::cpp_function([](const vector& self, T value) { self.w = value; }),
		           "Property to access the w-component of the vector.");

	if constexpr (std::is_signed_v<T>)
	{
		vec.def("__neg__", [](const vector& self) { return vector(-self); },
			"Negation operator for vectors.");
	}
}

template<typename T>
void init_generic_color(const py::module& m, const std::string& name)
{
	using color = hgui::kernel::Color<T>;
	using base = hgui::kernel::Vector<T, 4>;
	auto vec = py::class_<color, base>(m, name.c_str(), py::is_final(),
		           "A generic 4-dimensional mathematical vector class representing rgb-color with an alpha value.")
	           .def(py::init(),
		           "Default constructor for the color.")
	           .def(py::init<T, T>(), "rgb"_a, "aplha"_a = static_cast<T>(1),
		           "Constructs the color with a single value and an optional alpha value.")
	           .def(py::init<const std::string&, T>(), "hex"_a, "aplha"_a = static_cast<T>(1),
		           "Constructs the color with a single value and an optional alpha value.")
	           .def(py::init<T, T, T, T>(), "r"_a, "g"_a, "b"_a, "a"_a = static_cast<T>(1),
		           "Constructs the color with r-component, g-component, b-component and an optional a-component.")
	           .def(py::init<const color&>(), "color"_a,
		           "Copy constructor for the color.")
	           .def(py::init<const base&>(), "color"_a,
		           "Constructs the color from it's base class.")
	           .def(py::init([](const std::valarray<T>& valarray) { return new color(base(valarray)); }), "list"_a,
		           "Constructs the color from a list of values.")
	           .def("__getitem__", py::overload_cast<int>(&color::operator[], py::const_), py::return_value_policy::reference_internal, "index"_a,
		           "Get an element from the color by index.")
	           .def("__setitem__", [](color& self, int index, T value) { self[index] = value; }, "index"_a, "value"_a,
		           "Set an element in the color by index.")
	           .def("__copy__", [](const color& self) { return color(self); },
		           "Copy constructor for the color.")
	           .def("__deepcopy__", [](const color& self, py::dict) { return color(self); }, "memo"_a,
		           "Deep copy constructor for the color.")
	           .def("__add__", [](const color& self, const color& other) { return color(self + other); }, "color"_a,
		           "Addition operator for color.")
	           .def("__sub__", [](const color& self, const color& other) { return color(self - other); }, "color"_a,
		           "Subtraction operator for color.")
	           .def("__mul__", [](const color& self, T scalar) { return color(self * scalar); }, "scalar"_a,
		           "Scalar multiplication operator for color.")
	           .def("__rmul__", [](T scalar, const color& self) { return color(scalar * self); }, "scalar"_a,
		           "Scalar multiplication (reversed) operator for color.")
	           .def("__truediv__", [](const color& self, T scalar) { return color(self / scalar); }, "scalar"_a,
		           "Scalar division operator for color.")
	           .def("__str__", [](const color& self) -> std::string
			           {
				           std::stringstream ss;
				           ss << self;
				           return ss.str();
			           },
		           "String representation of the color.")
	           .def("__iter__", [](color& self) { return py::make_iterator(self.begin(), self.end()); }, py::return_value_policy::reference_internal,
		           "Iterator support for the color.")
	           .def_property("r", py::cpp_function([](const color& self) { return self.r; }, py::return_value_policy::reference_internal), py::cpp_function([](const color& self, T value) { self.r = value; }),
		           "Property to access the r-component of the color.")
	           .def_property("g", py::cpp_function([](const color& self) { return self.g; }, py::return_value_policy::reference_internal), py::cpp_function([](const color& self, T value) { self.g = value; }),
		           "Property to access the g-component of the color.")
	           .def_property("b", py::cpp_function([](const color& self) { return self.b; }, py::return_value_policy::reference_internal), py::cpp_function([](const color& self, T value) { self.b = value; }),
		           "Property to access the b-component of the color.")
	           .def_property("a", py::cpp_function([](const color& self) { return self.a; }, py::return_value_policy::reference_internal), py::cpp_function([](const color& self, T value) { self.a = value; }),
		           "Property to access the a-component of the color.");

	if constexpr (std::is_signed_v<T>)
	{
		vec.def("__neg__", [](const color& self) { return color(-self); },
			"Negation operator for color.");
	}
}

void init_glsl(const py::module& hgui)
{
	init_generic_GLSLvec2<int>(hgui, "ivec2");
	init_generic_GLSLvec2<unsigned>(hgui, "uvec2");
	init_generic_GLSLvec2<float>(hgui, "vec2");
	init_generic_GLSLvec2<double>(hgui, "dvec2");
	init_generic_GLSLvec3<int>(hgui, "ivec3");
	init_generic_GLSLvec3<unsigned>(hgui, "uvec3");
	init_generic_GLSLvec3<float>(hgui, "vec3");
	init_generic_GLSLvec3<double>(hgui, "dvec3");
	init_generic_GLSLvec4<int>(hgui, "ivec4");
	init_generic_GLSLvec4<unsigned>(hgui, "uvec4");
	init_generic_GLSLvec4<float>(hgui, "vec4");
	init_generic_GLSLvec4<double>(hgui, "dvec4");
	init_generic_color<float>(hgui, "color");
}
