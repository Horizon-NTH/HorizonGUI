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
		TagManager() = delete;
		~TagManager() = delete;
		TagManager(const TagManager& tagManager) = delete;
		TagManager(TagManager&& tagManager) = delete;

		TagManager& operator=(const TagManager& tagManager) = delete;
		TagManager& operator=(TagManager&& tagManager) = delete;

		static std::string create_tag(const std::string& newTag);
		[[nodiscard]] static const std::vector<std::string>& get_tags();
		[[nodiscard]] static const std::string& get_current_tag();
		static void set_current_tag(const std::string& tag);

	private:
		static inline std::string m_currentTag;
		static inline std::vector<std::string> m_tags;

		friend void kernel::resources_cleaner();
	};
}
