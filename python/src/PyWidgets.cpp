#include "../include/PyWidgets.h"

void PyWidget::set_size(const hgui::size& newSize)
{
	PYBIND11_OVERRIDE(void, Widget, set_size, newSize);
}

void PyWidget::set_position(const hgui::point& newPosition)
{
	PYBIND11_OVERRIDE(void, Widget, set_position, newPosition);
}

void PyWidget::set_rotation(float newRotation)
{
	PYBIND11_OVERRIDE(void, Widget, set_rotation, newRotation);
}

void PyWidget::draw() const
{
	PYBIND11_OVERRIDE_PURE(void, Widget, draw,);
}

bool PyWidget::is_inside(const hgui::point& point) const
{
	PYBIND11_OVERRIDE_PURE(bool, Widget, is_inside, point);
}

void PySprite::set_position(const hgui::point& newPosition)
{
	PYBIND11_OVERRIDE(void, Sprite, set_position, newPosition);
}

void PySprite::set_rotation(float newRotation)
{
	PYBIND11_OVERRIDE(void, Sprite, set_rotation, newRotation);
}

void PySprite::set_size(const hgui::size& newSize)
{
	PYBIND11_OVERRIDE(void, Sprite, set_size, newSize);
}

void PySprite::draw() const
{
	PYBIND11_OVERRIDE(void, Sprite, draw,);
}

bool PySprite::is_inside(const hgui::point& point) const
{
	PYBIND11_OVERRIDE(bool, Sprite, is_inside, point);
}

