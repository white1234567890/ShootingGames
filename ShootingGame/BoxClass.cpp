#include <gl\glew.h>
#include <gl\glut.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include "BoxClass.h"
#include "system.h"

//////////////////////////////////////////////////////////////////////////////
//コンストラクタ
//////////////////////////////////////////////////////////////////////////////
BoxClass::BoxClass(void)
{
	for(int i = 0 ; i < 4 ; i++)
	{
		m_Vertex.m_VertexPosition.push_back(POSITION());
	}
}

//////////////////////////////////////////////////////////////////////////////
//デストラクタ
//////////////////////////////////////////////////////////////////////////////
BoxClass::~BoxClass(void)
{
	std::vector<POSITION> Nullvector;
	m_Vertex.m_VertexPosition.swap(Nullvector);
}

//////////////////////////////////////////////////////////////////////////////
//protected関数
//////////////////////////////////////////////////////////////////////////////

bool BoxClass::Initialize()
{
	return true;
}

void BoxClass::RotateObject(double angle)
{
	RotateVector2(m_SemiLongVector.x , m_SemiLongVector.y , angle);
	RotateVector2(m_SemiShortVector.x , m_SemiShortVector.y , angle);
}

//////////////////////////////////////////////////////////////////////////////
//public関数
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//概略:
//	頂点座標を取得する
//戻り値:
//	m_Vertex:頂点座標
//////////////////////////////////////////////////////////////////////////////
VARIABLE_VERTEX BoxClass::GetVertex()
{
	return m_Vertex;
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	頂点座標を取得する
//引数:
//	i:頂点の配列番号
//戻り値:
//	m_VertexPosition[i]:頂点座標
//////////////////////////////////////////////////////////////////////////////
POSITION BoxClass::GetVertex(unsigned int i)
{
	if(i < m_Vertex.m_VertexPosition.size())
	{
		return m_Vertex.m_VertexPosition[i];
	}
	return m_Vertex.m_VertexPosition[0];
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	頂点数を取得する
//戻り値:
//	m_Vertex.m_VertexPosition.size:頂点数
//////////////////////////////////////////////////////////////////////////////
int BoxClass::GetVertexSize()
{
	return m_Vertex.m_VertexPosition.size();
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	矩形の半長軸の長さを取得する
//戻り値:
//	m_SemiLongAxis:矩形の半長軸の長さ
//////////////////////////////////////////////////////////////////////////////
double BoxClass::GetSemiLongAxis()
{
	return m_SemiLongAxis;
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	矩形の半短軸の長さを取得する
//戻り値:
//	m_SemiShortAxis:矩形の半短軸の長さ
//////////////////////////////////////////////////////////////////////////////
double BoxClass::GetSemiShortAxis()
{
	return m_SemiShortAxis;
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	矩形の半長軸のベクトルを取得する
//戻り値:
//	m_SemiLongVector:矩形の半長軸のベクトル
//////////////////////////////////////////////////////////////////////////////
THREE_DIMENSION_VECTOR BoxClass::GetSemiLongVector()
{
	return m_SemiLongVector;
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	矩形の半短軸のベクトルを取得する
//戻り値:
//	m_SemiShortVector:矩形の半短軸のベクトル
//////////////////////////////////////////////////////////////////////////////
THREE_DIMENSION_VECTOR BoxClass::GetSemiShortVector()
{
	return m_SemiShortVector;
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	矩形の4つの頂点を算出する
//////////////////////////////////////////////////////////////////////////////
void BoxClass::SetVertex()
{
	m_Vertex.m_VertexPosition[0].m_Vector.Set(m_Position.m_Vector.x + m_SemiLongVector.x + m_SemiShortVector.x , 
		m_Position.m_Vector.y + m_SemiLongVector.y + m_SemiShortVector.y , 0);
	m_Vertex.m_VertexPosition[1].m_Vector.Set(m_Position.m_Vector.x + m_SemiLongVector.x - m_SemiShortVector.x ,
		m_Position.m_Vector.y + m_SemiLongVector.y - m_SemiShortVector.y , 0);
	m_Vertex.m_VertexPosition[2].m_Vector.Set(m_Position.m_Vector.x - m_SemiLongVector.x - m_SemiShortVector.x ,
		m_Position.m_Vector.y - m_SemiLongVector.y - m_SemiShortVector.y , 0);
	m_Vertex.m_VertexPosition[3].m_Vector.Set(m_Position.m_Vector.x - m_SemiLongVector.x + m_SemiShortVector.x ,
		m_Position.m_Vector.y - m_SemiLongVector.y + m_SemiShortVector.y , 0);
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	更新
//////////////////////////////////////////////////////////////////////////////
bool BoxClass::Update()
{
	RotateObject(M_PI / 360 * 0.1);
	MoveObject();
	SetVertex();
	AccelObject();
	return true;
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
bool BoxClass::Initialize(POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , THREE_DIMENSION_VECTOR* semi_long_vector , THREE_DIMENSION_VECTOR* semi_short_vector , bool flag)
{
	m_Position = *position;
	m_Velocity = *velocity;
	m_Accelaration = *accelaration;
	m_SemiLongVector = *semi_long_vector;
	m_SemiShortVector = *semi_short_vector;

	m_SemiLongAxis = m_SemiLongVector.Magnitude();
	m_SemiShortAxis = m_SemiShortVector.Magnitude();

	SetVertex();

	return true;
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	描画
//////////////////////////////////////////////////////////////////////////////
void BoxClass::Render()
{
	//色設定（白）
	glColor3f(1.f , 1.f , 1.f);

	//中心点を描画
	glBegin(GL_POINTS);
	glVertex2d(Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesX(m_Position.m_Vector.x) ,
		Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesY(m_Position.m_Vector.y));
	glEnd();

	//四角を描画
	glBegin(GL_LINE_LOOP);

	//各頂点
	for(unsigned int i = 0 ; i < m_Vertex.m_VertexPosition.size() ; i++)
	{
		glVertex2d(Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesX(m_Vertex.m_VertexPosition[i].m_Vector.x) ,
			Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesY(m_Vertex.m_VertexPosition[i].m_Vector.y));
	}

	glEnd();
}