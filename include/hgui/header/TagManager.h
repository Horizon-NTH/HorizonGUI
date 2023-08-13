#pragma once

#include "Include.h"

namespace hgui
{
	namespace kernel
	{
		void resources_cleaner();
	}

	class TagManager
	{
	public:
		static std::string create_tag(const std::string& newTag);
		static const std::vector<std::string>& get_tags();
		static const std::string& get_current_tag();
		static void set_current_tag(const std::string& tag);

	private:
		TagManager();

		static std::string m_currentTag;
		static std::vector<std::string> m_tags;

		friend void kernel::resources_cleaner();
	};
}