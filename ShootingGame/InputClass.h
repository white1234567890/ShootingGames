#pragma once
#include "common.h"

class InputClass
{
protected:
	//�L�[�{�[�h�̔ԍ�
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

	unsigned int m_OldKeyFlag;	//�O�̃L�[
	unsigned int m_NowKeyFlag;	//���̃L�[
	unsigned int m_InputKeyFlag;	//2�x�����`�F�b�N������̃L�[

public:
	//�C���v�b�g���[�h
	enum INPUT_MODE
	{
		E_PROHIBIT_PRESS_TWICE,
		E_ALLOW_PLESS_TWICE
	}final;

	InputClass(void);
	~InputClass(void);

	//////////////////////////////////////////////////////////////////////////////
	//�L�[�{�[�h�̓��̓`�F�b�N
	//////////////////////////////////////////////////////////////////////////////
	void KeyBoard();

	//////////////////////////////////////////////////////////////////////////////
	//�L�[����
	//����:
	//	input_mode:�C���v�b�g���[�h
	//////////////////////////////////////////////////////////////////////////////
	unsigned int InputKey(INPUT_MODE input_mode);
};