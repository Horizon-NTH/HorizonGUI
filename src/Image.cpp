#include <hgui/header/Image.h>

#include <utility>

hgui::kernel::Image::Image(std::string  imagePath) :
	m_path(std::move(imagePath)),
	m_data(),
	m_autoLoaded(true)
{
	load_image();
}

hgui::kernel::Image::Image(std::string  imagePath, const ImageData& data) :
	m_path(std::move(imagePath)),
	m_data(data),
	m_autoLoaded(false)
{
}

hgui::kernel::Image::~Image()
{
	if (m_autoLoaded)
	{
		stbi_image_free(m_data.pixels);
	}
}

const hgui::kernel::ImageData& hgui::kernel::Image::get_data() const
{
	return m_data;
}

void hgui::kernel::Image::set_data(const ImageData& newData)
{
	if (m_autoLoaded)
	{
		stbi_image_free(m_data.pixels);
	}
	m_data = newData;
	m_autoLoaded = false;
}

hgui::size hgui::kernel::Image::get_size() const
{
	return {m_data.width, m_data.height};
}

void hgui::kernel::Image::load_image()
{
	int channel;
	m_data.pixels = stbi_load(m_path.c_str(), reinterpret_cast<int*>(&m_data.width), reinterpret_cast<int*>(&m_data.height), &channel, 0);
	switch (channel)
	{
	case 1:
		m_data.channel = channels::GREYSCALE;
		break;
	case 2:
		m_data.channel = channels::GREYSCALE_ALPHA;
		break;
	case 3:
		m_data.channel = channels::RGB;
		break;
	case 4:
		m_data.channel = channels::RGBA;
		break;
	default:
		break;
	}
	if (!m_data.pixels)
	{
		throw std::runtime_error(("ERROR WHILE LOADING IMAGE : " + m_path).c_str());
	}
}

void hgui::kernel::Image::save_image()
{
	auto function = [this](const size& size)
		{
			std::vector<unsigned char> pixels(static_cast<int>(this->m_data.channel)
				* static_cast<int>(size.width) * static_cast<int>(size.height));
			glReadPixels(0, 0, 1920, 1080, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
			stbi_write_png(this->m_path.c_str(), 1920, 1080, 4, pixels.data(), 1920 * 4);
		};
	int width, height;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);
	function(hgui::size(width, height));
}