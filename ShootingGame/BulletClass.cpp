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
//public関数
//////////////////////////////////////////////////////////////////////////////

//更新（純粋仮想関数）
bool BulletStatePatternClass::Update()
{
	return true;
}

//描画（純粋仮想関数）
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
//public関数
//////////////////////////////////////////////////////////////////////////////

//更新
bool PlayerNormalBulletStateClass::Update()
{
	return true;
}

//描画
void PlayerNormalBulletStateClass::Render()
{
	//色設定（青）
	glColor3f(0 , 0 , 1.f);

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
//EnemyNormalBulletStateClass
//////////////////////////////////////////////////////////////////////////////

EnemyNormalBulletStateClass::EnemyNormalBulletStateClass()
{
}

EnemyNormalBulletStateClass::~EnemyNormalBulletStateClass()
{
}

//////////////////////////////////////////////////////////////////////////////
//public関数
//////////////////////////////////////////////////////////////////////////////

//更新
bool EnemyNormalBulletStateClass::Update()
{
	return true;
}

//描画
void EnemyNormalBulletStateClass::Render()
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
//BulletClass
//////////////////////////////////////////////////////////////////////////////

BulletClass::BulletClass(void)
{
}


BulletClass::~BulletClass(void)
{
}

//////////////////////////////////////////////////////////////////////////////
//public関数
//////////////////////////////////////////////////////////////////////////////

//位置を取る
POSITION BulletClass::GetPosition()
{
	return m_BulletEntity->GetPosition();
}

//初期化
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
//概略:
//	描画
//////////////////////////////////////////////////////////////////////////////
void BulletClass::Render()
{
	m_BulletEntity->Render();
}