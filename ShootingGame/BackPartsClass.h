#pragma once
#include "PlayerClass.h"

class BackPartsClass :
	public BoxClass
{
private:
	PlayerClass *m_Pointer_to_Parent;	//プレイヤーへのポインタ
	
	//初期化(継承)
	virtual bool Initialize(POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , THREE_DIMENSIONAL_VECTOR* semi_long_vector , THREE_DIMENSIONAL_VECTOR* semi_short_vector , bool flag = true) final {return true ;}
	//描画(継承)
	virtual void Render() final{}
	
	//////////////////////////////////////////////////////////////////////////////
	//背中パーツのデータをロードする
	//引数:
	//	ロードするパーツタイプ
	//戻り値:
	//	true:データをロードした
	//	false:データのロードに失敗した
	//////////////////////////////////////////////////////////////////////////////
	bool LoadBackPartsData(int back_type);

public:
	BackPartsClass(void);
	~BackPartsClass(void);

	//////////////////////////////////////////////////////////////////////////////
	//概略:
	//	初期化
	//引数:
	//	back_type:背中パーツのタイプ
	//	local_position:プレイヤーから見た位置
	//	local_velocity:プレイヤーから見た速度
	//	local_accelaration:プレイヤーから見た加速度
	//	player:プレイヤーへのポインタ
	//	flag:描画フラグ
	//戻り値:
	//	true:成功
	//	false:失敗
	//////////////////////////////////////////////////////////////////////////////
	bool Initialize(int back_type , POSITION* local_position , VELOCITY* local_velocity , ACCELARATION* local_accelaration , PlayerClass* player , bool flag = true);
	
	//////////////////////////////////////////////////////////////////////////////
	//概略:
	//	描画
	//引数:
	//	player_world_position:プレイヤーの位置
	//////////////////////////////////////////////////////////////////////////////
	void Render(POSITION* player_world_position);
};