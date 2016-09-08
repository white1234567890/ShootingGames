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
	//概略:
	//	初期化
	//引数:
	//	*position:位置
	//	*velocity:速度
	//	*accelaration:加速度
	//	flag:フラグ
	//戻り値:
	//	true:とりあえずtrueを返す
	//////////////////////////////////////////////////////////////////////////////
	bool Initialize(POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , double radius , bool flag = true);

	bool Update();

	//////////////////////////////////////////////////////////////////////////////
	//概略:
	//	描画
	//////////////////////////////////////////////////////////////////////////////
	void Render();
};

