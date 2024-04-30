#pragma once

#include "Include.h"
#include "Define.h"

namespace hgui
{
	class Timer;
	class TextInputManager;

	namespace kernel
	{
		struct VariantKeyComparator
		{
			bool operator()(const std::variant<std::pair<keys, actions>, std::pair<std::vector<keys>, actions>>& leftSide, const std::variant<std::pair<keys, actions>, std::pair<std::vector<keys>, actions>>& rightSide) const;
		};
	}

	typedef std::pair<keys, actions> KeyBoardAction;
	typedef std::pair<std::vector<keys>, actions> KeyBoardCombinationAction;

	class KeyBoardManager
	{
		friend class Renderer;
		friend class WindowManager;
		friend class TextInputManager;

	public:
		KeyBoardManager() = delete;
		~KeyBoardManager() = delete;
		KeyBoardManager(const KeyBoardManager& keyboardManage) = delete;
		KeyBoardManager(KeyBoardManager&& keyboardManage) = delete;

		KeyBoardManager& operator=(const KeyBoardManager& keyboardManage) = delete;
		KeyBoardManager& operator=(KeyBoardManager&& keyboardManage) = delete;

		static void bind(const std::variant<std::pair<keys, actions>, std::pair<std::vector<keys>, actions>>& action, const std::function<void()>& function);
		[[nodiscard]] static bool is_bind(const std::variant<std::pair<keys, actions>, std::pair<std::vector<keys>, actions>>& action);
		[[nodiscard]] static const std::function<void()>& get_bind(const std::variant<std::pair<keys, actions>, std::pair<std::vector<keys>, actions>>& action);
		static void unbind(const std::variant<std::pair<keys, actions>, std::pair<std::vector<keys>, actions>>& action);
		static void bind_key_callback(const std::variant<std::function<void()>, std::function<void(keys, actions)>>& function);

	private:
		static void process();
		static void input(GLFWwindow* window, int key, int scan, int action, int mods);
		static void add_bind(const std::variant<std::pair<keys, actions>, std::pair<std::vector<keys>, actions>>& action, const std::function<void()>& function);

		static inline std::map<std::variant<std::pair<keys, actions>, std::pair<std::vector<keys>, actions>>, std::pair<std::shared_ptr<Timer>, std::function<void()>>, kernel::VariantKeyComparator> m_keys;
		static inline std::vector<std::pair<std::variant<std::pair<keys, actions>, std::pair<std::vector<keys>, actions>>, std::pair<std::shared_ptr<Timer>, std::function<void()>>>> m_apiBinds;
		static inline std::variant<std::function<void()>, std::function<void(keys, actions)>> m_keyCallback;

		friend void kernel::resources_cleaner();
	};
}
