#pragma once

#include "Include.h"
#include "Maths.hpp"

namespace hgui
{
	namespace kernel
	{
		class Monitor
		{
		public:
			Monitor(GLFWmonitor* monitorPTR);

			GLFWmonitor* get_monitorPTR() const;
			const size& get_size() const;
			std::string get_name() const;
			const point& get_position() const;

		private:
			GLFWmonitor* m_monitorPTR;
			size m_size;
			point m_position;
			std::string m_name;
		};
	}
}

