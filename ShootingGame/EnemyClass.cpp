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
//protected�֐�
//////////////////////////////////////////////////////////////////////////////

bool EnemyStatePatternClass::LoadEnemyStatus(WaveManagerClass *wave_manager , POSITION* position)
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
//public�֐�
//////////////////////////////////////////////////////////////////////////////


bool EnemyStatePatternClass::Initialize(WaveManagerClass *wave_manager , POSITION* position)
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
//private�֐�
//////////////////////////////////////////////////////////////////////////////

bool EnemyType1Class::LoadEnemyStatus(WaveManagerClass *wave_manager , POSITION* position)
{
	std::string FileName = "data/" + wave_manager->GetNowStage() + "/enemy/enemytype1.csv";

	std::ifstream ifs(FileName);

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
		if(position->m_Vector.x < WINDOW_WIDTH / 2)
		{
			BoxClass::Initialize(position , &VELOCITY(TempVector[0] , TempVector[1]) ,
				&ACCELARATION(TempVector[2] , TempVector[3]) , &THREE_DIMENSION_VECTOR(TempVector[4]) , &THREE_DIMENSION_VECTOR(0 , TempVector[5]));
		}
		else if(position->m_Vector.x > WINDOW_WIDTH / 2)
		{
			BoxClass::Initialize(position , &VELOCITY(TempVector[0] , TempVector[1]) ,
				&ACCELARATION(-TempVector[2] , TempVector[3]) , &THREE_DIMENSION_VECTOR(TempVector[4]) , &THREE_DIMENSION_VECTOR(0 , TempVector[5]));
		}
		else
		{
			BoxClass::Initialize(position , &VELOCITY(TempVector[0] , TempVector[1]) ,
				&ACCELARATION() , &THREE_DIMENSION_VECTOR(TempVector[4]) , &THREE_DIMENSION_VECTOR(0 , TempVector[5]));
		}
	}
	else
	{
		if(position->m_Vector.x < WINDOW_WIDTH / 2)
		{
			BoxClass::Initialize(position , &VELOCITY(TempVector[0] , TempVector[1]) ,
				&ACCELARATION(TempVector[2] , TempVector[3]) , &THREE_DIMENSION_VECTOR(0 , TempVector[5]) , &THREE_DIMENSION_VECTOR(TempVector[4]));
		}
		else if(position->m_Vector.x > WINDOW_WIDTH / 2)
		{
			BoxClass::Initialize(position , &VELOCITY(TempVector[0] , TempVector[1]) ,
				&ACCELARATION(-TempVector[2] , TempVector[3]) , &THREE_DIMENSION_VECTOR(0 , TempVector[5]) , &THREE_DIMENSION_VECTOR(TempVector[4]));
		}
		else
		{
			BoxClass::Initialize(position , &VELOCITY(TempVector[0] , TempVector[1]) ,
				&ACCELARATION() , &THREE_DIMENSION_VECTOR(0 , TempVector[5]) , &THREE_DIMENSION_VECTOR(TempVector[4]));
		}
	}

	m_Speed = TempVector[6];

	ReleaseVector(TempVector);

	return true;
}

void EnemyType1Class::MoveObject()
{
	if(m_Position.m_Vector.y < 0.8 * WINDOW_HEIGHT)
	{
		if(TimeCount() > 60)
		{
			m_Position.m_Vector += m_Velocity.m_Vector;

			AccelObject();

			THREE_DIMENSION_VECTOR TempVelocity = GetVelocity().m_Vector;
			TempVelocity.Nomalize();
			SetVelocity(&(TempVelocity * m_Speed));
		}
	}
	else
	{
		m_Position.m_Vector += m_Velocity.m_Vector;
	}

}

void EnemyType1Class::ShotBullet()
{
}

//////////////////////////////////////////////////////////////////////////////
//public�֐�
//////////////////////////////////////////////////////////////////////////////


