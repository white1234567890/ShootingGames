#pragma once
class InputClass
{
protected:
	enum NomalKeyNumber
	{
		E_UP_ARROW_KEY = 1,
		E_LEFT_ARROW_KEY = 1 << 1,
		E_RIGHT_ARROW_KEY = 1 << 2,
		E_DOWN_ARROW_KEY = 1 << 3,
		E_Z_KEY = 1 << 4,
		E_X_KEY = 1 << 5,
		E_ESC_KEY = 1 << 6,
		E_SHIFT_KEY = 1 << 7,
	};

	unsigned int m_InputKeyFlag;

public:
	InputClass(void);
	~InputClass(void);

	void KeyBoard();
};

