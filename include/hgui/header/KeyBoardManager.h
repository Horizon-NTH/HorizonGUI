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
			bool operator()(const std::variant<std::pair<keys, actions>, std::pair<std::vector<keys>, actions>>& leftSide,
			                const std::variant<std::pair<keys, actions>, std::pair<std::vector<keys>, actions>>& rightSide) const;
		};
	}

	typedef std::pair<keys, actions> KeyBoardAction;
	typedef std::pair<std::vector<keys>, actions> KeyBoardCombinationAction;

	class KeyBoardManager
	{
		friend class Renderer;
		friend class WindowManager;

	public:
		KeyBoardManager() = delete;
		~KeyBoardManager() = delete;
		KeyBoardManager(const KeyBoardManager& bufferManager) = delete;
		KeyBoardManager(KeyBoardManager&& bufferManager) = delete;

		KeyBoardManager& operator=(const KeyBoardManager& bufferManager) = delete;
		KeyBoardManager& operator=(KeyBoardManager&& bufferManager) = delete;

		static void bind(const std::variant<std::pair<keys, actions>, std::pair<std::vector<keys>, actions>>& action,
		                 const std::function<void()>& function);
		[[nodiscard]] static bool is_bind(const std::variant<std::pair<keys, actions>, std::pair<std::vector<keys>, actions>>& action);
		static void unbind(const std::variant<std::pair<keys, actions>, std::pair<std::vector<keys>, actions>>& action);
		static void bind_key_callback(const std::variant<std::function<void()>, std::function<void(keys, actions)>>& function);

	private:
		static void process();
		static void input(GLFWwindow* window, int key, int scan, int action, int mods);

		static std::map<std::variant<std::pair<keys, actions>, std::pair<std::vector<keys>, actions>>, std::pair<
			                Timer, std::function<void()>>, kernel::VariantKeyComparator> m_keys;
		static std::variant<std::function<void()>, std::function<void(keys, actions)>> m_keyCallback;

		friend void kernel::resources_cleaner();
	};
}
