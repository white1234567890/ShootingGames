#pragma once
#include "ChildClass.h"
#include "CircleClass.h"
#include "InputClass.h"

class PlayerClass :
	public CircleClass , public InputClass
{
private:
	ChildClass m_Child;

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
	//	flag:�t���O
	//�߂�l:
	//	true:�Ƃ肠����true��Ԃ�
	//////////////////////////////////////////////////////////////////////////////
	bool Initialize(POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , double radius , bool flag = true);

	bool Update();

	//////////////////////////////////////////////////////////////////////////////
	//�T��:
	//	�`��
	//////////////////////////////////////////////////////////////////////////////
	void Render();
};

