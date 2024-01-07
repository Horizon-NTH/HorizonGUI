#include "../include/hgui/header/GIF.h"
#include "../include/hgui/header/Image.h"

hgui::kernel::GIF::GIF(const std::string& gifPath) :
	m_data()
{
	load_gif(gifPath);
}

hgui::kernel::GIF::GIF(GIFData&& data) :
	m_data(std::move(data))
{
}

hgui::kernel::GIF& hgui::kernel::GIF::operator=(GIFData&& data) noexcept
{
	m_data = std::move(data);
	return *this;
}

hgui::kernel::GIFData& hgui::kernel::GIF::get_data()
{
	return m_data;
}

hgui::size hgui::kernel::GIF::get_size() const
{
	return {m_data.width, m_data.height};
}

hgui::kernel::GIF::Frame hgui::kernel::GIF::get_frame(unsigned frameNumber) const
{
	frameNumber = std::clamp(frameNumber - 1, 0u, m_data.framesCount - 1u);
	const auto& [pixels, delay] = m_data.pixels.at(frameNumber);
	ImageData data =
			{
				.width = m_data.width,
				.height = m_data.height,
				.channel = m_data.channel,
				.pixels = ImageData::pointer(pixels, [](unsigned char*)
					{
					})
			};
	return {std::make_shared<Image>(std::move(data)), delay};
}

void hgui::kernel::GIF::set_data(GIFData&& newData)
{
	m_data = std::move(newData);
}

void hgui::kernel::GIF::set_delay(const GIFData::delay& delay, unsigned frameNumber)
{
	frameNumber = std::clamp(frameNumber - 1, 0u, m_data.framesCount - 1u);
	m_data.pixels.at(frameNumber).second = delay;
}

void hgui::kernel::GIF::set_delay(const std::vector<GIFData::delay>& delays)
{
	if (delays.size() != m_data.framesCount)
	{
		throw std::runtime_error("YOU MUST PROVIDE A DELAY FOR EACH FRAME");
	}
	for (int i = 0; i < static_cast<int>(m_data.framesCount); i++)
	{
		m_data.pixels.at(i).second = delays.at(i);
	}
}

void hgui::kernel::GIF::load_gif(const std::string& gifPath)
{
	const auto buffer = read_binary_file(gifPath);

	int* delays = nullptr;
	int channel = 0;
	m_data.ptr = GIFData::pointer(stbi_load_gif_from_memory(buffer.data(), static_cast<int>(buffer.size()), &delays,
			reinterpret_cast<int*>(&m_data.width), reinterpret_cast<int*>(&m_data.height), reinterpret_cast<int*>(&m_data.framesCount), &channel, 0), [](stbi_uc* data)
			{
				stbi_image_free(data);
			});
	if (!m_data.ptr)
	{
		throw std::runtime_error("FAILED TO LOAD FILE : " + gifPath);
	}
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
	const int stride = static_cast<int>(m_data.width) * static_cast<int>(m_data.height) * channel;
	for (int i = 0; i < static_cast<int>(m_data.framesCount); i++)
	{
		m_data.pixels.emplace_back(m_data.ptr.get() + i * stride, GIFData::delay(delays[i]));
	}
	stbi_image_free(delays);
}

std::vector<stbi_uc> hgui::kernel::GIF::read_binary_file(const std::string& filePath)
{
	std::ifstream file(filePath, std::ios::binary);
	if (!file.is_open())
	{
		throw std::runtime_error("FAILED TO OPEN FILE : " + filePath);
	}
	file.seekg(0, std::ios::end);
	const std::streampos fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	std::vector<stbi_uc> buffer(fileSize);
	file.read(reinterpret_cast<char*>(buffer.data()), fileSize);

	return std::move(buffer);
}