bool EnemyType1Class::Initialize(WaveManagerClass *wave_manager , POSITION* position)
{
	LoadEnemyStatus(wave_manager , position);
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
	//�F�ݒ�i���j
	glColor3f(1.f , 1.f , 1.f);

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
//EnemyType�QClass
//////////////////////////////////////////////////////////////////////////////

EnemyType2Class::EnemyType2Class()
{
}

EnemyType2Class::~EnemyType2Class()
{
}

//////////////////////////////////////////////////////////////////////////////
//private�֐�
//////////////////////////////////////////////////////////////////////////////

bool EnemyType2Class::LoadEnemyStatus(WaveManagerClass *wave_manager , POSITION* position)
{
	std::string FileName = "data/" + wave_manager->GetNowStage() + "/enemy/enemytype2.csv";

	std::ifstream ifs(FileName);

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
		if(position->m_Vector.x < WINDOW_WIDTH / 2)
		{
			BoxClass::Initialize(position , &VELOCITY(TempVector[0] , TempVector[1]) ,
				&ACCELARATION(TempVector[2] , TempVector[3]) , &THREE_DIMENSION_VECTOR(TempVector[4]) , &THREE_DIMENSION_VECTOR(0 , TempVector[5]));
		}
		else if(position->m_Vector.x > WINDOW_WIDTH / 2)
		{
			BoxClass::Initialize(position , &VELOCITY(TempVector[0] , TempVector[1]) ,
				&ACCELARATION(-TempVector[2] , TempVector[3]) , &THREE_DIMENSION_VECTOR(TempVector[4]) , &THREE_DIMENSION_VECTOR(0 , TempVector[5]));
		}
		else
		{
			BoxClass::Initialize(position , &VELOCITY(TempVector[0] , TempVector[1]) ,
				&ACCELARATION() , &THREE_DIMENSION_VECTOR(TempVector[4]) , &THREE_DIMENSION_VECTOR(0 , TempVector[5]));
		}
	}
	else
	{
		if(position->m_Vector.x < WINDOW_WIDTH / 2)
		{
			BoxClass::Initialize(position , &VELOCITY(TempVector[0] , TempVector[1]) ,
				&ACCELARATION(TempVector[2] , TempVector[3]) , &THREE_DIMENSION_VECTOR(0 , TempVector[5]) , &THREE_DIMENSION_VECTOR(TempVector[4]));
		}
		else if(position->m_Vector.x > WINDOW_WIDTH / 2)
		{
			BoxClass::Initialize(position , &VELOCITY(TempVector[0] , TempVector[1]) ,
				&ACCELARATION(-TempVector[2] , TempVector[3]) , &THREE_DIMENSION_VECTOR(0 , TempVector[5]) , &THREE_DIMENSION_VECTOR(TempVector[4]));
		}
		else
		{
			BoxClass::Initialize(position , &VELOCITY(TempVector[0] , TempVector[1]) ,
				&ACCELARATION() , &THREE_DIMENSION_VECTOR(0 , TempVector[5]) , &THREE_DIMENSION_VECTOR(TempVector[4]));
		}
	}

	m_Speed = TempVector[6];

	ReleaseVector(TempVector);

	return true;
}

void EnemyType2Class::MoveObject()
{
	if(m_Position.m_Vector.y < 0.8 * WINDOW_HEIGHT)
	{
		if(TimeCount() > 60)
		{
			m_Position.m_Vector += m_Velocity.m_Vector;

			AccelObject();

			THREE_DIMENSION_VECTOR TempVelocity = GetVelocity().m_Vector;
			TempVelocity.Nomalize();
			SetVelocity(&(TempVelocity * m_Speed));
		}
	}
	else
	{
		m_Position.m_Vector += m_Velocity.m_Vector;
	}
}

void EnemyType2Class::ShotBullet()
{
}


//////////////////////////////////////////////////////////////////////////////
//public�֐�
//////////////////////////////////////////////////////////////////////////////

bool EnemyType2Class::Initialize(WaveManagerClass *wave_manager , POSITION* position)
{
	LoadEnemyStatus(wave_manager , position);
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
//public�֐�
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
		m_EnemyType->GetPosition().m_Vector.y < 0)
	{
		return false;
	}

	return true;
}

bool EnemyClass::Initiarize(WaveManagerClass *wave_manager , int enemy_type , POSITION* position)
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
	
	m_EnemyType->Initialize(wave_manager , position);

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