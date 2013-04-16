#ifndef _CE_KEYCODE_H_
#define _CE_KEYCODE_H_

//- Centhra Engine -
#include <CE/ScanCode.h>

// Johnny Patterson: I was trying to follow some kind of keycode standard, so I chose to use SDL's keycode values.

namespace ce
{
	#define SCANCODE_MASK (1 << 30)
	#define SCANCODE_TO_KEYCODE(X) (X | SCANCODE_MASK)

	enum KeyCode
	{
		Key_Unknown,

		Key_Backspace = '\b',
		Key_Tab = '\t',
		Key_NewLine = '\n',
		Key_Return = '\r',
		Key_Escape = 27,

		Key_Space = ' ',
		Key_Exclamation,
		Key_Quotation,
		Key_Number,
		Key_Dollar,
		Key_Percent,
		Key_Ampersand,
		Key_Apostrophe,
		Key_ParenthesisLeft,
		Key_ParenthesisRight,
		Key_Asterisk,
		Key_Plus,
		Key_Comma,
		Key_Minus,
		Key_Period,
		Key_Slash,

		Key_0 = '0',
		Key_1,
		Key_2,
		Key_3,
		Key_4,
		Key_5,
		Key_6,
		Key_7,
		Key_8,
		Key_9,

		Key_Colon = ':',
		Key_Semicolon,
		Key_LessThan,
		Key_Equal,
		Key_GreaterThan,
		Key_Question,
		Key_At,

		Key_BracketLeft = '[',
		Key_Backslash,
		Key_BracketRight,
		Key_Caret,
		Key_Underscore,
		Key_Grave,

		Key_A = 'a',
		Key_B,
		Key_C,
		Key_D,
		Key_E,
		Key_F,
		Key_G,
		Key_H,
		Key_I,
		Key_J,
		Key_K,
		Key_L,
		Key_M,
		Key_N,
		Key_O,
		Key_P,
		Key_Q,
		Key_R,
		Key_S,
		Key_T,
		Key_U,
		Key_V,
		Key_W,
		Key_X,
		Key_Y,
		Key_Z,

		Key_CurlyBracketLeft,
		Key_VerticalBar,
		Key_CurlyBracketRight,
		Key_Tilde,
		Key_Delete,

		Key_CapsLock = SCANCODE_TO_KEYCODE(Scan_CapsLock),
		Key_F1 = SCANCODE_TO_KEYCODE(Scan_F1),
		Key_F2 = SCANCODE_TO_KEYCODE(Scan_F2),
		Key_F3 = SCANCODE_TO_KEYCODE(Scan_F3),
		Key_F4 = SCANCODE_TO_KEYCODE(Scan_F4),
		Key_F5 = SCANCODE_TO_KEYCODE(Scan_F5),
		Key_F6 = SCANCODE_TO_KEYCODE(Scan_F6),
		Key_F7 = SCANCODE_TO_KEYCODE(Scan_F7),
		Key_F8 = SCANCODE_TO_KEYCODE(Scan_F8),
		Key_F9 = SCANCODE_TO_KEYCODE(Scan_F9),
		Key_F10 = SCANCODE_TO_KEYCODE(Scan_F10),
		Key_F11 = SCANCODE_TO_KEYCODE(Scan_F11),
		Key_F12 = SCANCODE_TO_KEYCODE(Scan_F12),

		Key_PrintScreen = SCANCODE_TO_KEYCODE(Scan_PrintScreen),
		Key_ScrollLock = SCANCODE_TO_KEYCODE(Scan_ScrollLock),
		Key_Break = SCANCODE_TO_KEYCODE(Scan_Break),
		Key_Pause = SCANCODE_TO_KEYCODE(Scan_Pause),

		Key_Insert = SCANCODE_TO_KEYCODE(Scan_Insert),
		Key_Home = SCANCODE_TO_KEYCODE(Scan_Home),
		Key_PageUp = SCANCODE_TO_KEYCODE(Scan_PageUp),
		Key_End = SCANCODE_TO_KEYCODE(Scan_End),
		Key_PageDown = SCANCODE_TO_KEYCODE(Scan_PageDown),
		Key_Right = SCANCODE_TO_KEYCODE(Scan_Right),
		Key_Left = SCANCODE_TO_KEYCODE(Scan_Left),
		Key_Down = SCANCODE_TO_KEYCODE(Scan_Down),
		Key_Up = SCANCODE_TO_KEYCODE(Scan_Up),

