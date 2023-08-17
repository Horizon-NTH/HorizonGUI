#pragma once

#include "Include.h"
#include "Define.h"
#include "Timer.h"

namespace hgui
{
	namespace kernel
	{
		struct VariantKeyComparator
		{
			bool operator()(const std::variant<std::pair<keys, actions>, std::pair<std::vector<keys>, actions>>& leftSide, const std::variant<std::pair<keys, actions>, std::pair<std::vector<keys>, actions>>& rightSide) const;
		};

		void resources_cleaner();
	}

	typedef std::pair<keys, actions> KeyBoardAction;
	typedef std::pair<std::vector<keys>, actions> KeyBoardCombinationAction;

	class KeyBoardManager
	{
		friend class RenderManager;
		friend class WindowManager;

	public:
		static void bind(const std::variant<std::pair<keys, actions>, std::pair<std::vector<keys>, actions>>& action, const std::function<void()>& function);
		static void unbind(const std::variant<std::pair<keys, actions>, std::pair<std::vector<keys>, actions>>& action);
		static void bind_keycallback(const std::variant<std::function<void()>, std::function<void(keys, actions)>>& function);

	private:
		KeyBoardManager() = delete;

		static void process();
		static void input(GLFWwindow* window, int key, int scancode, int action, int mods);

		static std::map<std::variant<std::pair<keys, actions>, std::pair<std::vector<keys>, actions>>, std::pair<Timer, std::function<void()>>, kernel::VariantKeyComparator> m_keys;
		static std::variant<std::function<void()>, std::function<void(keys, actions)>> m_keyCallback;

		friend void kernel::resources_cleaner();
	};
}

