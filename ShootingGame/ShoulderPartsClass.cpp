#include "ShoulderPartsClass.h"

#include <gl\glew.h>
#include <gl\glut.h>

#include "system.h"

//実体化
ShoulderPartsClass TestShoulderL;
ShoulderPartsClass TestShoulderR;

ShoulderPartsClass::ShoulderPartsClass(void)
{
	m_Pointer_to_Parent = NULL;
}


ShoulderPartsClass::~ShoulderPartsClass(void)
{
}

bool ShoulderPartsClass::Initialize(POSITION* local_position , VELOCITY* local_velocity , ACCELARATION* local_accelaration , THREE_DIMENSION_VECTOR* semi_long_vector , THREE_DIMENSION_VECTOR* semi_short_vector , PlayerClass* player , bool flag)
{
	m_Position = *local_position;
	m_Velocity = *local_velocity;
	m_Accelaration = *local_accelaration;
	m_SemiLongVector = *semi_long_vector;
	m_SemiShortVector = *semi_short_vector;

	m_SemiLongAxis = m_SemiLongVector.Magnitude();
	m_SemiShortAxis = m_SemiShortVector.Magnitude();

	SetVertex();

	m_Pointer_to_Parent = player;

	return true;
}

void ShoulderPartsClass::Render(POSITION* world_position)
{
	//色設定（赤）
	glColor3f(1.f , 0 , 0);

	//四角を描画
	glBegin(GL_POLYGON);

	//各頂点
	for(unsigned int i = 0 ; i < m_Vertex.size() ; i++)
	{
		glVertex2d(Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesX(world_position->m_Vector.x + m_Vertex.m_VertexPosition[i].m_Vector.x) ,
			Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesY(world_position->m_Vector.y + m_Vertex.m_VertexPosition[i].m_Vector.y));
	}

	glEnd();
}