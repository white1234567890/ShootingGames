#pragma once
#include "BoxClass.h"
#include "InputClass.h"
#include <string>

class ShoulderPartsClass;
class BackPartsClass;
class HipPartsClass;

class PlayerClass :
	public BoxClass , public InputClass
{
private:
	ShoulderPartsClass *m_Pointer_to_Shoulder_L;
	ShoulderPartsClass *m_Pointer_to_Shoulder_R;
	BackPartsClass *m_Pointer_to_Back;
	HipPartsClass *m_Pointer_to_Hip;
	double m_PLAYER_X_SPEED;
	double m_PLAYER_Y_SPEED;

	bool m_ShotFlag;

	bool LoadPlayerStatus(std::string file_name);

	void CheckInput();
	void PlayerCanNotOverScreen();
	void MoveObject();
	
	bool InitializeChild();
	bool UpdateChild();
	void RenderChild();

public:

	PlayerClass(void);
	~PlayerClass(void);

	//////////////////////////////////////////////////////////////////////////////
	//概略:
	//	プレイヤーの速度を設定する
	//引数:
	//	x:横軸速度
	//	y:縦軸速度
	//////////////////////////////////////////////////////////////////////////////
	void SetPlayerSpeed(double x , double y);

	//////////////////////////////////////////////////////////////////////////////
	//概略:
	//	初期化
	//引数:
	//	*position:位置
	//	*velocity:速度
	//	*accelaration:加速度
	//	*semi_long_vector:半長軸ベクトル
	//	*semi_short_vector:半短軸ベクトル
	//	*shoulder_l:左肩パーツへのポインタ
	//	*shoulder_r:右肩パーツへのポインタ
	//	*back:背中パーツへのポインタ
	//	*hip:腰パーツへのポインタ
	//	flag:フラグ
	//戻り値:
	//	true:とりあえずtrueを返す
	//////////////////////////////////////////////////////////////////////////////
	bool Initialize(std::string file_name , ShoulderPartsClass* shoulder_l , ShoulderPartsClass* shoulder_r , BackPartsClass* back , HipPartsClass* hip , bool flag = true);

	bool Update();

	//////////////////////////////////////////////////////////////////////////////
	//概略:
	//	描画
	//////////////////////////////////////////////////////////////////////////////
	void Render();
};