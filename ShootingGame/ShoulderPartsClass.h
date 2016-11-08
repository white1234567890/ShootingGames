#pragma once
#include "PlayerClass.h"
#include "BulletManagerClass.h"

class ShoulderPartsClass :
	public BoxClass
{
private:
	THREE_DIMENSIONAL_VECTOR m_ForwardVector;	//前方ベクトル

	int m_ShotType;	//ショットタイプ
	POSITION m_ShotPosition;	//ショットの位置
	double m_BarrelRange;	//ショットの初期位置を割り出すための長さ
	VELOCITY m_ShotVelocity;	//ショットの初速
	ACCELARATION m_ShotAccelaration;	//ショットの加速度
	THREE_DIMENSIONAL_VECTOR m_ShotSemiLongVector;	//ショットの画像の半長軸長
	THREE_DIMENSIONAL_VECTOR m_ShotSemiShortVector;	//ショットの画像の半短軸長
	double m_ShotSpeed;	//ショットの速さ

	PlayerClass *m_Pointer_to_Parent;	//プレイヤーへのポインタ

	//初期化（継承）
	virtual bool Initialize(POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , THREE_DIMENSIONAL_VECTOR* semi_long_vector , THREE_DIMENSIONAL_VECTOR* semi_short_vector , bool flag = true) final {return true ;}
	
	//更新（継承）
	virtual bool Update() final{return true;}
	
	//描画（継承）
	virtual void Render() final{}

	//////////////////////////////////////////////////////////////////////////////
	//肩パーツのデータをロードする
	//引数:
	//	shoulder_type:ロードするパーツタイプ
	//戻り値:
	//	true:データをロードした
	//	false:データのロードに失敗した
	//////////////////////////////////////////////////////////////////////////////
	bool LoadShoulderPartsData(int shoulder_type);
	
	//////////////////////////////////////////////////////////////////////////////
	//概略:
	//	ショットのパラメータを設定する
	//引数:
	//	int shot_type:ショットのタイプ
	//	barrel_range:初期位置を決定するための長さ
	//	velocity:ショットの初速
	//	shot_speed:ショットの速さ
	//	accelaration:ショットの加速度
	//	shot_semi_long_vector:ショットの画像の半長軸ベクトル
	//	shot_semishort_vector:ショットの画像の半短軸ベクトル
	//////////////////////////////////////////////////////////////////////////////
	void SetShotStatus(int shot_type , double barrel_range , VELOCITY* velocity , double shot_speed , ACCELARATION* accelaration , THREE_DIMENSIONAL_VECTOR* shot_semi_long_vector , THREE_DIMENSIONAL_VECTOR* shot_semi_short_vector);

public:

	ShoulderPartsClass(void);
	~ShoulderPartsClass(void);


	//ゲッタ（位置）
	POSITION GetShotPosition();
	
	//ゲッタ（速度）
	VELOCITY GetShotVelocity();
	
	//ゲッタ（加速度）
	ACCELARATION GetShotAccelaration();
	
	//ゲッタ（半長軸ベクトル）
	THREE_DIMENSIONAL_VECTOR GetShotSemiLongVector();
	
	//ゲッタ（半短軸ベクトル）
	THREE_DIMENSIONAL_VECTOR GetShotSemiShortVector();
	
	//////////////////////////////////////////////////////////////////////////////
	//概略:
	//	初期化
	//引数:
	//	shoulder_type:肩パーツタイプ
	//	local_position:プレイヤーから見た位置
	//	local_velocity:プレイヤーから見た速度
	//	local_accelaration:プレイヤーから見た加速度
	//	player:プレイヤーへのポインタ
	//	flag:描画フラグ
	//戻り値:
	//	true:成功
	//	false:失敗
	//////////////////////////////////////////////////////////////////////////////
	bool Initialize(int shoulder_type , POSITION* local_position , VELOCITY* local_velocity , ACCELARATION* local_accelaration , PlayerClass* player , bool flag = true);
	
	//////////////////////////////////////////////////////////////////////////////
	//概略:
	//	更新
	//引数:
	//	shot_flag:ショットを撃つか撃たないかのフラグ
	//////////////////////////////////////////////////////////////////////////////
	bool Update(bool shot_flag);

	//////////////////////////////////////////////////////////////////////////////
	//概略:
	//	描画
	//引数:
	//	player_world_position:プレイヤーの位置
	//////////////////////////////////////////////////////////////////////////////
	void Render(POSITION* player_world_positoin);
};