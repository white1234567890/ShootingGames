#include "HipPartsClass.h"

#include <gl\glew.h>
#include <gl\glut.h>

#include <fstream>
#include <sstream>

#include "system.h"
HipPartsClass::HipPartsClass(void)
{
}


HipPartsClass::~HipPartsClass(void)
{
}

//////////////////////////////////////////////////////////////////////////////
//private関数
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//腰パーツのデータをロードする
//引数:
//	ロードするパーツタイプ
//戻り値:
//	true:データをロードした
//	false:データのロードに失敗した
//////////////////////////////////////////////////////////////////////////////
bool HipPartsClass::LoadHipPartsData(int hip_type)
{
	//ファイルを読み込む
	std::ifstream ifs("data/player/HipPartsParameter.csv");

	//失敗したらfalseを返す
	if(ifs.fail()) return false;

	//データを読み込むための文字列
	std::string HipPartsParameters;

	//最初の1行は無視する
	std::getline(ifs , HipPartsParameters);

	//引き出したいパーツ情報まで行く
	for(int i = 0 ; i <= hip_type ; i++)
	{
		std::getline(ifs , HipPartsParameters);
	}

	std::string token;	//データ取り出し用のトークン
	std::istringstream stream(HipPartsParameters);	//データを一列読み込む文字列
	std::vector<double> TempVector;	//データ変換用配列
	
	//','が来るたびにトークンに文字列を取り出す
	while(getline(stream , token , ','))
	{
		//トークンの文字列を数字に変換する
		TempVector.push_back(std::stod(token));
	}

	//速さの設定
	SPEED_X_ASPECT = TempVector[1];
	SPEED_Y_ASPECT = TempVector[2];

	//画像の横の方が大きいとき
	if(TempVector[2] >= TempVector[3])
	{
		m_SemiLongVector = THREE_DIMENSIONAL_VECTOR(TempVector[3]);
		m_SemiShortVector = THREE_DIMENSIONAL_VECTOR(0 , TempVector[4]);
	}
	//画像の縦の方が大きいとき
	else
	{
		m_SemiLongVector = THREE_DIMENSIONAL_VECTOR(0 , TempVector[4]);
		m_SemiShortVector = THREE_DIMENSIONAL_VECTOR(TempVector[3]);
	}

	m_SemiLongAxis = m_SemiLongVector.Magnitude();
	m_SemiShortAxis = m_SemiShortVector.Magnitude();

	SetVertex();

	
	//いらないvectorを開放する
	ReleaseVector(TempVector);
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//public関数
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//概略:
//	初期化
//引数:
//	hip_type:装着する腰パーツのタイプ
//	local_position:プレイヤーから見た位置
//	local_velocity:プレイヤーから見た速度
//	local_accelaration:プレイヤーから見た加速度
//	player:プレイヤーへのポインタ
//	flag:描画フラグ
//戻り値:
//	true:成功
//	false:失敗
//////////////////////////////////////////////////////////////////////////////
bool HipPartsClass::Initialize(int hip_type , POSITION* local_position , VELOCITY* local_velocity , ACCELARATION* local_accelaration , PlayerClass* player , bool flag)
{
	m_Position = *local_position;
	m_Velocity = *local_velocity;
	m_Accelaration = *local_accelaration;

	m_Pointer_to_Parent = player;

	if(!LoadHipPartsData(hip_type)) return false;

	return true;
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	描画
//引数:
//	player_world_position:プレイヤーの位置
//////////////////////////////////////////////////////////////////////////////
void HipPartsClass::Render(POSITION* player_world_positoin)
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

