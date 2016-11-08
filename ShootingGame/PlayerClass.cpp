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
#include "CircleClass.h"

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
//プレイヤーの情報をロード
//引数:
//	file_name:ロードするファイル名
//////////////////////////////////////////////////////////////////////////////
bool PlayerClass::LoadPlayerStatus(int player_type)
{
	//ファイルを読み込む
	std::ifstream ifs("data/player/playerstatus.csv");

	//失敗したらfalseを返す
	if(ifs.fail()) return false;

	//データを読み込むための文字列
	std::string PlayerStatus;
	
	//最初の1行は無視する
	std::getline(ifs , PlayerStatus);

	//引き出したいプレイヤー情報まで行く
	for(int i = 0 ; i <= player_type ; i++)
	{
		std::getline(ifs , PlayerStatus);
	}

	std::string token;	//データ取り出し用のトークン
	std::istringstream stream(PlayerStatus);	//データを一列読み込む文字列
	std::vector<double> TempVector;	//データ変換用配列
	
	//','が来るたびにトークンに文字列を取り出す
	while(getline(stream , token , ','))
	{
		//トークンの文字列を数字に変換する
		TempVector.push_back(std::stod(token));
	}

	//当たり判定の設定
	m_PlayerCollider.Initialize(&m_Position , &m_Velocity , &m_Accelaration ,TempVector[1]);

	//横の方が大きいとき
	if(TempVector[2] >= TempVector[3])
	{
		m_SemiLongVector = THREE_DIMENSIONAL_VECTOR(TempVector[2]);
		m_SemiShortVector = THREE_DIMENSIONAL_VECTOR(0 , TempVector[3]);
	}
	//縦の方が大きいとき
	else
	{
		m_SemiLongVector = THREE_DIMENSIONAL_VECTOR(0 , TempVector[3]);
		m_SemiShortVector = THREE_DIMENSIONAL_VECTOR(TempVector[2]);
	}

	////ショット画像の横の方が大きいとき
	//if(TempVector[6] >= TempVector[7])
	//{
	//	m_Pointer_to_Shoulder_L->SetShotStatus(TempVector[4] , &VELOCITY() , TempVector[5] , &ACCELARATION() , &THREE_DIMENSIONAL_VECTOR(TempVector[6] / 2) , &THREE_DIMENSIONAL_VECTOR(0 , TempVector[7] / 2));
	//	m_Pointer_to_Shoulder_R->SetShotStatus(TempVector[4] , &VELOCITY() , TempVector[5] , &ACCELARATION() , &THREE_DIMENSIONAL_VECTOR(TempVector[6] / 2) , &THREE_DIMENSIONAL_VECTOR(0 , TempVector[7] / 2));
	//}
	////ショット画像の縦の方が大きいとき
	//else
	//{
	//	m_Pointer_to_Shoulder_L->SetShotStatus(TempVector[4] , &VELOCITY() , TempVector[5] , &ACCELARATION() , &THREE_DIMENSIONAL_VECTOR(0 , TempVector[7] / 2) , &THREE_DIMENSIONAL_VECTOR(TempVector[6] / 2));
	//	m_Pointer_to_Shoulder_R->SetShotStatus(TempVector[4] , &VELOCITY() , TempVector[5] , &ACCELARATION() , &THREE_DIMENSIONAL_VECTOR(0 , TempVector[7] / 2) , &THREE_DIMENSIONAL_VECTOR(TempVector[6] / 2));
	//}

	//いらないvectorを開放する
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


/////////////////////////////////////////////////////////////////////////////
//移動処理
//////////////////////////////////////////////////////////////////////////////
void PlayerClass::MoveObject()
{
	//SHIFTキーを押しているとき速さが半分になる
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
//引数:
//	shoulder_l_type
//	shoulder_r_type
//	back_type
//	hip_type
//戻り値:
//	true:初期化に成功
//	false:いずれかのデータのロードが失敗した
//////////////////////////////////////////////////////////////////////////////
bool PlayerClass::InitializeChild(int shoulder_l_type , int shoulder_r_type , int back_type , int hip_type)
{
	//左肩
	if(!m_Pointer_to_Shoulder_L->Initialize(shoulder_l_type , &POSITION(10 , 32) , &VELOCITY() , &ACCELARATION() , this)) return false;
	//右肩
	if(!m_Pointer_to_Shoulder_R->Initialize(shoulder_r_type , &POSITION(-10 , 32) , &VELOCITY() , &ACCELARATION() , this)) return false;
	//背中
	if(!m_Pointer_to_Back->Initialize(back_type , &POSITION(0 , 10) , &VELOCITY() , &ACCELARATION() , this)) return false;
	//腰
	if(!m_Pointer_to_Hip->Initialize(hip_type , &POSITION(0 , -10) , &VELOCITY() , &ACCELARATION() , this)) return false;
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
	//左肩
	m_Pointer_to_Shoulder_L->Update(m_ShotFlag);
	//右肩
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

//////////////////////////////////////////////////////////////////////////////
//概略:
//	プレイヤーの速度を設定する
//引数:
//	x:横軸速度
//	y:縦軸速度
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
//	player_type:プレイヤーキャラクターのタイプ
//	*shoulder_l:左肩パーツへのポインタ
//	shoulder_l_type:左肩パーツのタイプ
//	*shoulder_r:右肩パーツへのポインタ
//	shoulder_r_type:右肩パーツのタイプ
//	*back:背中パーツへのポインタ
//	back_type:背中パーツのタイプ
//	*hip:腰パーツへのポインタ
//	hip_type:腰パーツのタイプ
//	flag:フラグ
//戻り値:
//	true:初期化に成功
//	false:いずれかのファイルのロードが失敗している
//////////////////////////////////////////////////////////////////////////////
bool PlayerClass::Initialize(int player_type ,
		ShoulderPartsClass* shoulder_l , int shoulder_l_type ,
		ShoulderPartsClass* shoulder_r , int shoulder_r_type ,
		BackPartsClass* back , int back_type ,
		HipPartsClass* hip , int hip_type ,
		bool flag = true)
{
	//定位置スタート
	m_Position = POSITION(WINDOW_WIDTH / 2 , WINDOW_HEIGHT / 10);
	//速度0スタート
	m_Velocity.m_Vector = THREE_DIMENSIONAL_VECTOR();
	//加速度0スタート
	m_Accelaration = ACCELARATION();

	//半長軸長
	m_SemiLongAxis = m_SemiLongVector.Magnitude();
	//半短軸長
	m_SemiShortAxis = m_SemiShortVector.Magnitude();

	//頂点の再設定
	SetVertex();

	//子のポインタを記憶する
	m_Pointer_to_Shoulder_L = shoulder_l;	//左肩
	m_Pointer_to_Shoulder_R = shoulder_r;	//右肩
	m_Pointer_to_Back = back;	//背中
	m_Pointer_to_Hip = hip;	//腰

	//プレイヤーのデータをロードする
	if(!LoadPlayerStatus(file_name)) return false;

	//プレイヤーの速さを設定する
	SetPlayerSpeed(SPEED_X_ASPECT * WINDOW_WIDTH * WINDOW_HEIGHT / SPEED_ASPECT , SPEED_Y_ASPECT * WINDOW_WIDTH * WINDOW_HEIGHT / SPEED_ASPECT);

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