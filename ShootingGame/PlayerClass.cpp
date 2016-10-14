#include "PlayerClass.h"
#define _USE_MATH_DEFINES
#include <math.h>

#include <gl\glew.h>
#include <gl\glut.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include "system.h"
#include "ShoulderPartsClass.h"
#include "BackPartsClass.h"
#include "HipPartsClass.h"

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

bool PlayerClass::LoadPlayerStatus(std::string file_name)
{
	
	std::ifstream ifs(file_name);

	if(ifs.fail()) return false;

	std::string PlayerStatus;
	
	for(int i = 0 ; i < 2 ; i++)
	{
		std::getline(ifs , PlayerStatus);
	}

	std::string token;
	std::istringstream stream(PlayerStatus);
	std::vector<double> TempVector;
	
	while(getline(stream , token , ','))
	{
		TempVector.push_back(std::stod(token));
	}

	SPEED_X_ASPECT = TempVector[0];
	SPEED_Y_ASPECT = TempVector[1];

	if(TempVector[2] >= TempVector[3])
	{
		m_SemiLongVector = THREE_DIMENSION_VECTOR(TempVector[2]);
		m_SemiShortVector = THREE_DIMENSION_VECTOR(0 , TempVector[3]);
	}
	else
	{
		m_SemiLongVector = THREE_DIMENSION_VECTOR(0 , TempVector[3]);
		m_SemiShortVector = THREE_DIMENSION_VECTOR(TempVector[2]);
	}

	if(TempVector[6] >= TempVector[7])
	{
		m_Pointer_to_Shoulder_L->SetShotStatus(TempVector[4] , &VELOCITY() , TempVector[5] , &ACCELARATION() , &THREE_DIMENSION_VECTOR(TempVector[6] / 2) , &THREE_DIMENSION_VECTOR(0 , TempVector[7] / 2));
		m_Pointer_to_Shoulder_R->SetShotStatus(TempVector[4] , &VELOCITY() , TempVector[5] , &ACCELARATION() , &THREE_DIMENSION_VECTOR(TempVector[6] / 2) , &THREE_DIMENSION_VECTOR(0 , TempVector[7] / 2));
	}
	else
	{
		m_Pointer_to_Shoulder_L->SetShotStatus(TempVector[4] , &VELOCITY() , TempVector[5] , &ACCELARATION() , &THREE_DIMENSION_VECTOR(0 , TempVector[7] / 2) , &THREE_DIMENSION_VECTOR(TempVector[6] / 2));
		m_Pointer_to_Shoulder_R->SetShotStatus(TempVector[4] , &VELOCITY() , TempVector[5] , &ACCELARATION() , &THREE_DIMENSION_VECTOR(0 , TempVector[7] / 2) , &THREE_DIMENSION_VECTOR(TempVector[6] / 2));
	}

	ReleaseVector(TempVector);

	return true;
}

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
	if(!(m_InputKeyFlag & E_UP_ARROW_KEY || m_InputKeyFlag & E_DOWN_ARROW_KEY) || 
		(m_InputKeyFlag & E_UP_ARROW_KEY && m_InputKeyFlag & E_DOWN_ARROW_KEY)) m_Velocity.m_Vector.y = 0;
	//←キーも→キーも押されていなかったらx軸方向の速度成分を0にする
	if(!(m_InputKeyFlag & E_LEFT_ARROW_KEY || m_InputKeyFlag & E_RIGHT_ARROW_KEY) ||
		(m_InputKeyFlag & E_LEFT_ARROW_KEY && m_InputKeyFlag & E_RIGHT_ARROW_KEY)) m_Velocity.m_Vector.x = 0;

	if(m_InputKeyFlag & E_Z_KEY) m_ShotFlag = true;	//Zキーでショットフラグを立てる
	else m_ShotFlag = false;	//Zキーを離すと消す
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

void PlayerClass::MoveObject()
{
	if(m_InputKeyFlag & E_SHIFT_KEY)
	{
		m_Position.m_Vector += m_Velocity.m_Vector * 0.5;
	}
	else
	{
		m_Position.m_Vector += m_Velocity.m_Vector;
	}
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
	m_Pointer_to_Shoulder_L->Update(m_ShotFlag);
	m_Pointer_to_Shoulder_R->Update(m_ShotFlag);
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

/////////////////////////////////////////////////////////////////////////////
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
bool PlayerClass::Initialize(std::string file_name , ShoulderPartsClass* shoulder_l , ShoulderPartsClass* shoulder_r , BackPartsClass* back , HipPartsClass* hip , bool flag)
{
	m_Position = POSITION(WINDOW_WIDTH / 2 , WINDOW_HEIGHT / 10);
	m_Velocity.m_Vector = THREE_DIMENSION_VECTOR();
	m_Accelaration = ACCELARATION();

	m_SemiLongAxis = m_SemiLongVector.Magnitude();
	m_SemiShortAxis = m_SemiShortVector.Magnitude();

	SetVertex();

	m_Pointer_to_Shoulder_L = shoulder_l;
	m_Pointer_to_Shoulder_R = shoulder_r;
	m_Pointer_to_Back = back;
	m_Pointer_to_Hip = hip;

	LoadPlayerStatus(file_name);

	SetPlayerSpeed(SPEED_X_ASPECT * WINDOW_WIDTH * WINDOW_HEIGHT / SPEED_ASPECT , SPEED_Y_ASPECT * WINDOW_WIDTH * WINDOW_HEIGHT / SPEED_ASPECT);

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