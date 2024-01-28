#include "../include/hgui/header/Image.h"

hgui::kernel::Image::Image(const std::string& imagePath)
{
	load_image(imagePath);
}

hgui::kernel::Image::Image(ImageData&& data) :
	m_data(std::move(data))
{
}

hgui::kernel::Image& hgui::kernel::Image::operator=(ImageData&& image) noexcept
{
	m_data = std::move(image);
	return *this;
}

const hgui::kernel::ImageData& hgui::kernel::Image::get_data() const
{
	return m_data;
}

void hgui::kernel::Image::set_data(ImageData&& newData)
{
	m_data = std::move(newData);
}

void hgui::kernel::Image::load_image(const std::string& filePath)
{
	int channel, width, height;
	m_data.pixels = ImageData::pointer(
		stbi_load(filePath.c_str(), &width, &height, &channel, 0),
		[](unsigned char* data)
			{
				stbi_image_free(data);
			}
	);
	m_data.size = Size<unsigned>(width, height);
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
			m_data.channel = channels::UNKNOW;
			break;
	}
	if (!m_data.pixels)
	{
		throw std::runtime_error("ERROR WHILE LOADING IMAGE : " + filePath);
	}
}

hgui::size hgui::kernel::Image::get_size() const
{
	return static_cast<size>(m_data.size);
}

void hgui::kernel::Image::save_image(const std::string& filePath) const
{
	int channel = 3;
	switch (m_data.channel)
	{
		case channels::GREYSCALE:
			channel = 1;
			break;
		case channels::GREYSCALE_ALPHA:
			channel = 2;
			break;
		case channels::RGB:
			channel = 3;
			break;
		case channels::RGBA:
			channel = 4;
			break;
		default:
			break;
	}
	if (!stbi_write_png(filePath.c_str(), static_cast<int>(m_data.size.width), static_cast<int>(m_data.size.height), channel, m_data.pixels.get(), static_cast<int>(m_data.size.width) * channel))
	{
		throw std::runtime_error("ERROR WHILE SAVING IMAGE : " + filePath);
	}
}
