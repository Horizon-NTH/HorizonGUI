#include "../include/fwd.h"

PYBIND11_MODULE(hgui, m)
{
	m.doc() = "Python binding of HorizonGUI a graphical interface in c++ with OpenGl";
	init_hgui(m);
}

void init_hgui(py::module& hgui)
{
	init_enum(hgui);
	py::module kernel = hgui.def_submodule("kernel");
	init_vector(kernel);
	init_glsl(hgui);
	init_coordinate(hgui);
	const py::module shape = kernel.def_submodule("shape");
	init_shapes(shape);
	init_data(hgui, kernel);
	init_resources(hgui, kernel);
	init_function(hgui, kernel);
	init_utils(hgui);
	init_managers(hgui);
	init_widgets(hgui, kernel);
}
