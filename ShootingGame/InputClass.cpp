#include "InputClass.h"

#include <Windows.h>

//�R���X�g���N�^
InputClass::InputClass(void)
{
	m_OldKeyFlag = 0;
	m_NowKeyFlag = 0;
	m_InputKeyFlag = 0;
}

//�f�X�g���N�^
InputClass::~InputClass(void)
{
}

//////////////////////////////////////////////////////////////////////////////
//�L�[�{�[�h�̓��̓`�F�b�N
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
//�L�[����
//����:
//	input_mode:�C���v�b�g���[�h
//////////////////////////////////////////////////////////////////////////////
unsigned int InputClass::InputKey(INPUT_MODE input_mode)
{
	m_OldKeyFlag = m_NowKeyFlag;	//�O�̃L�[���L��

	//���͂��ꂽ�L�[�̃`�F�b�N
	KeyBoard();

	//�C���v�b�g���[�h��
	switch (input_mode)
	{
		//2�x�����֎~�̎�
	case InputClass::E_PROHIBIT_PRESS_TWICE:
		//2�x�����֎~�p�̒l��Ԃ�
		m_InputKeyFlag = m_NowKeyFlag & ~ m_OldKeyFlag;
		break;
	
		//2�x������k�̎�
	case InputClass::E_ALLOW_PLESS_TWICE:
		//���݂̃L�[��Ԃ�
		m_InputKeyFlag = m_NowKeyFlag;
		break;
	}
	return m_InputKeyFlag;
}