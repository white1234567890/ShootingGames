#include "ShoulderPartsClass.h"

#include <gl\glew.h>
#include <gl\glut.h>

#include "system.h"

#include "PlayerBulletManagerClass.h"
ShoulderPartsClass::ShoulderPartsClass(void)
{
	m_Pointer_to_Parent = NULL;
}


ShoulderPartsClass::~ShoulderPartsClass(void)
{
}

void ShoulderPartsClass::SetShotStatus(double barrel_range , VELOCITY* velocity , double shot_speed , ACCELARATION* accelaration , THREE_DIMENSION_VECTOR* shot_semi_long_vector , THREE_DIMENSION_VECTOR* shot_semi_short_vector)
{
	m_BarrelRange = barrel_range;
	m_ShotVelocity = *velocity;
	m_ShotSpeed = shot_speed;
	m_ShotAccelaration = *accelaration;
	m_ShotSemiLongVector = *shot_semi_long_vector;
	m_ShotSemiShortVector = *shot_semi_short_vector;
}

POSITION ShoulderPartsClass::GetShotPosition()
{
	return m_ShotPosition;
}

VELOCITY ShoulderPartsClass::GetShotVelocity()
{
	return m_ShotVelocity;
}
	
ACCELARATION ShoulderPartsClass::GetShotAccelaration()
{
	return m_ShotAccelaration;
}
	
THREE_DIMENSION_VECTOR ShoulderPartsClass::GetShotSemiLongVector()
{
	return m_ShotSemiLongVector;
}
	
THREE_DIMENSION_VECTOR ShoulderPartsClass::GetShotSemiShortVector()
{
	return m_ShotSemiShortVector;
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

	m_ForwardVector.Set(0 , 1);

	SetVertex();

	m_Pointer_to_Parent = player;

	return true;
}

bool ShoulderPartsClass::Update(bool shot_flag)
{
	m_ShotPosition.m_Vector = m_Pointer_to_Parent->GetPosition().m_Vector + m_Position.m_Vector + RotateVector2(m_ForwardVector.x , m_ForwardVector.y , m_Angle) * m_BarrelRange;
	m_ShotVelocity.m_Vector = RotateVector2(m_ForwardVector.x , m_ForwardVector.y , m_Angle) * m_ShotSpeed;

	if(shot_flag)
	{
		cl_PlayerBulletManager->CreateBullet(&m_ShotPosition , &m_ShotVelocity , &m_ShotAccelaration , &m_ShotSemiLongVector , &m_ShotSemiShortVector);
	}

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