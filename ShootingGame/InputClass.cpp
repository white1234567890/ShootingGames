#include "InputClass.h"

#include <Windows.h>

//コンストラクタ
InputClass::InputClass(void)
{
	m_InputKeyFlag = 0;
}

//デストラクタ
InputClass::~InputClass(void)
{
}

void InputClass::KeyBoard()
{
	if(GetAsyncKeyState(VK_UP))	m_InputKeyFlag |= E_UP_ARROW_KEY;
	else m_InputKeyFlag &= ~E_UP_ARROW_KEY;
	if(GetAsyncKeyState(VK_DOWN)) m_InputKeyFlag |= E_DOWN_ARROW_KEY;
	else m_InputKeyFlag &= ~E_DOWN_ARROW_KEY;
	if(GetAsyncKeyState(VK_LEFT)) m_InputKeyFlag |= E_LEFT_ARROW_KEY;
	else m_InputKeyFlag &= ~E_LEFT_ARROW_KEY;
	if(GetAsyncKeyState(VK_RIGHT)) m_InputKeyFlag |= E_RIGHT_ARROW_KEY;
	else m_InputKeyFlag &= ~E_RIGHT_ARROW_KEY;
	if(GetAsyncKeyState(VK_SHIFT)) m_InputKeyFlag |= E_SHIFT_KEY;
	else m_InputKeyFlag &= ~E_SHIFT_KEY;
	if(GetAsyncKeyState('Z')) m_InputKeyFlag |= E_Z_KEY;
	else m_InputKeyFlag &= ~E_Z_KEY;
	if(GetAsyncKeyState('X')) m_InputKeyFlag |= E_X_KEY;
	else m_InputKeyFlag &= ~E_X_KEY;
	if(GetAsyncKeyState(VK_ESCAPE)) m_InputKeyFlag |= E_ESC_KEY;
	else m_InputKeyFlag &= ~E_ESC_KEY;
}