		Key_NumLock = SCANCODE_TO_KEYCODE(Scan_NumLock),
		Key_KP_Slash = SCANCODE_TO_KEYCODE(Scan_KP_Slash),
		Key_KP_Asterisk = SCANCODE_TO_KEYCODE(Scan_KP_Asterisk),
		Key_KP_Minus = SCANCODE_TO_KEYCODE(Scan_KP_Minus),
		Key_KP_Plus = SCANCODE_TO_KEYCODE(Scan_KP_Plus),
		Key_KP_Enter = SCANCODE_TO_KEYCODE(Scan_KP_Enter),

		Key_KP_1 = SCANCODE_TO_KEYCODE(Scan_KP_1),
		Key_KP_2 = SCANCODE_TO_KEYCODE(Scan_KP_2),
		Key_KP_3 = SCANCODE_TO_KEYCODE(Scan_KP_3),
		Key_KP_4 = SCANCODE_TO_KEYCODE(Scan_KP_4),
		Key_KP_5 = SCANCODE_TO_KEYCODE(Scan_KP_5),
		Key_KP_6 = SCANCODE_TO_KEYCODE(Scan_KP_6),
		Key_KP_7 = SCANCODE_TO_KEYCODE(Scan_KP_7),
		Key_KP_8 = SCANCODE_TO_KEYCODE(Scan_KP_8),
		Key_KP_9 = SCANCODE_TO_KEYCODE(Scan_KP_9),
		Key_KP_0 = SCANCODE_TO_KEYCODE(Scan_KP_0),
		Key_KP_Period = SCANCODE_TO_KEYCODE(Scan_KP_Period),
		Key_NUS_Slash = SCANCODE_TO_KEYCODE(Scan_NUS_Slash),

		Key_KP_End = SCANCODE_TO_KEYCODE(Scan_KP_End),
		Key_KP_Down = SCANCODE_TO_KEYCODE(Scan_KP_Down),
		Key_KP_PageDown = SCANCODE_TO_KEYCODE(Scan_KP_PageDown),
		Key_KP_Left = SCANCODE_TO_KEYCODE(Scan_KP_Left),
		Key_KP_Right = SCANCODE_TO_KEYCODE(Scan_KP_Right),
		Key_KP_Home = SCANCODE_TO_KEYCODE(Scan_KP_Home),
		Key_KP_Up = SCANCODE_TO_KEYCODE(Scan_KP_Up),
		Key_KP_PageUp = SCANCODE_TO_KEYCODE(Scan_KP_PageUp),
		Key_KP_Insert = SCANCODE_TO_KEYCODE(Scan_KP_Insert),
		Key_KP_Delete = SCANCODE_TO_KEYCODE(Scan_KP_Delete),

		Key_Application = SCANCODE_TO_KEYCODE(Scan_Application),
		Key_KB_Power = SCANCODE_TO_KEYCODE(Scan_KB_Power),
		Key_KP_Equal = SCANCODE_TO_KEYCODE(Scan_KP_Equal),
		Key_F13 = SCANCODE_TO_KEYCODE(Scan_F13),
		Key_F14 = SCANCODE_TO_KEYCODE(Scan_F14),
		Key_F15 = SCANCODE_TO_KEYCODE(Scan_F15),
		Key_F16 = SCANCODE_TO_KEYCODE(Scan_F16),
		Key_F17 = SCANCODE_TO_KEYCODE(Scan_F17),
		Key_F18 = SCANCODE_TO_KEYCODE(Scan_F18),
		Key_F19 = SCANCODE_TO_KEYCODE(Scan_F19),
		Key_F20 = SCANCODE_TO_KEYCODE(Scan_F20),
		Key_F21 = SCANCODE_TO_KEYCODE(Scan_F21),
		Key_F22 = SCANCODE_TO_KEYCODE(Scan_F22),
		Key_F23 = SCANCODE_TO_KEYCODE(Scan_F23),
		Key_F24 = SCANCODE_TO_KEYCODE(Scan_F24),

