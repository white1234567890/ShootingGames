#include "PlayerClass.h"
#define _USE_MATH_DEFINES
#include <math.h>

#include <gl\glew.h>
#include <gl\glut.h>

#include "system.h"
#include "ShoulderPartsClass.h"
#include "BackPartsClass.h"
#include "HipPartsClass.h"

//実体化
PlayerClass TestPlayer;

//コンストラクタ
PlayerClass::PlayerClass(void)
{
	m_Pointer_to_Shoulder_L = NULL;
	m_Pointer_to_Shoulder_R = NULL;
}

//デストラクタ
PlayerClass::~PlayerClass(void)
{
}

//////////////////////////////////////////////////////////////////////////////
//private関数
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//概略:
//	インプットによってプレイヤーの挙動を変化させる
//////////////////////////////////////////////////////////////////////////////
void PlayerClass::CheckInput()
{
	if(m_InputKeyFlag & E_UP_ARROW_KEY) m_Velocity.m_Vector.y = m_PLAYER_Y_SPEED;	//↑キー
	if(m_InputKeyFlag & E_LEFT_ARROW_KEY) m_Velocity.m_Vector.x = -m_PLAYER_X_SPEED;	//←キー
	if(m_InputKeyFlag & E_RIGHT_ARROW_KEY) m_Velocity.m_Vector.x = m_PLAYER_X_SPEED;	//→キー
	if(m_InputKeyFlag & E_DOWN_ARROW_KEY) m_Velocity.m_Vector.y = -m_PLAYER_Y_SPEED;	//↓キー

	//↑キーも↓キーも押されていなかったらy軸方向の速度成分を0にする
	if(!(m_InputKeyFlag & E_UP_ARROW_KEY || m_InputKeyFlag & E_DOWN_ARROW_KEY)) m_Velocity.m_Vector.y = 0;
	//←キーも→キーも押されていなかったらx軸方向の速度成分を0にする
	if(!(m_InputKeyFlag & E_LEFT_ARROW_KEY || m_InputKeyFlag & E_RIGHT_ARROW_KEY)) m_Velocity.m_Vector.x = 0;
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	プレイヤーの移動可能範囲を制限する
//////////////////////////////////////////////////////////////////////////////
void PlayerClass::PlayerCanNotOverScreen()
{
	if(m_Position.m_Vector.y > WINDOW_HEIGHT) m_Position.m_Vector.y = WINDOW_HEIGHT;
	if(m_Position.m_Vector.y < 0) m_Position.m_Vector.y = 0;
	if(m_Position.m_Vector.x > WINDOW_WIDTH) m_Position.m_Vector.x = WINDOW_WIDTH;
	if(m_Position.m_Vector.x < 0) m_Position.m_Vector.x = 0;
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	子オブジェクトの初期設定
//戻り値:
//	true:とりあえずtrueを返す
//////////////////////////////////////////////////////////////////////////////
bool PlayerClass::InitializeChild()
{
	//左肩
	m_Pointer_to_Shoulder_L->Initialize(&POSITION(10 , 32) , &VELOCITY() , &ACCELARATION() , &THREE_DIMENSION_VECTOR(5) , &THREE_DIMENSION_VECTOR(0 , 5) , this);
	//右肩
	m_Pointer_to_Shoulder_R->Initialize(&POSITION(-10 , 32) , &VELOCITY() , &ACCELARATION() , &THREE_DIMENSION_VECTOR(5) , &THREE_DIMENSION_VECTOR(0 , 5) , this);
	//背中
	m_Pointer_to_Back->Initialize(&POSITION(0 , 10) , &VELOCITY() , &ACCELARATION() , &THREE_DIMENSION_VECTOR(0 , 10) , &THREE_DIMENSION_VECTOR(5) , this);
	//腰
	m_Pointer_to_Hip->Initialize(&POSITION(0 , -10) , &VELOCITY() , &ACCELARATION() , &THREE_DIMENSION_VECTOR(10) , &THREE_DIMENSION_VECTOR(0 , 5) , this);
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	子オブジェクトを更新する
//戻り値:
//	とりあえずtrueを返す
//////////////////////////////////////////////////////////////////////////////
bool PlayerClass::UpdateChild()
{
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	子オブジェクトを描画する
//////////////////////////////////////////////////////////////////////////////
void PlayerClass::RenderChild()
{
	//左肩
	m_Pointer_to_Shoulder_L->Render(&m_Position);
	//右肩
	m_Pointer_to_Shoulder_R->Render(&m_Position);
	//背中
	m_Pointer_to_Back->Render(&m_Position);
	//腰
	m_Pointer_to_Hip->Render(&m_Position);
}


//////////////////////////////////////////////////////////////////////////////
//public関数
//////////////////////////////////////////////////////////////////////////////

void PlayerClass::SetPlayerSpeed(double x , double y)
{
	m_PLAYER_X_SPEED = x;
	m_PLAYER_Y_SPEED = y;
}

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
bool PlayerClass::Initialize(POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , THREE_DIMENSION_VECTOR* semi_long_vector , THREE_DIMENSION_VECTOR* semi_short_vector , ShoulderPartsClass* shoulder_l , ShoulderPartsClass* shoulder_r , BackPartsClass* back , HipPartsClass* hip , bool flag)
{
	m_Position = *position;
	m_Velocity = *velocity;
	m_Accelaration = *accelaration;
	m_SemiLongVector = *semi_long_vector;
	m_SemiShortVector = *semi_short_vector;

	m_SemiLongAxis = m_SemiLongVector.Magnitude();
	m_SemiShortAxis = m_SemiShortVector.Magnitude();

	SetVertex();

	m_Pointer_to_Shoulder_L = shoulder_l;
	m_Pointer_to_Shoulder_R = shoulder_r;
	m_Pointer_to_Back = back;
	m_Pointer_to_Hip = hip;

	SetPlayerSpeed(PLAYER_SPEED_X_ASPECT * WINDOW_WIDTH * WINDOW_HEIGHT / 100000 , PLAYER_SPEED_Y_ASPECT * WINDOW_WIDTH * WINDOW_HEIGHT / 100000);

	InitializeChild();

	return true;
}


//////////////////////////////////////////////////////////////////////////////
//概略:
//	更新
//戻り値:
//	true:とりあえずtrueを返す
//////////////////////////////////////////////////////////////////////////////
bool PlayerClass::Update()
{
	CheckInput();	//キー入力を調べる
	MoveObject();	//移動させる
	SetVertex();	//頂点の再計算をする
	AccelObject();	//加速させる
	PlayerCanNotOverScreen();	//移動範囲を制限する

	UpdateChild();

	return true;
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	描画
//////////////////////////////////////////////////////////////////////////////
void PlayerClass::Render()
{
	//色設定（白）
	glColor3f(1.f , 1.f , 1.f);

	//四角を描画
	glBegin(GL_POLYGON);

	//各頂点
	for(unsigned int i = 0 ; i < m_Vertex.size() ; i++)
	{
		glVertex2d(Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesX(m_Vertex.m_VertexPosition[i].m_Vector.x) ,
			Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesY(m_Vertex.m_VertexPosition[i].m_Vector.y));
	}

	glEnd();

	RenderChild();
}