#pragma once
#include "DebugSwitch.h"

#include <vector>

//定数の宣言

const int BASE_WINDOW_HEIGHT = 720;
const int BASE_WINDOW_WIDTH = 960;
const int PLAYER_SPEED_ASPECT = 10000000;


//静的変数の宣言

static int WINDOW_HEIGHT = BASE_WINDOW_HEIGHT;	//ウィンドウサイズ縦
static int WINDOW_WIDTH = BASE_WINDOW_WIDTH;	//ウィンドウサイズ横
static double PLAYER_SPEED_Y_ASPECT = 50;	//プレイヤーの速さのy軸比
static double PLAYER_SPEED_X_ASPECT = 50;	//プレイヤーの速さのx軸比

//列挙体の宣言
enum GAME_MODE
{
	GAME_INIT,	//ゲーム初期化
	GAME_PLAY,	//ゲームメイン
	END = 99		//終了
};

//3次元ベクトル
typedef struct THREE_DIMENSION_VECTOR
{
	double x;	//x座標
	double y;	//y座標
	double z;	//z座標

	//コンストラクタ
	THREE_DIMENSION_VECTOR(double x = 0 , double y = 0 , double z = 0)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	//ベクトルの足し算
	THREE_DIMENSION_VECTOR operator + (THREE_DIMENSION_VECTOR obj)
	{
		THREE_DIMENSION_VECTOR ret;
		ret.x = this->x + obj.x;
		ret.y = this->y + obj.y;
		ret.z = this->z + obj.z;
		return ret;
	}

	//ベクトルの足し算
	void operator += (THREE_DIMENSION_VECTOR obj)
	{
		this->x = this->x + obj.x;
		this->y = this->y + obj.y;
		this->z = this->z + obj.z;
	}

	//ベクトルの引き算
	THREE_DIMENSION_VECTOR operator - (THREE_DIMENSION_VECTOR obj)
	{
		THREE_DIMENSION_VECTOR ret;
		ret.x = this->x - obj.x;
		ret.y = this->y - obj.y;
		ret.z = this->z - obj.z;
		return ret;
	}

	//ベクトルの引き算
	void operator -= (THREE_DIMENSION_VECTOR obj)
	{
		this->x = this->x - obj.x;
		this->y = this->y - obj.y;
		this->z = this->z - obj.z;
	}

	//逆ベクトル
	THREE_DIMENSION_VECTOR operator - ()
	{
		THREE_DIMENSION_VECTOR ret;
		ret.x = -this->x;
		ret.y = -this->y;
		ret.z = -this->z;
		return ret;
	}

	//スカラー倍
	THREE_DIMENSION_VECTOR operator * (double obj)
	{
		THREE_DIMENSION_VECTOR ret;
		ret.x = this->x * obj;
		ret.y = this->y * obj;
		ret.z = this->z * obj;
		return ret;
	}

	//スカラー倍
	void operator *= (double obj)
	{
		this->x = this->x * obj;
		this->y = this->y * obj;
		this->z = this->z * obj;
	}

	//成分の設定
	void Set(double x = 0 , double y = 0 , double z = 0)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	//ベクトルの大きさ
	double Magnitude()
	{
		return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	}

	//単位ベクトル
	THREE_DIMENSION_VECTOR GetNomalVector()
	{
		THREE_DIMENSION_VECTOR ret;
		ret.x = this->x / this->Magnitude();
		ret.y = this->y / this->Magnitude();
		ret.z = this->z / this->Magnitude();
		return ret;
	}

	//単位化
	void Nomalize()
	{
		*this = GetNomalVector();
	}
}THREE_DIMENSION_VECTOR;

//位置
typedef struct POSITION
{
	THREE_DIMENSION_VECTOR m_Vector;	//位置ベクトル
		
	//コンストラクタ
	POSITION(double x = 0 , double y = 0 , double z = 0) : m_Vector(x , y , z){}
}POSITION;

//速度
typedef struct VELOCITY
{
	THREE_DIMENSION_VECTOR m_Vector;	//速度ベクトル

	//コンストラクタ
	VELOCITY(double x = 0 , double y = 0 , double z = 0) : m_Vector(x , y , z){}
}VELOCITY;

//加速度
typedef struct ACCELARATION
{
	THREE_DIMENSION_VECTOR m_Vector;	//加速度ベクトル

	//コンストラクタ
	ACCELARATION(double x = 0 , double y = 0 , double z = 0) : m_Vector(x , y , z){}
}ACCELARATION;

//可変長頂点(規定値4頂点）
typedef struct FOUR_VERTEX
{
	POSITION m_VertexPosition[4];	//頂点の座標位置
	unsigned int FactorSize;	//要素数

	FOUR_VERTEX()
	{
		FactorSize = 4;
	}

	unsigned int size()
	{
		return FactorSize;
	}
}FOUR_VERTEX;



//変数の宣言
extern GAME_MODE GameMode;		//ゲームモード指定用変数