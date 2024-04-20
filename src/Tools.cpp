#include "../include/hgui/header/Tools.h"
#include "../include/hgui/header/TaskManager.h"
#include "../include/hgui/header/Image.h"
#include "../include/hgui/header/Audio.h"
#include "../include/hgui/header/GIF.h"
#include "../include/hgui/header/Renderer.h"

void hgui::after(const std::chrono::milliseconds& delay, const std::function<void()>& function)
{
	TaskManager::program(delay, function);
}

std::shared_ptr<hgui::kernel::Image> hgui::image_loader(const std::string& imagePath)
{
	return std::make_shared<kernel::Image>(imagePath);
}

std::shared_ptr<hgui::kernel::GIF> hgui::gif_loader(const std::string& gifPath)
{
	return std::make_shared<kernel::GIF>(gifPath);
}

std::shared_ptr<hgui::kernel::Audio> hgui::audio_loader(const std::string& audioPath)
{
	return std::make_shared<kernel::Audio>(audioPath);
}

std::string hgui::file_reader(const std::string& filePath)
{
	if (std::ifstream istream(filePath); istream.is_open())
	{
		std::stringstream sstream;
		sstream << istream.rdbuf();
		istream.close();
		return sstream.str();
	}
	throw std::runtime_error(("ERROR WHILE LOADING FILE :: " + filePath).c_str());
}

bool hgui::random(const double chances)
{
	const double probability = std::clamp(chances, 0., 1.);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::bernoulli_distribution distribution(probability);
	return distribution(gen);
}

std::string hgui::get_unique_id()
{
	static unsigned long long id = 0;
	std::stringstream newID;
	newID << "HGUI_UNIQUE_ID_" << id++;
	return newID.str();
}

double hgui::get_delta_time()
{
	return Renderer::m_deltaTime;
}
