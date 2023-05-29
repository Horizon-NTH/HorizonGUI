#include <hgui/header/Image.h>

hgui::kernel::Image::Image(const std::string& imagePath) :
    m_path(imagePath)
{
    load_image();
}

hgui::kernel::Image::Image(const std::string& imagePath, const ImageData& data) :
    m_path(imagePath), m_data(data)
{
}

hgui::kernel::Image::~Image()
{
    stbi_image_free(m_data.pixels);
}

const hgui::kernel::ImageData& hgui::kernel::Image::get_data() const
{
    return m_data;
}

void hgui::kernel::Image::set_data(const ImageData& newData)
{
    m_data = newData;
}

void hgui::kernel::Image::load_image()
{
    int channel;
    m_data.pixels = stbi_load(m_path.c_str(), &m_data.width, &m_data.height, &channel, NULL);
    switch (channel)
    {
    case 1: m_data.channel = GRAYSCALE; break;
    case 2: m_data.channel = GRAYSCALE_ALPHA; break;
    case 3: m_data.channel = RGB; break;
    case 4: m_data.channel = RGBA; break;
    default: break;
    }
    if (!m_data.pixels)
    {
        throw std::exception(("ERROR WHILE LOADING IMAGE : " + m_path).c_str());
    }
}

void hgui::kernel::Image::save_image()
{
    auto function = [this](glm::vec2 size)
    {
        std::vector<unsigned char> pixels(static_cast<int>(this->m_data.channel) * static_cast<int>(size.x) * static_cast<int>(size.y));
        glReadPixels(0, 0, 1920, 1080, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
        stbi_write_png(this->m_path.c_str(), 1920, 1080, 4, pixels.data(), 1920 * 4);
    };
    std::thread thread(function, MonitorManager::get_primary_monitor()->get_size());
}

const std::shared_ptr<hgui::kernel::Image> hgui::image_loader(const std::string& imagePath)
{
    return std::make_shared<hgui::kernel::Image>(imagePath);
}
