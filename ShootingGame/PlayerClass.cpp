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
	//右肩
	m_Shoulder_R.Initialize(&POSITION(32 , 32) , &VELOCITY() , &ACCELARATION() , &THREE_DIMENSION_VECTOR(5) , &THREE_DIMENSION_VECTOR(0 , 5));
	m_Shoulder_R.SetPosition(&(m_Position.m_Vector + m_Shoulder_R.GetLocalPosition().m_Vector));
	m_Shoulder_R.SetVertex();
	
	//左肩
	m_Shoulder_L.Initialize(&POSITION(-32 , 32) , &VELOCITY() , &ACCELARATION() , &THREE_DIMENSION_VECTOR(5) , &THREE_DIMENSION_VECTOR(0 , 5));
	m_Shoulder_L.SetPosition(&(m_Position.m_Vector + m_Shoulder_L.GetLocalPosition().m_Vector));
	m_Shoulder_L.SetVertex();
	
	//背中
	m_Back.Initialize(&POSITION(0 , 15) , &VELOCITY() , &ACCELARATION() , &THREE_DIMENSION_VECTOR(5) , &THREE_DIMENSION_VECTOR(0 , 10));
	m_Back.SetPosition(&(m_Position.m_Vector + m_Back.GetLocalPosition().m_Vector));
	m_Back.SetVertex();

	//腰
	m_Hip.Initialize(&POSITION(0 , -5) , &VELOCITY() , &ACCELARATION() , &THREE_DIMENSION_VECTOR(20) , &THREE_DIMENSION_VECTOR(0 , 5));
	m_Hip.SetPosition(&(m_Position.m_Vector + m_Hip.GetLocalPosition().m_Vector));
	m_Hip.SetVertex();
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
	//右肩
	m_Shoulder_R.SetPosition(&(m_Position.m_Vector + RotateVector2(m_Shoulder_R.GetLocalPosition().m_Vector.x , m_Shoulder_R.GetLocalPosition().m_Vector.y , m_Angle)));
	m_Shoulder_R.Update();

	//左肩
	m_Shoulder_L.SetPosition(&(m_Position.m_Vector + RotateVector2(m_Shoulder_L.GetLocalPosition().m_Vector.x , m_Shoulder_L.GetLocalPosition().m_Vector.y , m_Angle)));
	m_Shoulder_L.Update();

	//背中
	m_Back.SetPosition(&(m_Position.m_Vector + RotateVector2(m_Back.GetLocalPosition().m_Vector.x , m_Back.GetLocalPosition().m_Vector.y , m_Angle)));
	m_Back.Update();

	//腰
	m_Hip.SetPosition(&(m_Position.m_Vector + RotateVector2(m_Hip.GetLocalPosition().m_Vector.x , m_Hip.GetLocalPosition().m_Vector.y , m_Angle)));
	m_Hip.Update();

	return true;
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	子オブジェクトを描画する
//////////////////////////////////////////////////////////////////////////////
void PlayerClass::RenderChild()
{
	//右肩
	m_Shoulder_R.Render();

	//左肩
	m_Shoulder_L.Render();

	//背中
	m_Back.Render();

	//腰
	m_Hip.Render();
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
//	*semi_long_vector:半長軸ベクトル
//	*semi_short_vector:半短軸ベクトル
//	flag:フラグ
//戻り値:
//	true:とりあえずtrueを返す
//////////////////////////////////////////////////////////////////////////////
bool PlayerClass::Initialize(POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , THREE_DIMENSION_VECTOR* semi_long_vector , THREE_DIMENSION_VECTOR* semi_short_vector , bool flag)
{
	m_Position = *position;
	m_Velocity = *velocity;
	m_Accelaration = *accelaration;
	m_SemiLongVector = *semi_long_vector;
	m_SemiShortVector = *semi_short_vector;

	m_SemiLongAxis = m_SemiLongVector.Magnitude();
	m_SemiShortAxis = m_SemiShortVector.Magnitude();

	SetVertex();

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