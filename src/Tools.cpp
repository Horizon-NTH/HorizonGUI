#include <hgui/header/Tools.h>

void hgui::after(const std::chrono::milliseconds& delay, const std::function<void()>& function)
{
	hgui::TaskManager::program(delay, function);
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
