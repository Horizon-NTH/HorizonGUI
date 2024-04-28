#include "../include/Include.h"

void init_utils(const py::module& hgui)
{
	using cursor = hgui::kernel::Cursor;
	py::class_<cursor, std::shared_ptr<cursor>>(hgui, "Cursor",
				"The Cursor class allows you to set and customize the mouse cursor appearance for your graphical user interface.")
			.def(py::init<hgui::cursors>(), "standard_cursor"_a,
				"Constructs a Cursor object using a standard cursor.")
			.def(py::init<const std::shared_ptr<hgui::kernel::Image>&, const hgui::point&>(), "custom_cursor"_a, "click_position"_a,
				"Constructs a Cursor object using a custom cursor image and click position.")
			.def("make_custom", &cursor::make_custom_cursor, "custom_cursor"_a, "click_position"_a,
				"Sets the cursor to a custom image and click position.")
			.def("make_standard", &cursor::make_standard_cursor, "standard_cursor"_a,
				"Sets the cursor to one of the standard cursors.")
			.def_property_readonly("type", &cursor::get_type,
				"Retrieves the type of the cursor.")
			.def_static("hide", &hgui::CursorManager::hide,
				"Hides the cursor from view.")
			.def_static("reveal", &hgui::CursorManager::reveal,
				"Reveals the hidden cursor.")
			.def_static("disable", &hgui::CursorManager::disable,
				"Disable the cursor.")
			.def_static("enable", &hgui::CursorManager::enable,
				"Enable the cursor.")
			.def_static("use", &hgui::CursorManager::use, "cursor"_a,
				"Sets the cursor to the specified cursor object.")
			.def("get_cursor_used", &hgui::CursorManager::get_cursor_used, py::return_value_policy::reference_internal,
				"Retrieves the current used cursor.");

	using monitor = hgui::kernel::Monitor;
	py::class_<monitor, std::shared_ptr<monitor>>(hgui, "Monitor",
				"The Monitor class provides essential functionality for retrieving information about a monitor.")
			.def_property_readonly("size", &monitor::get_size, py::return_value_policy::reference_internal,
				"Retrieves the size of the monitor.")
			.def_property_readonly("name", &monitor::get_name,
				"Retrieves the name of the monitor.")
			.def_property_readonly("position", &monitor::get_position, py::return_value_policy::reference_internal,
				"Retrieves the position of the monitor.")
			.def_static("get", &hgui::MonitorManager::get, py::return_value_policy::reference_internal, "monitor_name"_a,
				"Retrieves a monitor with the specified name.")
			.def_static("get_monitors_names", &hgui::MonitorManager::get_monitors_names,
				"Retrieves a list of monitor names available in the system.")
			.def_static("get_primary_monitor", &hgui::MonitorManager::get_primary_monitor, py::return_value_policy::reference_internal,
				"Retrieves the primary monitor.");

	using soundplayer = hgui::kernel::SoundPlayer;
	py::class_<soundplayer, std::shared_ptr<soundplayer>>(hgui, "SoundPlayer",
				"The SoundPlayer class is designed for playing audio data.")
			.def(py::init([](const std::shared_ptr<hgui::kernel::Audio>& audio) { return hgui::SoundPlayerManager::create(audio); }), "audio"_a,
				"Constructs a SoundPlayer object by specifying an Audio object.")
			.def("play", &soundplayer::play,
				"Initiates playback of the associated audio.")
			.def("pause", &soundplayer::pause,
				"Pauses the audio playback.")
			.def("stop", &soundplayer::stop,
				"Stops the audio playback.")
			.def("is_playing", &soundplayer::is_playing,
				"Checks if the audio is currently playing.")
			.def_property("loop", &soundplayer::is_looping, [](const soundplayer& self, const bool loop) { loop ? self.loop() : self.stop_loop(); },
				"Property to determine if the sound will loop.")
			.def_property("volume", &soundplayer::get_volume, &soundplayer::set_volume,
				"Property to set the sound's volume.");

	using timer = hgui::Timer;
	py::class_<timer>(hgui, "Timer",
				"The Timer class provides functionality for measuring time intervals.")
			.def(py::init(),
				"Constructs a Timer object.")
			.def(py::init<const timer&>(),
				"Copy constructor.")
			.def("start", &timer::start,
				"Starts the timer, initiating time measurement.")
			.def("stop", &timer::stop,
				"Stops the timer, pausing time measurement.")
			.def("reset", &timer::reset,
				"Resets the timer, setting the elapsed time to zero.")
			.def("restart", &timer::restart,
				"Resets the timer, and then start it.")
			.def("get_time", &timer::get_time,
				"Retrieves the elapsed time in seconds.")
			.def("is_counting", &timer::is_counting,
				"Checks if the timer is actively measuring time.");

	using window = hgui::kernel::Window;
	py::class_<window, std::shared_ptr<window>>(hgui, "Window",
				"The Window class provides functionality for creating and managing graphical windows.")
			.def(py::init([](const std::string& windowName, const hgui::size& size, const hgui::point& position, const std::shared_ptr<hgui::kernel::Image>& icon, const std::shared_ptr<monitor>& fullscreenMonitor, const std::map<hgui::options, bool>& options)
					{
						return hgui::WindowManager::create(windowName, size, position, icon, fullscreenMonitor, options);
					}), "window_name"_a, "size"_a, "position"_a, "icon"_a = nullptr, "monitor"_a = nullptr, "options"_a = std::map<hgui::options, bool>{},
				"Creates a new window with the specified properties, such as window name, size, position, icon, monitor, and additional options.")
			.def_property("size", py::cpp_function(&window::get_size, py::return_value_policy::reference_internal), py::cpp_function(&window::set_size),
				"Property to access to the window size.")
			.def_property("position", py::cpp_function(&window::get_position, py::return_value_policy::reference_internal), py::cpp_function(&window::set_position),
				"Property to access to the window position.")
			.def("set_size_callback", [](window& self, const std::function<void()>& function) { self.set_size_callback(function); }, "function"_a,
				"Binds a size callback function that will be called each time the window size changes.")
			.def("set_position_callback", [](window& self, const std::function<void()>& function) { self.set_position_callback(function); }, "function"_a,
				"Binds a position callback function that will be called each time the window moves.");
}
