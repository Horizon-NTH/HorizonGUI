#include "../include/Include.h"

void init_data(const py::module& hgui, const py::module& kernel)
{
	// Image
	using image = hgui::kernel::Image;
	py::class_<image, std::shared_ptr<image>>(hgui, "Image",
				"The Image class is designed for loading, storing, and manipulating image data.")
			.def(py::init<const std::string&>(), "image_path"_a,
				"Constructs an Image object by specifying the path to the image file.")
			.def_property_readonly("size", &image::get_size,
				"Retrieves the size of the image (dimension).")
			.def("save", &image::save_image, "file_path"_a,
				"Saves the image data stored in the Image object as a png to the specified path.");

	using gif = hgui::kernel::GIF;
	py::class_<gif, std::shared_ptr<gif>>(hgui, "GIF",
				"The GIF class is designed for handling animated GIF image data.")
			.def(py::init<const std::string&>(), "gif_path"_a,
				"Constructs a GIF object by specifying the path to the GIF file.")
			.def_property_readonly("size", &gif::get_size,
				"Retrieves the size of the GIF (dimension).")
			.def("get_frames_count", &gif::get_frames_count,
				"Retrieves the GIF'a frames count.")
			.def("get_frame", &gif::get_frame, "frame_number"_a,
				"Retrieves a specific frame of the GIF, including the image and delay.")
			.def("set_delay", py::overload_cast<const std::vector<hgui::kernel::GIFData::delay>&>(&gif::set_delay), "delays_list"_a,
				"Sets the delay for a specific frame in the GIF.")
			.def("set_delay", py::overload_cast<const hgui::kernel::GIFData::delay&, unsigned int>(&gif::set_delay), "delay"_a, "frame_number"_a,
				"Sets delays for all frames in the GIF.");

	using audio = hgui::kernel::Audio;
	py::class_<audio, std::shared_ptr<audio>>(hgui, "Audio",
				"The Audio class is designed for handling audio data.")
			.def(py::init<const std::string&>(), "file_path"_a,
				"Constructs an Audio object by specifying the path to the audio file.");

	using character = hgui::kernel::Character;
	py::class_<character>(kernel, "Character",
				"The Character structure is used to represent individual characters loaded from a font file.")
			.def(py::init<const std::shared_ptr<hgui::kernel::Texture>&, hgui::size, hgui::ivec2, unsigned>(), "texture"_a, "size"_a, "bearing"_a, "advance"_a,
				"Default constructor")
			.def_readwrite("texture", &character::texture,
				"The texture associated with the character.")
			.def_readwrite("size", &character::size,
				"The size of the character.")
			.def_readwrite("bearing", &character::bearing,
				"The bearing, represented as an instance of ivec2. The bearing is an offset from the baseline to the top-left corner of the character.")
			.def_readwrite("advance", &character::advance,
				"The advance value represents how far to move the cursor horizontally after rendering this character.");

	using font = hgui::kernel::Font;
	py::class_<font, std::shared_ptr<font>>(hgui, "Font",
				"The Font class is responsible for managing fonts in your application. It provides the ability to load and use fonts from a specified font file.")
			.def(py::init<std::string>(), "font_path"_a,
				"Constructs a Font object, specifying the file path of the font to be loaded.")
			.def("get_char", &font::get_char, "character"_a, "size"_a,
				"Retrieves a Character struct for the specified character and font size.")
			.def("get_printable_characters", &font::get_printable_characters, "size"_a,
				"Retrieves all the printable characters that are available in the font.")
			.def("load_font", &font::load_font, "size"_a,
				"Loads the font for a specific size. The loaded font can be accessed using the get_char function.")
			.def("is_load", &font::is_load, "size"_a,
				"Checks if the font for a specific size is loaded and ready for use.");
}
