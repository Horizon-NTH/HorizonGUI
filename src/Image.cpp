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
	auto data = stbi_load(filePath.c_str(), &width, &height, &channel, 0);
	if (!data)
	{
		throw std::runtime_error("ERROR WHILE LOADING IMAGE : " + filePath);
	}
	m_data.size = Size<unsigned>(width, height);
	switch (channel)
	{
		case 1:
			m_data.channel = channels::GREYSCALE;
			break;
		case 2:
			{
				m_data.channel = channels::GREYSCALE_ALPHA;
				const auto newData = new stbi_uc[width * height * 4];
				for (int i = 0; i < width * height; ++i)
				{
					newData[i * 4] = data[i * 2];          // Red
					newData[i * 4 + 1] = data[i * 2];      // Green
					newData[i * 4 + 2] = data[i * 2];      // Blue
					newData[i * 4 + 3] = data[i * 2 + 1];  // Alpha
				}
				stbi_image_free(data);
				data = newData;
			}
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
	m_data.pixels = ImageData::pointer(data,
		[](unsigned char* image)
			{
				stbi_image_free(image);
			}
	);
}

hgui::size hgui::kernel::Image::get_size() const
{
	return static_cast<size>(m_data.size);
}

void hgui::kernel::Image::save_image(const std::string& filePath) const
{
	int channel = 3;
	const stbi_uc* data = m_data.pixels.get();
	[[maybe_unused]] std::unique_ptr<stbi_uc[]> newData;
	switch (m_data.channel)
	{
		case channels::GREYSCALE:
			channel = 1;
			break;
		case channels::GREYSCALE_ALPHA:
			channel = 2;
			newData = std::make_unique<stbi_uc[]>(m_data.size.width * m_data.size.height * 2);
			for (unsigned i = 0; i < m_data.size.width * m_data.size.height; ++i)
			{
				newData[i * 2] = data[i * 4];
				newData[i * 2 + 1] = data[i * 4 + 3];
			}
			data = newData.get();
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
	if (!stbi_write_png(filePath.c_str(), static_cast<int>(m_data.size.width), static_cast<int>(m_data.size.height), channel, data, static_cast<int>(m_data.size.width) * channel))
	{
		throw std::runtime_error("ERROR WHILE SAVING IMAGE : " + filePath);
	}
}
