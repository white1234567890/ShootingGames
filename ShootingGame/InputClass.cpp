#include "InputClass.h"

#include <Windows.h>

//コンストラクタ
InputClass::InputClass(void)
{
	m_OldKeyFlag = 0;
	m_NowKeyFlag = 0;
	m_InputKeyFlag = 0;
}

//デストラクタ
InputClass::~InputClass(void)
{
}

//////////////////////////////////////////////////////////////////////////////
//キーボードの入力チェック
//////////////////////////////////////////////////////////////////////////////
void InputClass::KeyBoard()
{
	if(GetAsyncKeyState(VK_UP))	m_NowKeyFlag |= E_UP_ARROW_KEY;
	else m_NowKeyFlag &= ~E_UP_ARROW_KEY;
	if(GetAsyncKeyState(VK_DOWN)) m_NowKeyFlag |= E_DOWN_ARROW_KEY;
	else m_NowKeyFlag &= ~E_DOWN_ARROW_KEY;
	if(GetAsyncKeyState(VK_LEFT)) m_NowKeyFlag |= E_LEFT_ARROW_KEY;
	else m_NowKeyFlag &= ~E_LEFT_ARROW_KEY;
	if(GetAsyncKeyState(VK_RIGHT)) m_NowKeyFlag |= E_RIGHT_ARROW_KEY;
	else m_NowKeyFlag &= ~E_RIGHT_ARROW_KEY;
	if(GetAsyncKeyState(VK_SHIFT)) m_NowKeyFlag |= E_SHIFT_KEY;
	else m_NowKeyFlag &= ~E_SHIFT_KEY;
	if(GetAsyncKeyState('Z')) m_NowKeyFlag |= E_Z_KEY;
	else m_NowKeyFlag &= ~E_Z_KEY;
	if(GetAsyncKeyState('X')) m_NowKeyFlag |= E_X_KEY;
	else m_NowKeyFlag &= ~E_X_KEY;
	if(GetAsyncKeyState(VK_ESCAPE)) m_NowKeyFlag |= E_ESC_KEY;
	else m_NowKeyFlag &= ~E_ESC_KEY;
}

//////////////////////////////////////////////////////////////////////////////
//キー入力
//引数:
//	input_mode:インプットモード
//////////////////////////////////////////////////////////////////////////////
unsigned int InputClass::InputKey(INPUT_MODE input_mode)
{
	m_OldKeyFlag = m_NowKeyFlag;	//前のキーを記憶

	//入力されたキーのチェック
	KeyBoard();

	//インプットモードが
	switch (input_mode)
	{
		//2度押し禁止の時
	case InputClass::E_PROHIBIT_PRESS_TWICE:
		//2度押し禁止用の値を返す
		m_InputKeyFlag = m_NowKeyFlag & ~ m_OldKeyFlag;
		break;
	
		//2度押しおkの時
	case InputClass::E_ALLOW_PLESS_TWICE:
		//現在のキーを返す
		m_InputKeyFlag = m_NowKeyFlag;
		break;
	}
	return m_InputKeyFlag;
}