		Key_KB_Execute = SCANCODE_TO_KEYCODE(Scan_KB_Execute),
		Key_KB_Help = SCANCODE_TO_KEYCODE(Scan_KB_Help),
		Key_KB_Menu = SCANCODE_TO_KEYCODE(Scan_KB_Menu),
		Key_KB_Select = SCANCODE_TO_KEYCODE(Scan_KB_Select),
		Key_KB_Stop = SCANCODE_TO_KEYCODE(Scan_KB_Stop),
		Key_KB_Again = SCANCODE_TO_KEYCODE(Scan_KB_Again),
		Key_KB_Undo = SCANCODE_TO_KEYCODE(Scan_KB_Undo),
		Key_KB_Cut = SCANCODE_TO_KEYCODE(Scan_KB_Cut),
		Key_KB_Copy = SCANCODE_TO_KEYCODE(Scan_KB_Copy),
		Key_KB_Paste = SCANCODE_TO_KEYCODE(Scan_KB_Paste),
		Key_KB_Find = SCANCODE_TO_KEYCODE(Scan_KB_Find),
		Key_KB_Mute = SCANCODE_TO_KEYCODE(Scan_KB_Mute),
		Key_KB_VolumeUp = SCANCODE_TO_KEYCODE(Scan_KB_VolumeUp),
		Key_KB_VolumeDown = SCANCODE_TO_KEYCODE(Scan_KB_VolumeDown),
		Key_KB_LockingCapsLock = SCANCODE_TO_KEYCODE(Scan_KB_LockingCapsLock),
		Key_KB_LockingNumLock = SCANCODE_TO_KEYCODE(Scan_KB_LockingNumLock),
		Key_KB_LockingScrollLock = SCANCODE_TO_KEYCODE(Scan_KB_LockingScrollLock),
		Key_KP_Comma = SCANCODE_TO_KEYCODE(Scan_KP_Comma), //- Brazilian Keypad Period -
		Key_KB_Equal = SCANCODE_TO_KEYCODE(Scan_KB_Equal),

		Key_KB_International1 = SCANCODE_TO_KEYCODE(Scan_KB_International1), //- Ro -
		Key_KB_International2 = SCANCODE_TO_KEYCODE(Scan_KB_International2), //- Katakana/Hiragana -
		Key_KB_International3 = SCANCODE_TO_KEYCODE(Scan_KB_International3), //- Yen -
		Key_KB_International4 = SCANCODE_TO_KEYCODE(Scan_KB_International4), //- Henkan -
		Key_KB_International5 = SCANCODE_TO_KEYCODE(Scan_KB_International5), //- Muhenkan -
		Key_KB_International6 = SCANCODE_TO_KEYCODE(Scan_KB_International6), //- PC9800 Keypad Comma -
		Key_KB_International7 = SCANCODE_TO_KEYCODE(Scan_KB_International7),
		Key_KB_International8 = SCANCODE_TO_KEYCODE(Scan_KB_International8),
		Key_KB_International9 = SCANCODE_TO_KEYCODE(Scan_KB_International9),

		Key_KB_Language1 = SCANCODE_TO_KEYCODE(Scan_KB_Language1), //- Hanguel/English -
		Key_KB_Language2 = SCANCODE_TO_KEYCODE(Scan_KB_Language2), //- Hanja -
		Key_KB_Language3 = SCANCODE_TO_KEYCODE(Scan_KB_Language3), //- Katakana -
		Key_KB_Language4 = SCANCODE_TO_KEYCODE(Scan_KB_Language4), //- Hiragana -
		Key_KB_Language5 = SCANCODE_TO_KEYCODE(Scan_KB_Language5), //- Zenkaku/Hankaku -
		Key_KB_Language6 = SCANCODE_TO_KEYCODE(Scan_KB_Language6),
		Key_KB_Language7 = SCANCODE_TO_KEYCODE(Scan_KB_Language7),
		Key_KB_Language8 = SCANCODE_TO_KEYCODE(Scan_KB_Language8),
		Key_KB_Language9 = SCANCODE_TO_KEYCODE(Scan_KB_Language9),

