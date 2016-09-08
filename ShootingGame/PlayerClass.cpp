#include "PlayerClass.h"
#include "system.h"
#define _USE_MATH_DEFINES
#include <math.h>

#include <gl\glew.h>
#include <gl\glut.h>

//コンストラクタ
PlayerClass::PlayerClass(void)
{
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
	if(m_InputKeyFlag & E_UP_ARROW_KEY) m_Velocity.m_Vector.y = 0.1;	//↑キー
	if(m_InputKeyFlag & E_LEFT_ARROW_KEY) m_Velocity.m_Vector.x = -0.1;	//←キー
	if(m_InputKeyFlag & E_RIGHT_ARROW_KEY) m_Velocity.m_Vector.x = 0.1;	//→キー
	if(m_InputKeyFlag & E_DOWN_ARROW_KEY) m_Velocity.m_Vector.y = -0.1;	//↓キー

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
}

//////////////////////////////////////////////////////////////////////////////
//public関数
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//概略:
//	初期化
//引数:
//	*position:位置
//	*velocity:速度
//	*accelaration:加速度
// radius:半径
//	flag:フラグ
//戻り値:
//	true:とりあえずtrueを返す
//////////////////////////////////////////////////////////////////////////////
bool PlayerClass::Initialize(POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , double radius , bool flag)
{
	m_Position = *position;	//位置
	m_Velocity = *velocity;	//速度
	m_Accelaration = *accelaration;	//加速度
	m_Radius = radius;	//半径
	m_Flag = flag;	//フラグ
	
	//子を初期化する
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
	RotateObject(GetAngleVelocity());	//無意味に回転させる
	CheckInput();	//キー入力を調べる
	MoveObject();	//移動させる
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

	//中心点を描画
	glBegin(GL_POINTS);
	glVertex2d(Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesX(m_Position.m_Vector.x) ,
		Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesY(m_Position.m_Vector.y));
	glEnd();

	RenderChild();
}