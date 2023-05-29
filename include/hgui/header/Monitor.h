#pragma once

#include "Include.h"

namespace hgui
{
	namespace kernel
	{
		class Monitor
		{
		public:
			Monitor(GLFWmonitor* monitorPTR);

			GLFWmonitor* get_monitorPTR() const;
			glm::vec2 get_size() const;
			std::string get_name() const;
			glm::vec2 get_position() const;

		private:
			GLFWmonitor* m_monitorPTR;
			glm::vec2 m_size;
			glm::vec2 m_position;
			std::string m_name;
		};
	}
}