		Key_KB_AltErase = SCANCODE_TO_KEYCODE(Scan_KB_AltErase),
		Key_KB_SystemRequest = SCANCODE_TO_KEYCODE(Scan_KB_SystemRequest),
		Key_KB_Cancel = SCANCODE_TO_KEYCODE(Scan_KB_Cancel),
		Key_KB_Clear = SCANCODE_TO_KEYCODE(Scan_KB_Clear),
		Key_KB_Prior = SCANCODE_TO_KEYCODE(Scan_KB_Prior),
		Key_KB_Return = SCANCODE_TO_KEYCODE(Scan_KB_Return),
		Key_KB_Separator = SCANCODE_TO_KEYCODE(Scan_KB_Separator),
		Key_KB_Out = SCANCODE_TO_KEYCODE(Scan_KB_Out),
		Key_KB_Oper = SCANCODE_TO_KEYCODE(Scan_KB_Oper),
		Key_KB_ClearAgain = SCANCODE_TO_KEYCODE(Scan_KB_ClearAgain),
		Key_KB_CrSelProps = SCANCODE_TO_KEYCODE(Scan_KB_CrSelProps),
		Key_KB_ExSel = SCANCODE_TO_KEYCODE(Scan_KB_ExSel),

		Key_KP_00 = SCANCODE_TO_KEYCODE(Scan_KP_00),
		Key_KP_000 = SCANCODE_TO_KEYCODE(Scan_KP_000),
		Key_KP_ThousandsSeparator = SCANCODE_TO_KEYCODE(Scan_KP_ThousandsSeparator),
		Key_KP_DecimalSeparator = SCANCODE_TO_KEYCODE(Scan_KP_DecimalSeparator),
		Key_KP_CurrencyUnit = SCANCODE_TO_KEYCODE(Scan_KP_CurrencyUnit),
		Key_KP_CurrencySubUnit = SCANCODE_TO_KEYCODE(Scan_KP_CurrencySubUnit),
		Key_KP_ParenthesisLeft = SCANCODE_TO_KEYCODE(Scan_KP_ParenthesisLeft),
		Key_KP_ParenthesisRight = SCANCODE_TO_KEYCODE(Scan_KP_ParenthesisRight),
		Key_KP_CurlyBracketLeft = SCANCODE_TO_KEYCODE(Scan_KP_CurlyBracketLeft),
		Key_KP_CurlyBracketRight = SCANCODE_TO_KEYCODE(Scan_KP_CurlyBracketRight),
		Key_KP_Tab = SCANCODE_TO_KEYCODE(Scan_KP_Tab),
		Key_KP_Backspace = SCANCODE_TO_KEYCODE(Scan_KP_Backspace),
		Key_KP_A = SCANCODE_TO_KEYCODE(Scan_KP_A),
		Key_KP_B = SCANCODE_TO_KEYCODE(Scan_KP_B),
		Key_KP_C = SCANCODE_TO_KEYCODE(Scan_KP_C),
		Key_KP_D = SCANCODE_TO_KEYCODE(Scan_KP_D),
		Key_KP_E = SCANCODE_TO_KEYCODE(Scan_KP_E),
		Key_KP_F = SCANCODE_TO_KEYCODE(Scan_KP_F),
		Key_KP_XOR = SCANCODE_TO_KEYCODE(Scan_KP_XOR),
		Key_KP_Caret = SCANCODE_TO_KEYCODE(Scan_KP_Caret),
		Key_KP_Percent = SCANCODE_TO_KEYCODE(Scan_KP_Percent),
		Key_KP_LessThan = SCANCODE_TO_KEYCODE(Scan_KP_LessThan),
		Key_KP_GreaterThan = SCANCODE_TO_KEYCODE(Scan_KP_GreaterThan),
		Key_KP_Ampersand = SCANCODE_TO_KEYCODE(Scan_KP_Ampersand),
		Key_KP_DoubleAmpersand = SCANCODE_TO_KEYCODE(Scan_KP_DoubleAmpersand),
		Key_KP_VerticalBar = SCANCODE_TO_KEYCODE(Scan_KP_VerticalBar),
		Key_KP_DoubleVerticalBar = SCANCODE_TO_KEYCODE(Scan_KP_DoubleVerticalBar),
		Key_KP_Colon = SCANCODE_TO_KEYCODE(Scan_KP_Colon),
		Key_KP_Number = SCANCODE_TO_KEYCODE(Scan_KP_Number),
		Key_KP_Space = SCANCODE_TO_KEYCODE(Scan_KP_Space),
		Key_KP_At = SCANCODE_TO_KEYCODE(Scan_KP_At),
		Key_KP_Exclamation = SCANCODE_TO_KEYCODE(Scan_KP_Exclamation),
		Key_KP_MemoryStore = SCANCODE_TO_KEYCODE(Scan_KP_MemoryStore),
		Key_KP_MemoryRecall = SCANCODE_TO_KEYCODE(Scan_KP_MemoryRecall),
		Key_KP_MemoryClear = SCANCODE_TO_KEYCODE(Scan_KP_MemoryClear),
		Key_KP_MemoryAdd = SCANCODE_TO_KEYCODE(Scan_KP_MemoryAdd),
		Key_KP_MemorySubtract = SCANCODE_TO_KEYCODE(Scan_KP_MemorySubtract),
		Key_KP_MemoryMultiply = SCANCODE_TO_KEYCODE(Scan_KP_MemoryMultiply),
		Key_KP_MemoryDivide = SCANCODE_TO_KEYCODE(Scan_KP_MemoryDivide),
		Key_KP_PlusMinus = SCANCODE_TO_KEYCODE(Scan_KP_PlusMinus),
		Key_KP_Clear = SCANCODE_TO_KEYCODE(Scan_KP_Clear),
		Key_KP_ClearEntry = SCANCODE_TO_KEYCODE(Scan_KP_ClearEntry),
		Key_KP_Binary = SCANCODE_TO_KEYCODE(Scan_KP_Binary),
		Key_KP_Octal = SCANCODE_TO_KEYCODE(Scan_KP_Octal),
		Key_KP_Decimal = SCANCODE_TO_KEYCODE(Scan_KP_Decimal),
		Key_KP_Hexadecimal = SCANCODE_TO_KEYCODE(Scan_KP_Hexadecimal),

