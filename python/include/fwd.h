#pragma once

#include "Include.h"

void init_hgui(py::module& hgui);
void init_shapes(const py::module& kernel);
void init_vector(const py::module& kernel);
void init_function(py::module& hgui, py::module& kernel);
void init_glsl(const py::module& hgui);
void init_coordinate(const py::module& hgui);
void init_enum(const py::module& hgui);
void init_data(const py::module& hgui, const py::module& kernel);
void init_resources(const py::module& hgui, const py::module& kernel);
void init_utils(const py::module& hgui);
void init_managers(py::module& hgui);
void init_widgets(const py::module& hgui, const py::module& kernel);
