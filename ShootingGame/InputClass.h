#pragma once
class InputClass
{
protected:
	enum KEYNUMBER
	{
		E_UP_ARROW_KEY = 1,
		E_LEFT_ARROW_KEY = 1 << 1,
		E_RIGHT_ARROW_KEY = 1 << 2,
		E_DOWN_ARROW_KEY = 1 << 3,
	};

	unsigned int m_InputKeyFlag;

public:
	InputClass(void);
	~InputClass(void);

	void KeyBoardDown(unsigned char key);
	void KeyBoardUp(unsigned char key);
	void SpecialKeyBoardDown(int key);
	void SpecialKeyBoardUp(int key);
};

