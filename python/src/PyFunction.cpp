#include "../include/Include.h"

void init_function(py::module& hgui, py::module& kernel)
{
	// Dot function
	// int
	kernel.def("dot", &hgui::kernel::dot<int, 1>, "u"_a, "v"_a,
		"Calculate the dot product of two 1-dimensional integer vectors.");
	kernel.def("dot", &hgui::kernel::dot<int, 2>, "u"_a, "v"_a,
		"Calculate the dot product of two 2-dimensional integer vectors.");
	kernel.def("dot", &hgui::kernel::dot<int, 3>, "u"_a, "v"_a,
		"Calculate the dot product of two 3-dimensional integer vectors.");
	kernel.def("dot", &hgui::kernel::dot<int, 4>, "u"_a, "v"_a,
		"Calculate the dot product of two 4-dimensional integer vectors.");
	// unsigned
	kernel.def("dot", &hgui::kernel::dot<unsigned, 1>, "u"_a, "v"_a,
		"Calculate the dot product of two 1-dimensional unsigned integer vectors.");
	kernel.def("dot", &hgui::kernel::dot<unsigned, 2>, "u"_a, "v"_a,
		"Calculate the dot product of two 2-dimensional unsigned integer vectors.");
	kernel.def("dot", &hgui::kernel::dot<unsigned, 3>, "u"_a, "v"_a,
		"Calculate the dot product of two 3-dimensional unsigned integer vectors.");
	kernel.def("dot", &hgui::kernel::dot<unsigned, 4>, "u"_a, "v"_a,
		"Calculate the dot product of two 4-dimensional unsigned integer vectors.");
	// float
	kernel.def("dot", &hgui::kernel::dot<float, 1>, "u"_a, "v"_a,
		"Calculate the dot product of two 1-dimensional floating-point vectors.");
	kernel.def("dot", &hgui::kernel::dot<float, 2>, "u"_a, "v"_a,
		"Calculate the dot product of two 2-dimensional floating-point vectors.");
	kernel.def("dot", &hgui::kernel::dot<float, 3>, "u"_a, "v"_a,
		"Calculate the dot product of two 3-dimensional floating-point vectors.");
	kernel.def("dot", &hgui::kernel::dot<float, 4>, "u"_a, "v"_a,
		"Calculate the dot product of two 4-dimensional floating-point vectors.");
	// double
	kernel.def("dot", &hgui::kernel::dot<double, 1>, "u"_a, "v"_a,
		"Calculate the dot product of two 1-dimensional double-precision vectors.");
	kernel.def("dot", &hgui::kernel::dot<double, 2>, "u"_a, "v"_a,
		"Calculate the dot product of two 2-dimensional double-precision vectors.");
	kernel.def("dot", &hgui::kernel::dot<double, 3>, "u"_a, "v"_a,
		"Calculate the dot product of two 3-dimensional double-precision vectors.");
	kernel.def("dot", &hgui::kernel::dot<double, 4>, "u"_a, "v"_a,
		"Calculate the dot product of two 4-dimensional double-precision vectors.");

	// Cross function
	kernel.def("cross", &hgui::kernel::cross<int>, "u"_a, "v"_a,
		"Calculate the cross product of two 3-dimensional integer vectors.");
	kernel.def("cross", &hgui::kernel::cross<unsigned>, "u"_a, "v"_a,
		"Calculate the cross product of two 3-dimensional unsigned integer vectors.");
	kernel.def("cross", &hgui::kernel::cross<float>, "u"_a, "v"_a,
		"Calculate the cross product of two 3-dimensional floating-point vectors.");
	kernel.def("cross", &hgui::kernel::cross<double>, "u"_a, "v"_a,
		"Calculate the cross product of two 3-dimensional double-precision vectors.");

	// Distance function
	// int
	kernel.def("distance", &hgui::kernel::distance<int, 1>, "u"_a, "v"_a,
		"Calculate the distance between two 1-dimensional integer vectors.");
	kernel.def("distance", &hgui::kernel::distance<int, 2>, "u"_a, "v"_a,
		"Calculate the distance between two 2-dimensional integer vectors.");
	kernel.def("distance", &hgui::kernel::distance<int, 3>, "u"_a, "v"_a,
		"Calculate the distance between two 3-dimensional integer vectors.");
	kernel.def("distance", &hgui::kernel::distance<int, 4>, "u"_a, "v"_a,
		"Calculate the distance between two 4-dimensional integer vectors.");
	// unsigned
	kernel.def("distance", &hgui::kernel::distance<unsigned, 1>, "u"_a, "v"_a,
		"Calculate the distance between two 1-dimensional unsigned integer vectors.");
	kernel.def("distance", &hgui::kernel::distance<unsigned, 2>, "u"_a, "v"_a,
		"Calculate the distance between two 2-dimensional unsigned integer vectors.");
	kernel.def("distance", &hgui::kernel::distance<unsigned, 3>, "u"_a, "v"_a,
		"Calculate the distance between two 3-dimensional unsigned integer vectors.");
	kernel.def("distance", &hgui::kernel::distance<unsigned, 4>, "u"_a, "v"_a,
		"Calculate the distance between two 4-dimensional unsigned integer vectors.");
	// float
	kernel.def("distance", &hgui::kernel::distance<float, 1>, "u"_a, "v"_a,
		"Calculate the distance between two 1-dimensional floating-point vectors.");
	kernel.def("distance", &hgui::kernel::distance<float, 2>, "u"_a, "v"_a,
		"Calculate the distance between two 2-dimensional floating-point vectors.");
	kernel.def("distance", &hgui::kernel::distance<float, 3>, "u"_a, "v"_a,
		"Calculate the distance between two 3-dimensional floating-point vectors.");
	kernel.def("distance", &hgui::kernel::distance<float, 4>, "u"_a, "v"_a,
		"Calculate the distance between two 4-dimensional floating-point vectors.");
	// double
	kernel.def("distance", &hgui::kernel::distance<double, 1>, "u"_a, "v"_a,
		"Calculate the distance between two 1-dimensional double-precision vectors.");
	kernel.def("distance", &hgui::kernel::distance<double, 2>, "u"_a, "v"_a,
		"Calculate the distance between two 2-dimensional double-precision vectors.");
	kernel.def("distance", &hgui::kernel::distance<double, 3>, "u"_a, "v"_a,
		"Calculate the distance between two 3-dimensional double-precision vectors.");
	kernel.def("distance", &hgui::kernel::distance<double, 4>, "u"_a, "v"_a,
		"Calculate the distance between two 4-dimensional double-precision vectors.");

	hgui.def("after", &hgui::after, "delay"_a, "function"_a,
		"Schedules a function to be executed after a specified delay.");
	hgui.def("file_reader", &hgui::file_reader, "file_path"_a,
		"Reads the contents of a file and returns them as a string.");
	hgui.def("random", &hgui::random, "chances"_a,
		"Generates a random boolean value based on the given probability (chances). Returns true with the given probability, and false otherwise.");
	hgui.def("get_unique_id", &hgui::get_unique_id,
		"Generates a unique identifier string. Each call to this function produces a new unique ID.");
	hgui.def("get_delta_time", &hgui::get_delta_time,
		"Retrieve the delta time of the application.");
	hgui.def("init", &hgui::init,
		"Initializes the HorizonGUI library. This function initializes all dependencies needed and must be called at the beginning of your code.");
	hgui.def("end", &hgui::end,
		"Terminates application, destroys all windows, releases all acquired resources and exits rendering loop.");
	hgui.def("get_mouse_position", &hgui::MouseManager::get_position,
		"Retrieves the current cursor position as a point.");
	hgui.def("active", &hgui::kernel::Widget::active, "tags"_a = std::vector<std::string>{},
		"Activates widget's binds based on their tags, allowing you to specify which group of widgets should be active.");
	hgui.def("loop", &hgui::Renderer::loop,
		"Starts the rendering loop, which continuously redraws the graphics on the screen.");
}
