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
	//概略:
	//	初期化
	//引数:
	//	*position:位置
	//	*velocity:速度
	//	*accelaration:加速度
	//	*semi_long_vector:半長軸ベクトル
	//	*semi_short_vector:半短軸ベクトル
	//	flag:フラグ
	//戻り値:
	//	true:とりあえずtrueを返す
	//////////////////////////////////////////////////////////////////////////////
	bool Initialize(POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , THREE_DIMENSION_VECTOR* semi_long_vector , THREE_DIMENSION_VECTOR* semi_short_vector , bool flag = true);

	bool Update();

	//////////////////////////////////////////////////////////////////////////////
	//概略:
	//	描画
	//////////////////////////////////////////////////////////////////////////////
	void Render();
};