void init_widgets(const py::module& hgui, const py::module& kernel)
{
	using widget = hgui::kernel::Widget;
	py::class_<widget, PyWidget, std::shared_ptr<widget>>(kernel, "Widget",
				"The Widget class is a fundamental component designed for creating interactive graphical widgets in your application.")
			.def(py::init<const std::shared_ptr<hgui::kernel::Shader>&, const hgui::size&, const hgui::point&, float>(), "shader"_a, "size"_a, "position"_a, "rotation"_a,
				"Constructs a Widget object with the specified rendering shader, size, position, and a rotation.")
			.def_property("position", py::cpp_function(&widget::get_position, py::return_value_policy::reference_internal), py::cpp_function(&widget::set_position),
				"Property to access the widget's position.")
			.def_property("size", py::cpp_function(&widget::get_size, py::return_value_policy::reference_internal), py::cpp_function(&widget::set_size),
				"Property to access the widget's size.")
			.def_property("rotation", py::cpp_function(&widget::get_rotation, py::return_value_policy::copy), py::cpp_function(&widget::set_rotation),
				"Property to access the widget's rotation.")
			.def("bind", py::overload_cast<const std::variant<hgui::inputs, std::pair<hgui::buttons, hgui::actions>, std::tuple<hgui::inputs, hgui::buttons, hgui::actions>>&, const std::function<void()>&>(&widget::bind), "action"_a, "function"_a,
				"Binds an input or an action to a user-defined function, allowing interaction with the widget.")
			.def("is_bind", py::overload_cast<const std::variant<hgui::inputs, std::pair<hgui::buttons, hgui::actions>, std::tuple<hgui::inputs, hgui::buttons, hgui::actions>>&>(&widget::is_bind), "action"_a,
				"Check if an input or an action is already bind to the widget.")
			.def("unbind", py::overload_cast<const std::variant<hgui::inputs, std::pair<hgui::buttons, hgui::actions>, std::tuple<hgui::inputs, hgui::buttons, hgui::actions>>&>(&widget::unbind), "action"_a,
				"Unbinds a previously bound input or an action from the widget.")
			.def("draw", &widget::draw,
				"A pure virtual function that must be implemented by derived widget classes to define the rendering behavior.")
			.def("is_inside", &widget::is_inside, "point"_a,
				"Indicates whether the given point is over the widget. A pure virtual function that must be implemented by derived widget classes to define the inputs behavior.")
			.def_static("get_active_tag", &widget::get_active_tag, py::return_value_policy::reference_internal,
				"Retrieve all tags that are actually active.")
			.def_static("get_widgets", &widget::get_widgets, py::return_value_policy::reference_internal, "tag"_a,
				"Return all widgets as std::weak_ptr that are associated to the given tag.");

	using button = hgui::kernel::Button;
	py::class_<button, widget, std::shared_ptr<button>>(hgui, "Button", py::is_final(),
				"The Button class, is a user interface element designed to respond to user interactions. Buttons are commonly used to trigger actions when clicked, providing interactivity within your graphical application.")
			.def(py::init([](const std::function<void()>& function, const hgui::size& size, const hgui::point& position, const std::shared_ptr<hgui::kernel::Texture>& texture, hgui::color& color, const float borderRadius, const bool blurrOnHover, const std::string& text, const std::shared_ptr<hgui::kernel::Font>& font, const hgui::color& textColor, const float rotation)
					{
						return hgui::ButtonManager::create(function, size, position, texture, color, borderRadius, blurrOnHover, text, font, textColor, rotation);
					}), "function"_a, "size"_a, "position"_a, "texture"_a = nullptr, "colors"_a = HGUI_COLOR_WHITE, "borderRadius"_a = 100.f, "blurrOnHover"_a = true, "text"_a = "", "font"_a = nullptr, "textColor"_a = HGUI_COLOR_BLACK, "rotation"_a = 0.f,
				"Constructs a Button object with the specified action function, size, position, text label, colors (normal color, hover color and pressed color), rotation, corner angular radius, and optional texture and let you choose if the button will be blurred when in focus.")
			.def("press", &button::press,
				"Simulates a button press, invoking the assigned action function.")
			.def_property("state", py::cpp_function(&button::get_state, py::return_value_policy::reference_internal), py::cpp_function(&button::set_state),
				"Property to access the button's state.")
			.def_property("blurrOnHover", py::cpp_function(&button::get_blurr_on_hover, py::return_value_policy::copy), py::cpp_function(&button::set_blurr_on_hover),
				"Property to access the button's blurrOnHover status.")
			.def_property("color", py::cpp_function(&button::get_color, py::return_value_policy::reference_internal), py::cpp_function([](button& self, const std::variant<hgui::color, std::tuple<hgui::color, hgui::color, hgui::color>>& colors)
					{
						self.set_color(colors.index() == 1 ? std::get<1>(colors) : std::tuple(std::get<0>(colors), std::get<0>(colors), std::get<0>(colors)));
					}),
				"Property to access the button's colors.")
			.def_property("texture", py::cpp_function(&button::get_texture, py::return_value_policy::reference_internal), py::cpp_function(&button::set_texture),
				"Property to access the button's texture.")
			.def_property("text", py::cpp_function(&button::get_text, py::return_value_policy::reference_internal), py::cpp_function(&button::set_text),
				"Property to access the button's text.")
			.def_property("function", py::cpp_function(&button::get_function, py::return_value_policy::reference_internal), py::cpp_function(&button::set_function),
				"Property to access the button's function.");

	using canvas = hgui::kernel::Canvas;
	py::class_<canvas, widget, std::shared_ptr<canvas>>(hgui, "Canvas", py::is_final(),
				"The Canvas class,  is an essential element within your graphical application for drawing and managing various shapes and lines.")
			.def(py::init([](const std::shared_ptr<hgui::kernel::Shader>& shader, const hgui::size& size, const hgui::point& position, const hgui::color& color, const float rotation)
					{
						return hgui::CanvasManager::create(shader, size, position, color, rotation);
					}), "shader"_a, "size"_a, "position"_a, "color"_a = HGUI_COLOR_WHITE, "rotation"_a = 0.f,
				"Constructs a Canvas object with the specified shader, size, position, color, and a rotation.")
			.def("get_drawer", &canvas::get_drawer, py::return_value_policy::reference_internal,
				"Retrieves the associated Drawer object, allowing you to draw various shapes on the Canvas.");

	using label = hgui::kernel::Label;
	py::class_<label, widget, std::shared_ptr<label>>(hgui, "Label", py::is_final(),
				"The Label class is designed to display labels within your graphical application. Labels can be used to present information, titles, or any textual content.")
			.def(py::init([](const std::string& text, const hgui::point& position, const std::shared_ptr<hgui::kernel::Font>& font, const std::tuple<unsigned int, hgui::color, float>& textOptions, const float rotation)
					{
						return hgui::LabelManager::create(text, position, font, textOptions, rotation);
					}), "text"_a, "position"_a, "font"_a, "textOptions"_a = std::tuple{12u, HGUI_COLOR_WHITE, 1.0f}, "rotation"_a = 0.f,
				"Constructs a Label object with the specified text, position, font, font size, color, scale and a rotation.")
			.def_property("text", py::cpp_function(&label::get_text, py::return_value_policy::copy), py::cpp_function(&label::set_text),
				"Property to access the label's text.")
			.def_property("font_size", py::cpp_function(&label::get_font_size, py::return_value_policy::copy), py::cpp_function(&label::set_font_size),
				"Property to access the label's font_size.")
			.def_property("width", py::cpp_function([](const label& self) { return self.get_size().width; }, py::return_value_policy::reference_internal), py::cpp_function(&label::set_width),
				"Property to access the label's width.")
			.def_property("height", py::cpp_function([](const label& self) { return self.get_size().height; }, py::return_value_policy::reference_internal), py::cpp_function(&label::set_height),
				"Property to access the label's height.")
			.def_property("color", py::cpp_function(&label::get_color, py::return_value_policy::reference_internal), py::cpp_function(&label::set_color),
				"Property to access the text's color.");

	using ranges = hgui::kernel::Ranges;
	py::class_<ranges>(kernel, "Ranges",
				"The Ranges structure represents the range of values the slider can take, including minimum and maximum values, step size, and precision.")
			.def(py::init<float, float, unsigned, unsigned>(), "min"_a, "max"_a, "step"_a = 0u, "precision"_a = 2u,
				"Default constructor")
			.def_readwrite("min", &ranges::min,
				"Minimum value of the slider.")
			.def_readwrite("max", &ranges::max,
				"Maximum value of the slider.")
			.def_readwrite("step", &ranges::step,
				"Number of step in the slider.")
			.def_readwrite("precision", &ranges::precision,
				"Precision of the values.")
			.def("round", &ranges::round, "value"_a,
				"Rounds the given value based on the precision.")
			.def("sort", &ranges::sort,
				"Sorts the minimum and maximum values.");

	using slider = hgui::kernel::Slider;
	py::class_<slider, widget, std::shared_ptr<slider>>(hgui, "Slider", py::is_final(),
				"The Slider class is designed to provide a graphical slider within your graphical application. Sliders are interactive controls that allow users to select a value from a specified range.")
			.def(py::init([](const ranges& range, const hgui::size& size, const hgui::point& position, const hgui::color& inactiveBarColor, const hgui::color& activeBarColor, const hgui::color& sliderColor, const slider::Function& function, const float rotation)
					{
						return hgui::SliderManager::create(range, size, position, inactiveBarColor, activeBarColor, sliderColor, function, rotation);
					}), "range"_a, "size"_a, "position"_a, "inactiveBarColor"_a = hgui::color(66), "activeBarColor"_a = hgui::color(9, 127, 224), "sliderColor"_a = HGUI_COLOR_WHITE, "function"_a = nullptr, "rotation"_a = 0.f,
				"Constructs a Slider object with the specified range, colors, size, position, function, and a rotation.")
			.def_property("range", py::cpp_function(&slider::get_range, py::return_value_policy::reference_internal), py::cpp_function(&slider::set_range),
				"Property to access the slider's range.")
			.def_property("value", py::cpp_function(&slider::get_value, py::return_value_policy::reference_internal), py::cpp_function(&slider::set_value),
				"Property to access the slider's value.")
			.def_property("slider_position", py::cpp_function(&slider::get_slider_position, py::return_value_policy::reference_internal), py::cpp_function(&slider::set_slider_position),
				"Property to access the slider's position.")
			.def_property("function", py::cpp_function(&slider::get_function, py::return_value_policy::reference_internal), py::cpp_function(&slider::set_function),
				"Property to access the slider's function.");

	using sprite = hgui::kernel::Sprite;
	py::class_<sprite, widget, PySprite, std::shared_ptr<sprite>>(hgui, "Sprite",
				"The Sprite class, represents a graphical element that displays an image or texture. Sprites are commonly used to render images, textures, or icons within your graphical application.")
			.def(py::init([](const std::variant<std::shared_ptr<hgui::kernel::Texture>, std::shared_ptr<hgui::kernel::Image>>& texture, const hgui::size& size, const hgui::point& position, const hgui::color& color, float rotation)
					{
						return hgui::SpriteManager::create(texture, size, position, color, rotation);
					}), "texture"_a, "size"_a, "position"_a, "color"_a = HGUI_COLOR_WHITE, "rotation"_a = 0.f,
				"Constructs a Sprite object with the specified texture, size, position, color, and a rotation.")
			.def_property("texture", py::cpp_function(&sprite::get_texture, py::return_value_policy::reference_internal), py::cpp_function(&sprite::set_texture),
				"Property to access the sprite's texture.");

	using animatedsprite = hgui::kernel::AnimatedSprite;
	py::class_<animatedsprite, sprite, std::shared_ptr<animatedsprite>>(hgui, "AnimatedSprite", py::is_final(),
				"The AnimatedSprite class, is an extension of the Sprite class, designed specifically for handling animated sprites. Animated sprites are graphical elements that display a sequence of images or frames.")
			.def(py::init([](const std::shared_ptr<hgui::kernel::GIF>& gif, const hgui::size& size, const hgui::point& position, const hgui::color& color, float rotation)
					{
						return hgui::SpriteManager::create(gif, size, position, color, rotation);
					}), "gif"_a, "size"_a, "position"_a, "color"_a = HGUI_COLOR_WHITE, "rotation"_a = 0.f,
				"Constructs an AnimatedSprite object with the specified, GIF, size, position, color, and a rotation.")
			.def_property("gif", py::cpp_function(&animatedsprite::get_gif, py::return_value_policy::reference_internal), py::cpp_function(&animatedsprite::set_gif),
				"Property to access the gif.")
			.def_property("loop", py::cpp_function(&animatedsprite::is_looping, py::return_value_policy::copy), py::cpp_function([](animatedsprite& self, const bool value) { value ? self.loop() : self.stop_loop(); }),
				"Property to set if the gif is looping.")
			.def("play", &animatedsprite::play,
				"Initiates the playback of the animated sequence.")
			.def("is_playing", &animatedsprite::is_playing,
				"Indicates whether the animated sequence is currently playing.")
			.def("pause", &animatedsprite::pause,
				"Pauses the playback of the animated sequence.")
			.def("stop", &animatedsprite::stop,
				"Stops the playback of the animated sequence.");
}
