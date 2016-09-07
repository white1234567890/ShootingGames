#pragma once
#include "BoxChildClass.h"
#include "InputClass.h"

class PlayerClass :
	public BoxClass , public InputClass
{
private:
	BoxChildClass m_Child;

	void CheckInput();
	void PlayerCanNotOverScreen();
	
	bool InitializeChild();
	bool UpdateChild();
	void RenderChild();

public:
	PlayerClass(void);
	~PlayerClass(void);

	//////////////////////////////////////////////////////////////////////////////
	//�T��:
	//	������
	//����:
	//	*position:�ʒu
	//	*velocity:���x
	//	*accelaration:�����x
	//	*semi_long_vector:�������x�N�g��
	//	*semi_short_vector:���Z���x�N�g��
	//	flag:�t���O
	//�߂�l:
	//	true:�Ƃ肠����true��Ԃ�
	//////////////////////////////////////////////////////////////////////////////
	bool Initialize(POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , THREE_DIMENSION_VECTOR* semi_long_vector , THREE_DIMENSION_VECTOR* semi_short_vector , bool flag = true);

	bool Update();

	//////////////////////////////////////////////////////////////////////////////
	//�T��:
	//	�`��
	//////////////////////////////////////////////////////////////////////////////
	void Render();
};

