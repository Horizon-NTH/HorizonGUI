#pragma once

#include "Include.h"
#include "WindowManager.h"
#include "Timer.h"

namespace hgui
{
	namespace key
	{
		enum KeyBoardKey
		{
			UNKNOWN = -1,
			ESCAPE = 256,
			F1 = 290,
			F2 = 291,
			F3 = 292,
			F4 = 293,
			F5 = 294,
			F6 = 295,
			F7 = 296,
			F8 = 297,
			F9 = 298,
			F10 = 299,
			F11 = 300,
			F12 = 301,
			PRINT_SCREEN = 283,
			INSERT = 260,
			DELETE = 261,
			SQUARE = 96,
			AMPERSAND = 49,
			E_WITH_ACUTE = 50,
			QUOTATION = 51,
			APOSTROPHE = 52,
			LEFT_BRACKET = 53,
			MINUS = 54,
			E_WITH_GRAVE = 55,
			UNDERSCORE = 56,
			C_WITH_CEDILLA = 57,
			A_WITH_GRAVE = 48,
			RIGHT_BRACKET = 45,
			EQUAL = 61,
			BACKSPACE = 259,
			TAB = 258,
			A = 81,
			Z = 87,
			E = 69,
			R = 82,
			T = 84,
			Y = 89,
			U = 85,
			I = 73,
			O = 79,
			P = 80,
			CIRCUMFLEX = 91,
			DOLLAR = 93,
			ASTERISK = 92,
			CAPS_LOCK = 280,
			Q = 65,
			S = 83,
			D = 68,
			F = 70,
			G = 71,
			H = 72,
			J = 74,
			K = 75,
			L = 76,
			M = 59,
			U_WITH_GRAVE = 39,
			ENTER = 257,
			LEFT_SHIFT = 340,
			SIGN = 162,
			W = 90,
			X = 88,
			C = 67,
			V = 86,
			B = 66,
			N = 78,
			COMMA = 77,
			SEMILICON = 44,
			COLON = 46,
			EXCLMATION_MARK = 47,
			RIGHT_SHIFT = 344,
			LEFT_CONTROL = 341,
			WINDOWS = 343,
			LEFT_ALT = 342,
			SPACE = 32,
			RIGHT_ALT = 346,
			RIGHT_CONTROL = 345,
			RIGHT = 262,
			LEFT = 263,
			DOWN = 264,
			UP = 265,
			PAGE_UP = 266,
			PAGE_DOWN = 267,
			HOME = 268,
			END = 269,
			PAUSE = 284,
			SCROLL_LOCK = 281,
			NUM_LOCK = 282,
			KP_0 = 320,
			KP_1 = 321,
			KP_2 = 322,
			KP_3 = 323,
			KP_4 = 324,
			KP_5 = 325,
			KP_6 = 326,
			KP_7 = 327,
			KP_8 = 328,
			KP_9 = 329,
			KP_DECIMAL = 330,
			KP_DIVIDE = 331,
			KP_MULTIPLY = 332,
			KP_SUBTRACT = 333,
			KP_ADD = 334,
			KP_ENTER = 335,
			KP_EQUAL = 336
		};

		enum Action
		{
			PRESS = 1,
			REPEAT = 2,
			RELEASE = 0
		};
	}
	namespace kernel
	{
		void resources_cleaner();
	}

	namespace kernel
	{
		struct VariantKeyComparator
		{
			bool operator()(const std::variant<std::pair<key::KeyBoardKey, key::Action>, std::pair<std::vector<key::KeyBoardKey>, key::Action>>& leftSide, const std::variant<std::pair<key::KeyBoardKey, key::Action>, std::pair<std::vector<key::KeyBoardKey>, key::Action>>& rightSide) const;
		};
	}

	typedef std::pair<key::KeyBoardKey, key::Action> KeyBoardAction;
	typedef std::pair<std::vector<key::KeyBoardKey>, key::Action> KeyBoardCombinationAction;

	class KeyBoardManager
	{
		friend class RenderManager;

	public:
		static void bind(std::variant<std::pair<key::KeyBoardKey, key::Action>, std::pair<std::vector<key::KeyBoardKey>, key::Action>> action, std::function<void()> function);
		static void unbind(std::variant<std::pair<key::KeyBoardKey, key::Action>, std::pair<std::vector<key::KeyBoardKey>, key::Action>> action);

	private:
		KeyBoardManager();

		static void process();

		static std::map<std::variant<std::pair<key::KeyBoardKey, key::Action>, std::pair<std::vector<key::KeyBoardKey>, key::Action>>, std::pair<Timer, std::function<void()>>, kernel::VariantKeyComparator> m_keys;
		
		friend void kernel::resources_cleaner();
	};
}

