#include <hgui/header/Tools.h>

void hgui::after(std::chrono::milliseconds delay, std::function<void()> function)
{
	std::thread thread([delay, function]() { std::this_thread::sleep_for(delay); function(); });
	thread.detach();
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
