#include "ShoulderPartsClass.h"

#include <gl\glew.h>
#include <gl\glut.h>

#include "system.h"

#include "PlayerBulletManagerClass.h"
ShoulderPartsClass::ShoulderPartsClass(void)
{
	m_Pointer_to_Parent = NULL;
}


ShoulderPartsClass::~ShoulderPartsClass(void)
{
}

//////////////////////////////////////////////////////////////////////////////
//private関数
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//肩パーツのデータをロードする
//引数:
//	shoulder_type:ロードするパーツタイプ
//戻り値:
//	true:データをロードした
//	false:データのロードに失敗した
//////////////////////////////////////////////////////////////////////////////
bool LoadShoulderPartsData(int shoulder_type)
{
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	ショットのパラメータを設定する
//引数:
//	shot_type:ショットタイプ
//	barrel_range:初期位置を決定するための長さ
//	velocity:ショットの初速
//	shot_speed:ショットの速さ
//	accelaration:ショットの加速度
//	shot_semi_long_vector:ショットの画像の半長軸ベクトル
//	shot_semishort_vector:ショットの画像の半短軸ベクトル
//////////////////////////////////////////////////////////////////////////////
void ShoulderPartsClass::SetShotStatus(int shot_type , double barrel_range , VELOCITY* velocity , double shot_speed , ACCELARATION* accelaration , THREE_DIMENSIONAL_VECTOR* shot_semi_long_vector , THREE_DIMENSIONAL_VECTOR* shot_semi_short_vector)
{
	m_ShotType = shot_type;
	m_BarrelRange = barrel_range;
	m_ShotVelocity = *velocity;
	m_ShotSpeed = shot_speed;
	m_ShotAccelaration = *accelaration;
	m_ShotSemiLongVector = *shot_semi_long_vector;
	m_ShotSemiShortVector = *shot_semi_short_vector;
}

//////////////////////////////////////////////////////////////////////////////
//public関数
//////////////////////////////////////////////////////////////////////////////

//ゲッタ（位置）
POSITION ShoulderPartsClass::GetShotPosition()
{
	return m_ShotPosition;
}

//ゲッタ（速度）
VELOCITY ShoulderPartsClass::GetShotVelocity()
{
	return m_ShotVelocity;
}
	
//ゲッタ（加速度）
ACCELARATION ShoulderPartsClass::GetShotAccelaration()
{
	return m_ShotAccelaration;
}
	
//ゲッタ（半長軸ベクトル）
THREE_DIMENSIONAL_VECTOR ShoulderPartsClass::GetShotSemiLongVector()
{
	return m_ShotSemiLongVector;
}
	
//ゲッタ（半短軸ベクトル）
THREE_DIMENSIONAL_VECTOR ShoulderPartsClass::GetShotSemiShortVector()
{
	return m_ShotSemiShortVector;
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	初期化
//引数:
//	local_position:プレイヤーから見た位置
//	local_velocity:プレイヤーから見た速度
//	local_accelaration:プレイヤーから見た加速度
//	semi_long_vector:画像の大きさ(半長軸長)
//	semi_short_vector:画像の大きさ(半短軸長)
//	player:プレイヤーへのポインタ
//	flag:描画フラグ
//戻り値:
//	true:成功
//	false:失敗
//////////////////////////////////////////////////////////////////////////////
bool ShoulderPartsClass::Initialize(POSITION* local_position , VELOCITY* local_velocity , ACCELARATION* local_accelaration , PlayerClass* player , bool flag)
{
	m_Position = *local_position;
	m_Velocity = *local_velocity;
	m_Accelaration = *local_accelaration;

	m_SemiLongAxis = m_SemiLongVector.Magnitude();
	m_SemiShortAxis = m_SemiShortVector.Magnitude();

	m_ForwardVector.Set(0 , 1);

	SetVertex();

	m_Pointer_to_Parent = player;

	return true;
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	更新
//引数:
//	shot_flag:ショットを撃つか撃たないかのフラグ
//////////////////////////////////////////////////////////////////////////////
bool ShoulderPartsClass::Update(bool shot_flag)
{
	//ショットの位置を割り出す
	m_ShotPosition.m_Vector = m_Pointer_to_Parent->GetPosition().m_Vector + m_Position.m_Vector + RotateVector2(&m_ForwardVector , m_Angle) * m_BarrelRange;
	
	//ショットの速度を割り出す
	m_ShotVelocity.m_Vector = RotateVector2(&m_ForwardVector , m_Angle) * m_ShotSpeed;

	//ショットを撃つとき
	if(shot_flag)
	{
		//ショットを生成する
		cl_PlayerBulletManager->CreateBullet(&m_ShotPosition , &m_ShotVelocity , &m_ShotAccelaration , &m_ShotSemiLongVector , &m_ShotSemiShortVector);
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	描画
//引数:
//	player_world_position:プレイヤーの位置
//////////////////////////////////////////////////////////////////////////////
void ShoulderPartsClass::Render(POSITION* player_world_positoin)
{
	//色設定（赤）
	glColor3f(1.f , 0 , 0);

	//四角を描画
	glBegin(GL_POLYGON);

	//各頂点
	for(unsigned int i = 0 ; i < m_Vertex.size() ; i++)
	{
		glVertex2d(Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesX(player_world_positoin->m_Vector.x + m_Vertex.m_VertexPosition[i].m_Vector.x) ,
			Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesY(player_world_positoin->m_Vector.y + m_Vertex.m_VertexPosition[i].m_Vector.y));
	}

	glEnd();
}