#include "Include.h"
#include "Application.h"

int main(void)
{
	try
	{
		Application run;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
	return 0;
}