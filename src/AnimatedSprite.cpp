#include "../include/hgui/header/AnimatedSprite.h"
#include "../include/hgui/header/TextureManager.h"
#include "../include/hgui/header/TaskManager.h"
#include "../include/hgui/header/GIF.h"

hgui::kernel::AnimatedSprite::AnimatedSprite(const std::shared_ptr<Shader>& shader, const std::shared_ptr<GIF>& gif, const size& size, const point& position, const color& color, const float rotation) :
	Sprite(shader, nullptr, size, position, color, rotation),
	m_gif(gif),
	m_frameRendered(1u),
	m_loop(false)
{
}

const std::shared_ptr<hgui::kernel::GIF>& hgui::kernel::AnimatedSprite::get_gif() const
{
	return m_gif;
}

void hgui::kernel::AnimatedSprite::set_gif(const std::shared_ptr<GIF>& gif)
{
	m_gif = gif;
}

void hgui::kernel::AnimatedSprite::play()
{
	display();
}

void hgui::kernel::AnimatedSprite::pause()
{
	if (TaskManager::is_program(m_taskID))
	{
		TaskManager::deprogram(m_taskID);
	}
}

void hgui::kernel::AnimatedSprite::stop()
{
	if (TaskManager::is_program(m_taskID))
	{
		TaskManager::deprogram(m_taskID);
	}
	m_frameRendered = 1u;
}

void hgui::kernel::AnimatedSprite::loop()
{
	m_loop = true;
	play();
}

void hgui::kernel::AnimatedSprite::stop_loop()
{
	m_loop = false;
}

bool hgui::kernel::AnimatedSprite::is_playing() const
{
	return TaskManager::is_program(m_taskID);
}

bool hgui::kernel::AnimatedSprite::is_looping() const
{
	return m_loop;
}

void hgui::kernel::AnimatedSprite::display()
{
	const auto& [size, framesCount, channel, pixels, ptr] = m_gif->get_data();
	const auto [image, delay] = m_gif->get_frame(m_frameRendered++);
	Sprite::set_texture(TextureManager::create(image));
	if (m_frameRendered <= framesCount)
	{
		m_taskID = TaskManager::program(delay, [this] { display(); });
	}
	else
	{
		m_frameRendered = 1u;
		if (m_loop)
		{
			m_taskID = TaskManager::program(delay, [this] { display(); });
		}
	}
}
