#pragma once
//TAG
#define HGUI_TAG_MAIN "HGUI_TAG_MAIN"
//COLOR
#define HGUI_COLOR_BLACK hgui::color(0.f)
#define HGUI_COLOR_WHITE hgui::color(1.f)
#define HGUI_COLOR_RED hgui::color(1.f, 0.f, 0.f)
#define HGUI_COLOR_GREEN hgui::color(0.f, 1.f, 0.f)
#define HGUI_COLOR_BLUE hgui::color(0.f, 0.f, 1.f)
//PRECISION
#ifndef HGUI_PRECISION
#define HGUI_PRECISION float
#endif // !HGUI_PRECISION

//ENUMS
namespace hgui
{
	enum class keys
	{
		UNKNOWN          = -1,
		ESCAPE           = 256,
		F1               = 290,
		F2               = 291,
		F3               = 292,
		F4               = 293,
		F5               = 294,
		F6               = 295,
		F7               = 296,
		F8               = 297,
		F9               = 298,
		F10              = 299,
		F11              = 300,
		F12              = 301,
		PRINT_SCREEN     = 283,
		INSERT           = 260,
		BACKSPACE        = 261,
		SQUARE           = 96,
		AMPERSAND        = 49,
		E_WITH_ACUTE     = 50,
		QUOTATION        = 51,
		APOSTROPHE       = 52,
		LEFT_BRACKET     = 53,
		MINUS            = 54,
		E_WITH_GRAVE     = 55,
		UNDERSCORE       = 56,
		C_WITH_CEDILLA   = 57,
		A_WITH_GRAVE     = 48,
		RIGHT_BRACKET    = 45,
		EQUAL            = 61,
		REMOVE           = 259,
		TAB              = 258,
		A                = 81,
		Z                = 87,
		E                = 69,
		R                = 82,
		T                = 84,
		Y                = 89,
		U                = 85,
		I                = 73,
		O                = 79,
		P                = 80,
		CIRCUMFLEX       = 91,
		DOLLAR           = 93,
		ASTERISK         = 92,
		CAPS_LOCK        = 280,
		Q                = 65,
		S                = 83,
		D                = 68,
		F                = 70,
		G                = 71,
		H                = 72,
		J                = 74,
		K                = 75,
		L                = 76,
		M                = 59,
		U_WITH_GRAVE     = 39,
		ENTER            = 257,
		LEFT_SHIFT       = 340,
		SIGN             = 162,
		W                = 90,
		X                = 88,
		C                = 67,
		V                = 86,
		B                = 66,
		N                = 78,
		COMMA            = 77,
		SEMICOLON        = 44,
		COLON            = 46,
		EXCLAMATION_MARK = 47,
		RIGHT_SHIFT      = 344,
		LEFT_CONTROL     = 341,
		WINDOWS          = 343,
		LEFT_ALT         = 342,
		SPACE            = 32,
		RIGHT_ALT        = 346,
		RIGHT_CONTROL    = 345,
		RIGHT            = 262,
		LEFT             = 263,
		DOWN             = 264,
		UP               = 265,
		PAGE_UP          = 266,
		PAGE_DOWN        = 267,
		HOME             = 268,
		END              = 269,
		PAUSE            = 284,
		SCROLL_LOCK      = 281,
		NUM_LOCK         = 282,
		KP_0             = 320,
		KP_1             = 321,
		KP_2             = 322,
		KP_3             = 323,
		KP_4             = 324,
		KP_5             = 325,
		KP_6             = 326,
		KP_7             = 327,
		KP_8             = 328,
		KP_9             = 329,
		KP_DECIMAL       = 330,
		KP_DIVIDE        = 331,
		KP_MULTIPLY      = 332,
		KP_SUBTRACT      = 333,
		KP_ADD           = 334,
		KP_ENTER         = 335,
		KP_EQUAL         = 336
	};

	enum class buttons
	{
		LEFT     = 0,
		RIGHT    = 1,
		MIDDLE   = 2,
		BUTTON_3 = 3,
		BUTTON_4 = 4,
		BUTTON_5 = 5,
		BUTTON_6 = 6,
		BUTTON_7 = 7,
		BUTTON_8 = 8
	};

	enum class inputs
	{
		OVER,
		NOVER,
		MOTION,
		SCROLL,
		SCROLL_UP,
		SCROLL_DOWN
	};

	enum class actions
	{
		PRESS   = 1,
		REPEAT  = 2,
		RELEASE = 0
	};

	enum class effects
	{
		CLASSIC,
		BLURRED,
		NEGATIVE
	};

	enum class options
	{
		RESIZABLE        = 0x00020003,
		VISIBLE          = 0x00020004,
		DECORATED        = 0x00020005,
		FOCUSED          = 0x00020001,
		AUTO_ICONIFY     = 0x00020006,
		FLOATING         = 0x00020007,
		MAXIMIZED        = 0x00020008,
		CENTER_CURSOR    = 0x00020009,
		FOCUS_ON_SHOW    = 0x0002000C,
		SCALE_TO_MONITOR = 0x0002200C
	};

	enum class channels
	{
		GREYSCALE       = 0x1903,
		GREYSCALE_ALPHA = 0x8227,
		RGB             = 0x1907,
		RGBA            = 0x1908,
		UNKNOW          = 0
	};

	enum class state
	{
		NORMAL = 0,
		HOVER  = 1,
		PRESS  = 2
	};

	enum class cursors
	{
		ARROW     = GLFW_ARROW_CURSOR,
		IBEAM     = GLFW_IBEAM_CURSOR,
		CROSSHAIR = GLFW_CROSSHAIR_CURSOR,
		HAND      = GLFW_POINTING_HAND_CURSOR,
		HRESIZE   = GLFW_RESIZE_EW_CURSOR,
		VRESIZE   = GLFW_RESIZE_NS_CURSOR,
		CUSTOM    = NULL
	};

	enum class reference
	{
		WIDTH,
		HEIGHT,
		BOTH
	};

	namespace kernel
	{
		void resources_cleaner();
	}
}
