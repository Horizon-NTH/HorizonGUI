#include "../include/Include.h"

void init_managers(py::module& hgui)
{
	using tag = hgui::TagManager;
	py::module manager = hgui.def_submodule("TagManager",
		"The TagManager module is an utility that provides functionality to manage and organize tags within your application. Tags can be associated with various elements, such as widgets, to categorize and group them. This allows you to create, retrieve, and set the current tag. It's a useful tool for implementing features like rendering specific groups of elements or applying effects to elements with certain tags.");
	manager.def("create_tag", &tag::create_tag, "new_tag"_a,
		"Creates a new tag with the provided name.");
	manager.def("get_tags", &tag::get_tags, py::return_value_policy::reference_internal,
		"Retrieves a vector containing all the created tags.");
	manager.def("get_current_tag", &tag::get_current_tag, py::return_value_policy::reference_internal,
		"Retrieves the current active tag.");
	manager.def("set_current_tag", &tag::set_current_tag, "tag"_a,
		"Sets the current active tag to the specified tag.");

	using task = hgui::TaskManager;
	manager = hgui.def_submodule("TaskManager",
		"The TaskManager module is a utility for scheduling and executing tasks or functions after a specific time. It is commonly used in graphical applications to manage tasks that require periodic execution, such as animation updates, frame rendering, or other recurring operations.");
	manager.def("program", &task::program, "delay"_a, "function"_a, "id"_a = "",
		"Schedules a task for execution after the specified delay. This function takes a delay duration and a function to be executed after the delay. It can also take an ID to be associated with this task; if no ID is passed, a custom one is created. This function also retrieves the ID of the newly created task.");
	manager.def("is_program", &task::is_program, "id"_a,
		"Retrieve true if a program is scheduled for the given id.");
	manager.def("deprogram", &task::deprogram, "tasks"_a = task::get_ids(),
		"Deprogram the task with the associated id.");
	manager.def("get_ids", &task::get_ids,
		"Returns the ids of all programmed tasks.");

	using keyboard = hgui::KeyBoardManager;
	manager = hgui.def_submodule("KeyBoardManager",
		"The KeyBoardManager module facilitates keyboard input handling in your graphical user interface. It allows you to bind specific key with a specific actions to corresponding functions, enabling you to respond to key action. It supports binding both individual keys and key combinations.");
	manager.def("bind", &keyboard::bind, "action"_a, "function"_a,
		"Binds a keyboard action or combination to a specific function.");
	manager.def("get_bind", &keyboard::get_bind, "action"_a,
		"Retrieves the function bound to a keyboard action or combination.");
	manager.def("is_bind", &keyboard::is_bind, "action"_a,
		"Checks if a keyboard action or combination is already bound.");
	manager.def("unbind", &keyboard::unbind, "action"_a,
		"Unbinds a previously bound keyboard action or combination.");
	manager.def("bind_key_callback", &keyboard::bind_key_callback, "function"_a,
		"Binds a key callback function that can handle either a single key or key-action pair or receive key and action information.");

	using mouse = hgui::MouseManager;
	manager = hgui.def_submodule("MouseManager",
		"The MouseManager module provides a convenient interface for handling various mouse-related input actions and events in your graphical application. It is responsible for managing mouse button clicks, scroll actions, and cursor position tracking.");
	manager.def("bind", &mouse::bind, "action"_a, "function"_a,
		"Binds one of the mouses inputs or actions to a user-defined function.");
	manager.def("is_bind", &mouse::is_bind, "action"_a,
		"Retrieve if one of the mouses inputs or actions is already bind.");
	manager.def("unbind", &mouse::unbind, "action"_a,
		"Unbinds a previously bound one of the mouses inputs or actions.");
	manager.def("bind_click_callback", &mouse::bind_click_callback, "function"_a,
		"Binds a callback function for handling mouse button clicks.");
	manager.def("bind_scroll_callback", &mouse::bind_scroll_callback, "function"_a,
		"Binds a callback function for handling mouse scroll events.");

	using renderer = hgui::Renderer;
	manager = hgui.def_submodule("Renderer",
		"The Renderer module is a fundamental component for rendering and displaying graphical content in your graphical application.");
	manager.def("draw", &renderer::draw, "tags"_a = std::vector<std::string>{}, "post_processing_option"_a = hgui::effects::CLASSIC,
		"Renders graphical content based on specified tags and post-processing effects.");
	manager.def("set_background_color", &renderer::set_background_color, "color"_a,
		"Sets the background color for the rendering.");
	manager.def("get_background_color", &renderer::get_background_color,
		"Retrieves the current background color.");
	manager.def("set_draw_callback", &renderer::set_draw_callback, "function"_a,
		"Set a custom function that will be called inside the render loop.");
}
