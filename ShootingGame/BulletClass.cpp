#include "BulletClass.h"

#include <gl\glew.h>
#include <gl\glut.h>

#include "system.h"


//////////////////////////////////////////////////////////////////////////////
//BulletStatePatternClass
//////////////////////////////////////////////////////////////////////////////

BulletStatePatternClass::BulletStatePatternClass()
{
}

BulletStatePatternClass::~BulletStatePatternClass()
{
}

//////////////////////////////////////////////////////////////////////////////
//public�֐�
//////////////////////////////////////////////////////////////////////////////

//�X�V�i�������z�֐��j
bool BulletStatePatternClass::Update()
{
	return true;
}

//�`��i�������z�֐��j
void BulletStatePatternClass::Render()
{
}

//////////////////////////////////////////////////////////////////////////////
//PlayerNormalBulletStateClass
//////////////////////////////////////////////////////////////////////////////

PlayerNormalBulletStateClass::PlayerNormalBulletStateClass()
{
}

PlayerNormalBulletStateClass::~PlayerNormalBulletStateClass()
{
}

//////////////////////////////////////////////////////////////////////////////
//public�֐�
//////////////////////////////////////////////////////////////////////////////

//�X�V
bool PlayerNormalBulletStateClass::Update()
{
	return true;
}

//�`��
void PlayerNormalBulletStateClass::Render()
{
	//�F�ݒ�i�j
	glColor3f(0 , 0 , 1.f);

	//�l�p��`��
	glBegin(GL_POLYGON);

	//�e���_
	for(unsigned int i = 0 ; i < m_Vertex.size() ; i++)
	{
		glVertex2d(Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesX(m_Vertex.m_VertexPosition[i].m_Vector.x) ,
			Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesY(m_Vertex.m_VertexPosition[i].m_Vector.y));
	}

	glEnd();
}

//////////////////////////////////////////////////////////////////////////////
//EnemyNormalBulletStateClass
//////////////////////////////////////////////////////////////////////////////

EnemyNormalBulletStateClass::EnemyNormalBulletStateClass()
{
}

EnemyNormalBulletStateClass::~EnemyNormalBulletStateClass()
{
}

//////////////////////////////////////////////////////////////////////////////
//public�֐�
//////////////////////////////////////////////////////////////////////////////

//�X�V
bool EnemyNormalBulletStateClass::Update()
{
	return true;
}

//�`��
void EnemyNormalBulletStateClass::Render()
{
	//�F�ݒ�i�΁j
	glColor3f(0 , 1.f , 0);

	//�l�p��`��
	glBegin(GL_POLYGON);

	//�e���_
	for(unsigned int i = 0 ; i < m_Vertex.size() ; i++)
	{
		glVertex2d(Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesX(m_Vertex.m_VertexPosition[i].m_Vector.x) ,
			Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesY(m_Vertex.m_VertexPosition[i].m_Vector.y));
	}

	glEnd();
}

//////////////////////////////////////////////////////////////////////////////
//BulletClass
//////////////////////////////////////////////////////////////////////////////

BulletClass::BulletClass(void)
{
}


BulletClass::~BulletClass(void)
{
}

//////////////////////////////////////////////////////////////////////////////
//public�֐�
//////////////////////////////////////////////////////////////////////////////

//�ʒu�����
POSITION BulletClass::GetPosition()
{
	return m_BulletEntity->GetPosition();
}

//������
bool BulletClass::Initialize(int bullet_type , POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , THREE_DIMENSIONAL_VECTOR* semi_long_vector , THREE_DIMENSIONAL_VECTOR* semi_short_vector)
{
	switch (bullet_type)
	{
	case E_PLAYER_NORMAL:
		m_BulletEntity = new PlayerNormalBulletStateClass;
		break;

	case E_ENEMY_TYPE1:
		m_BulletEntity = new EnemyNormalBulletStateClass;
		break;
	}

	m_BulletEntity->Initialize(position , velocity , accelaration , semi_long_vector , semi_short_vector);
}

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	�`��
//////////////////////////////////////////////////////////////////////////////
void BulletClass::Render()
{
	m_BulletEntity->Render();
}