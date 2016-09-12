#pragma once
<<<<<<< HEAD
#include "BoxClass.h"
=======
#include "ChildClass.h"
#include "CircleClass.h"
>>>>>>> 01baa79cb0d485862d37499ae753f38b6866ee30
#include "InputClass.h"

class ShoulderPartsClass;
class BackPartsClass;
class HipPartsClass;

class PlayerClass :
	public CircleClass , public InputClass
{
private:
<<<<<<< HEAD
	ShoulderPartsClass *m_Pointer_to_Shoulder_L;
	ShoulderPartsClass *m_Pointer_to_Shoulder_R;
	BackPartsClass *m_Pointer_to_Back;
	HipPartsClass *m_Pointer_to_Hip;
	double m_PLAYER_X_SPEED;
	double m_PLAYER_Y_SPEED;
=======
	ChildClass m_Child;
>>>>>>> 01baa79cb0d485862d37499ae753f38b6866ee30

	void CheckInput();
	void PlayerCanNotOverScreen();
	
	bool InitializeChild();
	bool UpdateChild();
	void RenderChild();

public:
	PlayerClass(void);
	~PlayerClass(void);

	void SetPlayerSpeed(double x , double y);

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
<<<<<<< HEAD
	bool Initialize(POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , THREE_DIMENSION_VECTOR* semi_long_vector , THREE_DIMENSION_VECTOR* semi_short_vector , ShoulderPartsClass* shoulder_l , ShoulderPartsClass* shoulder_r , BackPartsClass* back , HipPartsClass* hip , bool flag = true);
=======
	bool Initialize(POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , double radius , bool flag = true);
>>>>>>> 01baa79cb0d485862d37499ae753f38b6866ee30

	bool Update();

	//////////////////////////////////////////////////////////////////////////////
	//概略:
	//	描画
	//////////////////////////////////////////////////////////////////////////////
	void Render();
};

extern PlayerClass TestPlayer;
