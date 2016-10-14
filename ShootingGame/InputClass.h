#pragma once
#include "common.h"

class InputClass
{
protected:
	enum NOMAL_KEY_NUMBER
	{
		E_UP_ARROW_KEY = 1,
		E_LEFT_ARROW_KEY = 1 << 1,
		E_RIGHT_ARROW_KEY = 1 << 2,
		E_DOWN_ARROW_KEY = 1 << 3,
		E_Z_KEY = 1 << 4,
		E_X_KEY = 1 << 5,
		E_ESC_KEY = 1 << 6,
		E_RETURN_KEY = 1 << 7,
		E_SHIFT_KEY = 1 << 8,
	};

	unsigned int m_OldKeyFlag;
	unsigned int m_NowKeyFlag;
	unsigned int m_InputKeyFlag;

public:
	enum INPUT_MODE
	{
		E_PROHIBIT_PRESS_TWICE,
		E_ALLOW_PLESS_TWICE
	}final;

	InputClass(void);
	~InputClass(void);

	void KeyBoard();

	unsigned int InputKey(INPUT_MODE input_mode);
};

