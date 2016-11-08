#include "EnemyClass.h"
#include <gl\glew.h>
#include <gl\glut.h>
#include "system.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "WaveManagerClass.h"

//////////////////////////////////////////////////////////////////////////////
//EnemyStatePatternClass
//////////////////////////////////////////////////////////////////////////////

EnemyStatePatternClass::EnemyStatePatternClass()
{
}

EnemyStatePatternClass::~EnemyStatePatternClass()
{
}

//////////////////////////////////////////////////////////////////////////////
//protected関数
//////////////////////////////////////////////////////////////////////////////

//敵情報をロード（純粋仮想関数）
bool EnemyStatePatternClass::LoadEnemyStatus(WaveManagerClass *wave_manager , POSITION* position)
{
	return true;
}

//敵の位置を移動（純粋仮想関数）
void EnemyStatePatternClass::MoveObject()
{
}

//敵が弾を撃つ（純粋仮想関数）
void EnemyStatePatternClass::ShotBullet()
{
}

/////////////////////////////////////////////////////////////////////////////
//敵とプレイヤーの弾の当たり判定
//////////////////////////////////////////////////////////////////////////////
bool EnemyStatePatternClass::CheckHitEnemy_and_PlayerBullet(PlayerBulletManagerClass *player_bullet_manager)
{
	if(player_bullet_manager->m_Bullet.ToBegin())
	{
		do
		{
			if(CheckHitBoxandBox(&player_bullet_manager->m_Bullet.GetCurrentNode() , this)) 
			{
				std::cout << "Hit!" << std::endl;
				return true;
			}
		}while(player_bullet_manager->m_Bullet.Next());
	}
	
	return false;
}

//////////////////////////////////////////////////////////////////////////////
//public関数
//////////////////////////////////////////////////////////////////////////////

//初期化（純粋仮想関数）
bool EnemyStatePatternClass::Initialize(WaveManagerClass *wave_manager , POSITION* position)
{
	return true;
}

//更新（純粋仮想関数）
bool EnemyStatePatternClass::Update(PlayerBulletManagerClass *player_bullet_manager)
{
	return true;
}

//描画（純粋仮想関数）
void EnemyStatePatternClass::Render()
{
}

//////////////////////////////////////////////////////////////////////////////
//EnemyType1Class
//////////////////////////////////////////////////////////////////////////////

EnemyType1Class::EnemyType1Class()
{
}

EnemyType1Class::~EnemyType1Class()
{
}

//////////////////////////////////////////////////////////////////////////////
//private関数
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//敵情報をロード
//引数:
//	wave_manager:ウェーブマネージャー
//	position:敵生成位置
//	true:敵情報のロードに成功
//	false:敵情報のロードに失敗
//////////////////////////////////////////////////////////////////////////////
bool EnemyType1Class::LoadEnemyStatus(WaveManagerClass *wave_manager , POSITION* position)
{
	//読み込むファイル名を指定
	std::string FileName = "data/" + wave_manager->GetNowStage() + "/enemy/enemytype1.csv";

	//ファイルを読み込む
	std::ifstream ifs(FileName);

	//読み込みに失敗したらfalseを返す
	if(ifs.fail()) return false;
	
	std::string EnemyStatus;	//読み込んだ文字列を入れる
	
	//最初の1行は無視する
	for(int i = 0 ; i < 2 ; i++)
	{
		std::getline(ifs , EnemyStatus);
	}
	
	std::string token;	//データ分割用トークン
	std::istringstream stream(EnemyStatus);	//読み込む文字列
	std::vector<double> TempVector;	//文字列を浮動小数点数に直す
	
	//','が来るたびにトークンに文字を読み込む
	while(getline(stream , token , ','))
	{
		//文字を数字に直す
		TempVector.push_back(std::stod(token));
	}

	//画像が横長の時
	if(TempVector[1] >= TempVector[2])
	{
		//生成位置が真ん中より←の時
		if(position->m_Vector.x < WINDOW_WIDTH / 2)
		{
			//加速度をそのまま初期化
			BoxClass::Initialize(position , &VELOCITY(0 , -TempVector[0]) ,
				&ACCELARATION(TempVector[3] , TempVector[4]) , &THREE_DIMENSIONAL_VECTOR(TempVector[1]) , &THREE_DIMENSIONAL_VECTOR(0 , TempVector[2]));
		}
		//生成位置が真ん中より→の時
		else if(position->m_Vector.x > WINDOW_WIDTH / 2)
		{
			//加速度を逆にして初期化
			BoxClass::Initialize(position , &VELOCITY(0 , -TempVector[0]) ,
				&ACCELARATION(-TempVector[3] , TempVector[4]) , &THREE_DIMENSIONAL_VECTOR(TempVector[1]) , &THREE_DIMENSIONAL_VECTOR(0 , TempVector[2]));
		}
		//生成位置が真ん中の時
		else
		{
			//加速度を0にして初期化
			BoxClass::Initialize(position , &VELOCITY(0 , -TempVector[0]) ,
				&ACCELARATION() , &THREE_DIMENSIONAL_VECTOR(TempVector[1]) , &THREE_DIMENSIONAL_VECTOR(0 , TempVector[2]));
		}
	}
	//画像が縦長の時
	else
	{
		//生成位置が真ん中より←の時
		if(position->m_Vector.x < WINDOW_WIDTH / 2)
		{
			//加速度をそのまま初期化
			BoxClass::Initialize(position , &VELOCITY(0 , -TempVector[0]) ,
				&ACCELARATION(TempVector[3] , TempVector[4]) , &THREE_DIMENSIONAL_VECTOR(0 , TempVector[2]) , &THREE_DIMENSIONAL_VECTOR(TempVector[1]));
		}
		//生成位置が真ん中より→の時
		else if(position->m_Vector.x > WINDOW_WIDTH / 2)
		{
			//加速度を逆にして初期化
			BoxClass::Initialize(position , &VELOCITY(0 , -TempVector[0]) ,
				&ACCELARATION(-TempVector[3] , TempVector[4]) , &THREE_DIMENSIONAL_VECTOR(0 , TempVector[2]) , &THREE_DIMENSIONAL_VECTOR(TempVector[1]));
		}
		//生成位置が真ん中の時
		else
		{
			//加速度を0にして初期化
			BoxClass::Initialize(position , &VELOCITY(0 , -TempVector[0]) ,
				&ACCELARATION() , &THREE_DIMENSIONAL_VECTOR(0 , TempVector[2]) , &THREE_DIMENSIONAL_VECTOR(TempVector[1]));
		}
	}

	//移動の速さを決定
	m_Speed = TempVector[0];

	//使ったvectorを開放する
	ReleaseVector(TempVector);

	return true;
}