		Key_ControlLeft = SCANCODE_TO_KEYCODE(Scan_ControlLeft),
		Key_ShiftLeft = SCANCODE_TO_KEYCODE(Scan_ShiftLeft),
		Key_AltLeft = SCANCODE_TO_KEYCODE(Scan_AltLeft),
		Key_GUILeft = SCANCODE_TO_KEYCODE(Scan_GUILeft),
		Key_ControlRight = SCANCODE_TO_KEYCODE(Scan_ControlRight),
		Key_ShiftRight = SCANCODE_TO_KEYCODE(Scan_ShiftRight),
		Key_AltRight = SCANCODE_TO_KEYCODE(Scan_AltRight),
		Key_GUIRight = SCANCODE_TO_KEYCODE(Scan_GUIRight)
	};

	enum Modifier
	{
		Mod_None,
		Mod_ShiftLeft = 0x0001,
		Mod_ShiftRight = 0x0002,
		Mod_ControlLeft = 0x0040,
		Mod_ControlRight = 0x0080,
		Mod_AltLeft = 0x0100,
		Mod_AltRight = 0x0200,
		Mod_GUILeft = 0x0400,
		Mod_GUIRight = 0x0800,
		Mod_NumLock = 0x1000,
		Mod_CapsLock = 0x2000,

		Mod_Control = Mod_ControlLeft | Mod_ControlRight,
		Mod_Shift = Mod_ShiftLeft | Mod_ShiftRight,
		Mod_Alt = Mod_AltLeft | Mod_AltRight,
		Mod_GUI = Mod_GUILeft | Mod_GUIRight
	};
}

#endif
