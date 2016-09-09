#include "BoxChildClass.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <gl\glew.h>
#include <gl\glut.h>

#include "system.h"


BoxChildClass::BoxChildClass(void)
{
}


BoxChildClass::~BoxChildClass(void)
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
//	*semi_long_vector:半長軸ベクトル
//	*semi_short_vector:半短軸ベクトル
//	flag:フラグ
//戻り値:
//	true:とりあえずtrueを返す
//////////////////////////////////////////////////////////////////////////////
bool BoxChildClass::Initialize(POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , THREE_DIMENSION_VECTOR* semi_long_vector , THREE_DIMENSION_VECTOR* semi_short_vector , bool flag)
{
	m_LocalPosition = *position;
	m_LocalVelocity = *velocity;
	m_LocalAccelaration = *accelaration;
	m_SemiLongVector = *semi_long_vector;
	m_SemiShortVector = *semi_short_vector;

	m_SemiLongAxis = m_SemiLongVector.Magnitude();
	m_SemiShortAxis = m_SemiShortVector.Magnitude();

	SetVertex();

	return true;
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	更新
//////////////////////////////////////////////////////////////////////////////
bool BoxChildClass::Update()
{
	SetVertex();
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	描画
//////////////////////////////////////////////////////////////////////////////
void BoxChildClass::Render()
{
		//色設定（赤）
	glColor3f(1.f , 0 , 0);

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