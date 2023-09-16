#include <hgui/header/TextureManager.h>

std::map<std::string, std::shared_ptr<hgui::kernel::Texture>> hgui::TextureManager::m_textures;

std::shared_ptr<hgui::kernel::Texture>& hgui::TextureManager::create(const std::string& textureID, const std::shared_ptr<kernel::Image>& image)
{
    if (m_textures.find(textureID) == m_textures.end())
    {
        m_textures[textureID] = std::make_shared<kernel::Texture>(image);
        return m_textures[textureID];
    }
    else
    {
        throw std::runtime_error(("THERE IS ALREADY A TEXTURE WITH THE ID : " + textureID).c_str());
    }
}

std::shared_ptr<hgui::kernel::Texture>& hgui::TextureManager::get(const std::string& textureID)
{
    if (m_textures.find(textureID) != m_textures.end())
    {
        return m_textures[textureID];
    }
    else
    {
        throw std::runtime_error(("THERE IS NO TEXTURE WITH THE ID : " + textureID).c_str());
    }
}

void hgui::TextureManager::destroy(const std::initializer_list<std::string>& texturesID)
{
    if (texturesID.size())
    {
        for (const std::string& textureID : texturesID)
        {
            m_textures.erase(textureID);
        }
    }
    else
    {
        m_textures.clear();
    }
}