//////////////////////////////////////////////////////////////////////////////
//敵の位置を移動
//////////////////////////////////////////////////////////////////////////////
void EnemyType1Class::MoveObject()
{
	//敵位置が画面の4/5より↓の時
	if(m_Position.m_Vector.y < 0.8 * WINDOW_HEIGHT)
	{
		//1秒経ったら
		if(TimeCount() > 60)
		{
			//位置を移動させる
			m_Position.m_Vector += m_Velocity.m_Vector;

			//加速度から速度を出す
			AccelObject();

			//速度を速さに合わせる
			THREE_DIMENSIONAL_VECTOR TempVelocity = GetVelocity().m_Vector;
			TempVelocity.Nomalize();
			SetVelocity(&(TempVelocity * m_Speed));
		}
	}
	else
		//敵位置画面の4/5より↑の時
	{
		//↓に進む
		m_Position.m_Vector += m_Velocity.m_Vector;
	}
}

//////////////////////////////////////////////////////////////////////////////
//敵が弾を撃つ
//////////////////////////////////////////////////////////////////////////////
void EnemyType1Class::ShotBullet()
{
}

//////////////////////////////////////////////////////////////////////////////
//public関数
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//初期化
//引数:
//	wave_manager:ウェーブマネージャー
//	position:敵生成位置
//戻り値:
//	true:敵情報のロードに成功
//	false:敵情報のロードに失敗
//////////////////////////////////////////////////////////////////////////////
bool EnemyType1Class::Initialize(WaveManagerClass *wave_manager , POSITION* position)
{
	//敵情報をロード
	LoadEnemyStatus(wave_manager , position);
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//更新
//////////////////////////////////////////////////////////////////////////////
bool EnemyType1Class::Update(PlayerBulletManagerClass *player_bullet_manager)
{
	//敵を移動させる
	MoveObject();
	//頂点情報を設定する
	SetVertex();
	//当たり判定を取る
	if(CheckHitEnemy_and_PlayerBullet(player_bullet_manager)) return false;
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//描画
//////////////////////////////////////////////////////////////////////////////
void EnemyType1Class::Render()
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
}

//////////////////////////////////////////////////////////////////////////////
//EnemyType２Class
//////////////////////////////////////////////////////////////////////////////

EnemyType2Class::EnemyType2Class()
{
}

EnemyType2Class::~EnemyType2Class()
{
}

//////////////////////////////////////////////////////////////////////////////
//private関数
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//敵情報をロード
//引数:
//	wave_manager:ウェーブマネージャー
//	position:敵生成位置
//	true:敵情報のロードに成功
//	false:敵情報のロードに失敗
//////////////////////////////////////////////////////////////////////////////
bool EnemyType2Class::LoadEnemyStatus(WaveManagerClass *wave_manager , POSITION* position)
{
	//読み込むファイル名を指定
	std::string FileName = "data/" + wave_manager->GetNowStage() + "/enemy/enemytype2.csv";
	
	//ファイルを読み込む
	std::ifstream ifs(FileName);

	//読み込みに失敗したらfalseを返す
	if(ifs.fail()) return false;
	
	std::string EnemyStatus;	//読み込んだ文字列を入れる
	
	//最初の1行は無視する
	for(int i = 0 ; i < 2 ; i++)
	{
		std::getline(ifs , EnemyStatus);
	}
	
	std::string token;	//データ分割用トークン
	std::istringstream stream(EnemyStatus);	//読み込む文字列
	std::vector<double> TempVector;	//文字列を浮動小数点数に直す
	
	//','が来るたびにトークンに文字を読み込む
	while(getline(stream , token , ','))
	{
		//文字を数字に直す
		TempVector.push_back(std::stod(token));
	}

	//画像が横長の時
	if(TempVector[1] >= TempVector[2])
	{
		//生成位置が真ん中より←の時
		if(position->m_Vector.x < WINDOW_WIDTH / 2)
		{
			//加速度をそのまま初期化
			BoxClass::Initialize(position , &VELOCITY(0 , -TempVector[0]) ,
				&ACCELARATION(TempVector[3] , TempVector[4]) , &THREE_DIMENSIONAL_VECTOR(TempVector[1]) , &THREE_DIMENSIONAL_VECTOR(0 , TempVector[2]));
		}
		//生成位置が真ん中より→の時
		else if(position->m_Vector.x > WINDOW_WIDTH / 2)
		{
			//加速度を逆にして初期化
			BoxClass::Initialize(position , &VELOCITY(0 , -TempVector[0]) ,
				&ACCELARATION(-TempVector[3] , TempVector[4]) , &THREE_DIMENSIONAL_VECTOR(TempVector[1]) , &THREE_DIMENSIONAL_VECTOR(0 , TempVector[2]));
		}
		//生成位置が真ん中の時
		else
		{
			//加速度を0にして初期化
			BoxClass::Initialize(position , &VELOCITY(0 , -TempVector[0]) ,
				&ACCELARATION() , &THREE_DIMENSIONAL_VECTOR(TempVector[1]) , &THREE_DIMENSIONAL_VECTOR(0 , TempVector[2]));
		}
	}
	//画像が縦長の時
	else
	{
		//生成位置が真ん中より←の時
		if(position->m_Vector.x < WINDOW_WIDTH / 2)
		{
			//加速度をそのまま初期化
			BoxClass::Initialize(position , &VELOCITY(0 , -TempVector[0]) ,
				&ACCELARATION(TempVector[3] , TempVector[4]) , &THREE_DIMENSIONAL_VECTOR(0 , TempVector[2]) , &THREE_DIMENSIONAL_VECTOR(TempVector[1]));
		}
		//生成位置が真ん中より→の時
		else if(position->m_Vector.x > WINDOW_WIDTH / 2)
		{
			//加速度を逆にして初期化
			BoxClass::Initialize(position , &VELOCITY(0 , -TempVector[0]) ,
				&ACCELARATION(-TempVector[3] , TempVector[4]) , &THREE_DIMENSIONAL_VECTOR(0 , TempVector[2]) , &THREE_DIMENSIONAL_VECTOR(TempVector[1]));
		}
		//生成位置が真ん中の時
		else
		{
			//加速度を0にして初期化
			BoxClass::Initialize(position , &VELOCITY(0 , -TempVector[0]) ,
				&ACCELARATION() , &THREE_DIMENSIONAL_VECTOR(0 , TempVector[2]) , &THREE_DIMENSIONAL_VECTOR(TempVector[1]));
		}
	}

	//移動の速さを決定
	m_Speed = TempVector[0];

	//使ったvectorを開放する
	ReleaseVector(TempVector);

	return true;
}

//////////////////////////////////////////////////////////////////////////////
//敵の位置を移動
//////////////////////////////////////////////////////////////////////////////
void EnemyType2Class::MoveObject()
{
	//敵位置が画面の4/5より↓の時
	if(m_Position.m_Vector.y < 0.8 * WINDOW_HEIGHT)
	{
		//1秒経ったら
		if(TimeCount() > 60)
		{
			//位置を移動させる
			m_Position.m_Vector += m_Velocity.m_Vector;

			//加速度から速度を出す
			AccelObject();

			//速度を速さに合わせる
			THREE_DIMENSIONAL_VECTOR TempVelocity = GetVelocity().m_Vector;
			TempVelocity.Nomalize();
			SetVelocity(&(TempVelocity * m_Speed));
		}
	}
	else
		//敵位置画面の4/5より↑の時
	{
		//↓に進む
		m_Position.m_Vector += m_Velocity.m_Vector;
	}
}

//////////////////////////////////////////////////////////////////////////////
//敵が弾を撃つ
//////////////////////////////////////////////////////////////////////////////
void EnemyType2Class::ShotBullet()
{
}


//////////////////////////////////////////////////////////////////////////////
//public関数
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//初期化
//引数:
//	wave_manager:ウェーブマネージャー
//	position:敵生成位置
//戻り値:
//	true:敵情報のロードに成功
//	false:敵情報のロードに失敗
//////////////////////////////////////////////////////////////////////////////
bool EnemyType2Class::Initialize(WaveManagerClass *wave_manager , POSITION* position)
{
	//敵情報をロード
	LoadEnemyStatus(wave_manager , position);
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//更新
//////////////////////////////////////////////////////////////////////////////
bool EnemyType2Class::Update(PlayerBulletManagerClass *player_bullet_manager)
{
	//敵を移動させる
	MoveObject();
	//頂点情報を設定する
	SetVertex();
	//当たり判定を取る
	if(CheckHitEnemy_and_PlayerBullet(player_bullet_manager)) return false;
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//描画
//////////////////////////////////////////////////////////////////////////////
void EnemyType2Class::Render()
{
	//色設定（緑）
	glColor3f(0 , 1.f , 0);

	//四角を描画
	glBegin(GL_POLYGON);

	//各頂点
	for(unsigned int i = 0 ; i < m_Vertex.size() ; i++)
	{
		glVertex2d(Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesX(m_Vertex.m_VertexPosition[i].m_Vector.x) ,
			Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesY(m_Vertex.m_VertexPosition[i].m_Vector.y));
	}

	glEnd();
}

//////////////////////////////////////////////////////////////////////////////
//EnemyContextClass
//////////////////////////////////////////////////////////////////////////////

EnemyContextClass::EnemyContextClass(void)
{
	m_EnemyType = nullptr;	//敵実体にnullポインタを突っ込む
}


EnemyContextClass::~EnemyContextClass(void)
{

}

//////////////////////////////////////////////////////////////////////////////
//public関数
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//開放
//////////////////////////////////////////////////////////////////////////////
void EnemyContextClass::Release()
{
	//敵の実体がnullじゃないとき
	if(m_EnemyType != nullptr)
	{
		//敵の実体を消去する
		delete m_EnemyType;
	}

	//敵の実体にnullを入れる
	m_EnemyType = nullptr;
}

//////////////////////////////////////////////////////////////////////////////
	//敵が画面内にいるかチェックする
	//////////////////////////////////////////////////////////////////////////////
bool EnemyContextClass::CheckEnemyIsInScreen()
{
	//敵の位置が画面の下左右より外側にいるとき
	if(m_EnemyType->GetPosition().m_Vector.x < 0 || m_EnemyType->GetPosition().m_Vector.x > WINDOW_WIDTH ||
		m_EnemyType->GetPosition().m_Vector.y < 0)
	{
		//falseを返す
		return false;
	}

	//trueを返す
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//初期化
//引数:
//	wave_manager:ウェーブマネージャー
//	enemy_type:的タイプ
//	position:生成位置
//戻り値:
//	true:敵情報のロードに成功
//	false:敵情報のロードに失敗
//////////////////////////////////////////////////////////////////////////////
bool EnemyContextClass::Initiarize(WaveManagerClass *wave_manager , int enemy_type , POSITION* position)
{
	//敵タイプによって生成するステートを変化させる
	switch (enemy_type)
	{
	case E_ENEMY_TYPE_1:
		m_EnemyType = new EnemyType1Class;
		break;

	case E_ENEMY_TYPE_2:
		m_EnemyType = new EnemyType2Class;
		break;
	}
	
	//敵の初期化をする
	m_EnemyType->Initialize(wave_manager , position);

	return true;
}


//////////////////////////////////////////////////////////////////////////////
//更新
//////////////////////////////////////////////////////////////////////////////
bool EnemyContextClass::Update(PlayerBulletManagerClass *player_bullet_manager)
{
	if(!m_EnemyType->Update(player_bullet_manager)) return false;
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//描画
//////////////////////////////////////////////////////////////////////////////
void EnemyContextClass::Render()
{
	m_EnemyType->Render();
}