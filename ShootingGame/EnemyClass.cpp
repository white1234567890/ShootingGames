#include "EnemyClass.h"
#include <gl\glew.h>
#include <gl\glut.h>
#include "system.h"

#include <fstream>
#include <iostream>
#include <sstream>

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

bool EnemyStatePatternClass::LoadEnemyStatus(POSITION* position)
{
	return true;
}

void EnemyStatePatternClass::MoveObject()
{
}

void EnemyStatePatternClass::ShotBullet()
{
}


//////////////////////////////////////////////////////////////////////////////
//public関数
//////////////////////////////////////////////////////////////////////////////


bool EnemyStatePatternClass::Initialize(POSITION* position)
{
	return true;
}

bool EnemyStatePatternClass::Update()
{
	return true;
}

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

bool EnemyType1Class::LoadEnemyStatus(POSITION* position)
{
	std::ifstream ifs("data/enemy/enemytype1.csv");

	if(ifs.fail()) return false;
	
	std::string EnemyStatus;
	
	for(int i = 0 ; i < 2 ; i++)
	{
		std::getline(ifs , EnemyStatus);
	}
	
	std::string token;
	std::istringstream stream(EnemyStatus);
	std::vector<double> TempVector;
	
	while(getline(stream , token , ','))
	{
		TempVector.push_back(std::stod(token));
	}

	if(TempVector[4] >= TempVector[5])
	{
		BoxClass::Initialize(position , &VELOCITY(TempVector[0] , TempVector[1]) ,
			&ACCELARATION(TempVector[2] , TempVector[3]) , &THREE_DIMENSION_VECTOR(TempVector[4]) , &THREE_DIMENSION_VECTOR(0 , TempVector[5]));
	}
	else
	{
		BoxClass::Initialize(position , &VELOCITY(TempVector[0] , TempVector[1]) ,
			&ACCELARATION(TempVector[2] , TempVector[3]) , &THREE_DIMENSION_VECTOR(0 , TempVector[5]) , &THREE_DIMENSION_VECTOR(TempVector[4]));
	}

	return true;
}

void EnemyType1Class::MoveObject()
{
	m_Position.m_Vector += m_Velocity.m_Vector;
	AccelObject();
}

void EnemyType1Class::ShotBullet()
{
}

//////////////////////////////////////////////////////////////////////////////
//public関数
//////////////////////////////////////////////////////////////////////////////


bool EnemyType1Class::Initialize(POSITION* position)
{
	LoadEnemyStatus(position);
	return true;
}

bool EnemyType1Class::Update()
{
	MoveObject();
	SetVertex();
	return true;
}

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

bool EnemyType2Class::LoadEnemyStatus(POSITION* position)
{
	std::ifstream ifs("data/enemy/enemytype2.csv");

	if(ifs.fail()) return false;
	
	std::string EnemyStatus;
	
	for(int i = 0 ; i < 2 ; i++)
	{
		std::getline(ifs , EnemyStatus);
	}
	
	std::string token;
	std::istringstream stream(EnemyStatus);
	std::vector<double> TempVector;
	
	while(getline(stream , token , ','))
	{
		TempVector.push_back(std::stod(token));
	}

if(TempVector[4] >= TempVector[5])
	{
		BoxClass::Initialize(position , &VELOCITY(TempVector[0] , TempVector[1]) ,
			&ACCELARATION(TempVector[2] , TempVector[3]) , &THREE_DIMENSION_VECTOR(TempVector[4]) , &THREE_DIMENSION_VECTOR(0 , TempVector[5]));
	}
	else
	{
		BoxClass::Initialize(position , &VELOCITY(TempVector[0] , TempVector[1]) ,
			&ACCELARATION(TempVector[2] , TempVector[3]) , &THREE_DIMENSION_VECTOR(0 , TempVector[5]) , &THREE_DIMENSION_VECTOR(TempVector[4]));
	}

	return true;
}

void EnemyType2Class::MoveObject()
{
	m_Position.m_Vector += m_Velocity.m_Vector;
	AccelObject();
}

void EnemyType2Class::ShotBullet()
{
}


//////////////////////////////////////////////////////////////////////////////
//public関数
//////////////////////////////////////////////////////////////////////////////

bool EnemyType2Class::Initialize(POSITION* position)
{
	LoadEnemyStatus(position);
	return true;
}

bool EnemyType2Class::Update()
{
	MoveObject();
	SetVertex();
	return true;
}

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
//EnemyClass
//////////////////////////////////////////////////////////////////////////////

EnemyClass::EnemyClass(void)
{
	m_EnemyType = nullptr;
}


EnemyClass::~EnemyClass(void)
{

}

//////////////////////////////////////////////////////////////////////////////
//public関数
//////////////////////////////////////////////////////////////////////////////

void EnemyClass::Release()
{
	if(m_EnemyType != nullptr)
	{
		delete m_EnemyType;
	}
	m_EnemyType = nullptr;
}

bool EnemyClass::CheckEnemyIsInScreen()
{
	if(m_EnemyType->GetPosition().m_Vector.x < 0 || m_EnemyType->GetPosition().m_Vector.x > WINDOW_WIDTH ||
		m_EnemyType->GetPosition().m_Vector.y < 0 || m_EnemyType->GetPosition().m_Vector.y > WINDOW_HEIGHT)
	{
		return false;
	}

	return true;
}

bool EnemyClass::Initiarize(int enemy_type , POSITION* position)
{
	switch (enemy_type)
	{
	case E_ENEMY_TYPE_1:
		m_EnemyType = new EnemyType1Class;
		break;

	case E_ENEMY_TYPE_2:
		m_EnemyType = new EnemyType2Class;
		break;
	}
	
	m_EnemyType->Initialize(position);

	return true;
}

bool EnemyClass::Update()
{
	m_EnemyType->Update();
	return true;
}

void EnemyClass::Render()
{
	m_EnemyType->Render();
}