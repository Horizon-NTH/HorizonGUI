#include <hgui/header/Tools.h>

void hgui::after(const std::chrono::milliseconds& delay, const std::function<void()>& function)
{
	hgui::TaskManager::program(delay, function);
}

std::shared_ptr<hgui::kernel::Image> hgui::image_loader(const std::string& imagePath)
{
	return std::make_shared<hgui::kernel::Image>(imagePath);
}

std::string hgui::file_reader(const std::string& filePath)
{
	std::ifstream istream(filePath);
	if (istream.is_open())
	{
		std::stringstream sstream;
		sstream << istream.rdbuf();
		istream.close();
		return sstream.str();
	}
	else
	{
		throw std::runtime_error(("ERROR WHILE LOADING FILE :: " + filePath).c_str());
	}
}

bool hgui::random(const double chances)
{
	static bool firstTime = true;
	if (firstTime)
	{
		std::srand(static_cast<unsigned int>(std::time(nullptr)));
		firstTime = false;
	}
	return static_cast<double>(std::rand()) / RAND_MAX <= chances;
}

std::string hgui::get_unique_id()
{
	static unsigned long long id = 0;
	std::stringstream newID;
	newID << "HGUI_UNIQUE_ID_" << id++;
	return newID.str();
}
