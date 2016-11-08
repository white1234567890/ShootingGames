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

//�G�������[�h�i�������z�֐��j
bool EnemyStatePatternClass::LoadEnemyStatus(WaveManagerClass *wave_manager , POSITION* position)
{
	return true;
}

//�G�̈ʒu���ړ��i�������z�֐��j
void EnemyStatePatternClass::MoveObject()
{
}

//�G���e�����i�������z�֐��j
void EnemyStatePatternClass::ShotBullet()
{
}

/////////////////////////////////////////////////////////////////////////////
//�G�ƃv���C���[�̒e�̓����蔻��
//////////////////////////////////////////////////////////////////////////////
bool EnemyStatePatternClass::CheckHitEnemy_and_PlayerBullet(PlayerBulletManagerClass *player_bullet_manager)
{
	if(player_bullet_manager->m_Bullet.ToBegin())
	{
		do
		{
			if(CheckHitBoxandBox(&player_bullet_manager->m_Bullet.GetCurrentNode() , this)) 
			{
				std::cout << "Hit!" << std::endl;
				return true;
			}
		}while(player_bullet_manager->m_Bullet.Next());
	}
	
	return false;
}

//////////////////////////////////////////////////////////////////////////////
//public�֐�
//////////////////////////////////////////////////////////////////////////////

//�������i�������z�֐��j
bool EnemyStatePatternClass::Initialize(WaveManagerClass *wave_manager , POSITION* position)
{
	return true;
}

//�X�V�i�������z�֐��j
bool EnemyStatePatternClass::Update(PlayerBulletManagerClass *player_bullet_manager)
{
	return true;
}

//�`��i�������z�֐��j
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

//////////////////////////////////////////////////////////////////////////////
//�G�������[�h
//����:
//	wave_manager:�E�F�[�u�}�l�[�W���[
//	position:�G�����ʒu
//	true:�G���̃��[�h�ɐ���
//	false:�G���̃��[�h�Ɏ��s
//////////////////////////////////////////////////////////////////////////////
bool EnemyType1Class::LoadEnemyStatus(WaveManagerClass *wave_manager , POSITION* position)
{
	//�ǂݍ��ރt�@�C�������w��
	std::string FileName = "data/" + wave_manager->GetNowStage() + "/enemy/enemytype1.csv";

	//�t�@�C����ǂݍ���
	std::ifstream ifs(FileName);

	//�ǂݍ��݂Ɏ��s������false��Ԃ�
	if(ifs.fail()) return false;
	
	std::string EnemyStatus;	//�ǂݍ��񂾕����������
	
	//�ŏ���1�s�͖�������
	for(int i = 0 ; i < 2 ; i++)
	{
		std::getline(ifs , EnemyStatus);
	}
	
	std::string token;	//�f�[�^�����p�g�[�N��
	std::istringstream stream(EnemyStatus);	//�ǂݍ��ޕ�����
	std::vector<double> TempVector;	//������𕂓������_���ɒ���
	
	//','�����邽�тɃg�[�N���ɕ�����ǂݍ���
	while(getline(stream , token , ','))
	{
		//�����𐔎��ɒ���
		TempVector.push_back(std::stod(token));
	}

	//�摜�������̎�
	if(TempVector[1] >= TempVector[2])
	{
		//�����ʒu���^�񒆂�聩�̎�
		if(position->m_Vector.x < WINDOW_WIDTH / 2)
		{
			//�����x�����̂܂܏�����
			BoxClass::Initialize(position , &VELOCITY(0 , -TempVector[0]) ,
				&ACCELARATION(TempVector[3] , TempVector[4]) , &THREE_DIMENSIONAL_VECTOR(TempVector[1]) , &THREE_DIMENSIONAL_VECTOR(0 , TempVector[2]));
		}
		//�����ʒu���^�񒆂�聨�̎�
		else if(position->m_Vector.x > WINDOW_WIDTH / 2)
		{
			//�����x���t�ɂ��ď�����
			BoxClass::Initialize(position , &VELOCITY(0 , -TempVector[0]) ,
				&ACCELARATION(-TempVector[3] , TempVector[4]) , &THREE_DIMENSIONAL_VECTOR(TempVector[1]) , &THREE_DIMENSIONAL_VECTOR(0 , TempVector[2]));
		}
		//�����ʒu���^�񒆂̎�
		else
		{
			//�����x��0�ɂ��ď�����
			BoxClass::Initialize(position , &VELOCITY(0 , -TempVector[0]) ,
				&ACCELARATION() , &THREE_DIMENSIONAL_VECTOR(TempVector[1]) , &THREE_DIMENSIONAL_VECTOR(0 , TempVector[2]));
		}
	}
	//�摜���c���̎�
	else
	{
		//�����ʒu���^�񒆂�聩�̎�
		if(position->m_Vector.x < WINDOW_WIDTH / 2)
		{
			//�����x�����̂܂܏�����
			BoxClass::Initialize(position , &VELOCITY(0 , -TempVector[0]) ,
				&ACCELARATION(TempVector[3] , TempVector[4]) , &THREE_DIMENSIONAL_VECTOR(0 , TempVector[2]) , &THREE_DIMENSIONAL_VECTOR(TempVector[1]));
		}
		//�����ʒu���^�񒆂�聨�̎�
		else if(position->m_Vector.x > WINDOW_WIDTH / 2)
		{
			//�����x���t�ɂ��ď�����
			BoxClass::Initialize(position , &VELOCITY(0 , -TempVector[0]) ,
				&ACCELARATION(-TempVector[3] , TempVector[4]) , &THREE_DIMENSIONAL_VECTOR(0 , TempVector[2]) , &THREE_DIMENSIONAL_VECTOR(TempVector[1]));
		}
		//�����ʒu���^�񒆂̎�
		else
		{
			//�����x��0�ɂ��ď�����
			BoxClass::Initialize(position , &VELOCITY(0 , -TempVector[0]) ,
				&ACCELARATION() , &THREE_DIMENSIONAL_VECTOR(0 , TempVector[2]) , &THREE_DIMENSIONAL_VECTOR(TempVector[1]));
		}
	}

	//�ړ��̑���������
	m_Speed = TempVector[0];

	//�g����vector���J������
	ReleaseVector(TempVector);

	return true;
}

//////////////////////////////////////////////////////////////////////////////
//�G�̈ʒu���ړ�
//////////////////////////////////////////////////////////////////////////////
void EnemyType1Class::MoveObject()
{
	//�G�ʒu����ʂ�4/5��聫�̎�
	if(m_Position.m_Vector.y < 0.8 * WINDOW_HEIGHT)
	{
		//1�b�o������
		if(TimeCount() > 60)
		{
			//�ʒu���ړ�������
			m_Position.m_Vector += m_Velocity.m_Vector;

			//�����x���瑬�x���o��
			AccelObject();

			//���x�𑬂��ɍ��킹��
			THREE_DIMENSIONAL_VECTOR TempVelocity = GetVelocity().m_Vector;
			TempVelocity.Nomalize();
			SetVelocity(&(TempVelocity * m_Speed));
		}
	}
	else
		//�G�ʒu��ʂ�4/5��聪�̎�
	{
		//���ɐi��
		m_Position.m_Vector += m_Velocity.m_Vector;
	}
}

//////////////////////////////////////////////////////////////////////////////
//�G���e������
//////////////////////////////////////////////////////////////////////////////
void EnemyType1Class::ShotBullet()
{
}

//////////////////////////////////////////////////////////////////////////////
//public�֐�
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//������
//����:
//	wave_manager:�E�F�[�u�}�l�[�W���[
//	position:�G�����ʒu
//�߂�l:
//	true:�G���̃��[�h�ɐ���
//	false:�G���̃��[�h�Ɏ��s
//////////////////////////////////////////////////////////////////////////////
bool EnemyType1Class::Initialize(WaveManagerClass *wave_manager , POSITION* position)
{
	//�G�������[�h
	LoadEnemyStatus(wave_manager , position);
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//�X�V
//////////////////////////////////////////////////////////////////////////////
bool EnemyType1Class::Update(PlayerBulletManagerClass *player_bullet_manager)
{
	//�G���ړ�������
	MoveObject();
	//���_����ݒ肷��
	SetVertex();
	//�����蔻������
	if(CheckHitEnemy_and_PlayerBullet(player_bullet_manager)) return false;
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//�`��
//////////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////////////
//�G�������[�h
//����:
//	wave_manager:�E�F�[�u�}�l�[�W���[
//	position:�G�����ʒu
//	true:�G���̃��[�h�ɐ���
//	false:�G���̃��[�h�Ɏ��s
//////////////////////////////////////////////////////////////////////////////
bool EnemyType2Class::LoadEnemyStatus(WaveManagerClass *wave_manager , POSITION* position)
{
	//�ǂݍ��ރt�@�C�������w��
	std::string FileName = "data/" + wave_manager->GetNowStage() + "/enemy/enemytype2.csv";
	
	//�t�@�C����ǂݍ���
	std::ifstream ifs(FileName);

	//�ǂݍ��݂Ɏ��s������false��Ԃ�
	if(ifs.fail()) return false;
	
	std::string EnemyStatus;	//�ǂݍ��񂾕����������
	
	//�ŏ���1�s�͖�������
	for(int i = 0 ; i < 2 ; i++)
	{
		std::getline(ifs , EnemyStatus);
	}
	
	std::string token;	//�f�[�^�����p�g�[�N��
	std::istringstream stream(EnemyStatus);	//�ǂݍ��ޕ�����
	std::vector<double> TempVector;	//������𕂓������_���ɒ���
	
	//','�����邽�тɃg�[�N���ɕ�����ǂݍ���
	while(getline(stream , token , ','))
	{
		//�����𐔎��ɒ���
		TempVector.push_back(std::stod(token));
	}

	//�摜�������̎�
	if(TempVector[1] >= TempVector[2])
	{
		//�����ʒu���^�񒆂�聩�̎�
		if(position->m_Vector.x < WINDOW_WIDTH / 2)
		{
			//�����x�����̂܂܏�����
			BoxClass::Initialize(position , &VELOCITY(0 , -TempVector[0]) ,
				&ACCELARATION(TempVector[3] , TempVector[4]) , &THREE_DIMENSIONAL_VECTOR(TempVector[1]) , &THREE_DIMENSIONAL_VECTOR(0 , TempVector[2]));
		}
		//�����ʒu���^�񒆂�聨�̎�
		else if(position->m_Vector.x > WINDOW_WIDTH / 2)
		{
			//�����x���t�ɂ��ď�����
			BoxClass::Initialize(position , &VELOCITY(0 , -TempVector[0]) ,
				&ACCELARATION(-TempVector[3] , TempVector[4]) , &THREE_DIMENSIONAL_VECTOR(TempVector[1]) , &THREE_DIMENSIONAL_VECTOR(0 , TempVector[2]));
		}
		//�����ʒu���^�񒆂̎�
		else
		{
			//�����x��0�ɂ��ď�����
			BoxClass::Initialize(position , &VELOCITY(0 , -TempVector[0]) ,
				&ACCELARATION() , &THREE_DIMENSIONAL_VECTOR(TempVector[1]) , &THREE_DIMENSIONAL_VECTOR(0 , TempVector[2]));
		}
	}
	//�摜���c���̎�
	else
	{
		//�����ʒu���^�񒆂�聩�̎�
		if(position->m_Vector.x < WINDOW_WIDTH / 2)
		{
			//�����x�����̂܂܏�����
			BoxClass::Initialize(position , &VELOCITY(0 , -TempVector[0]) ,
				&ACCELARATION(TempVector[3] , TempVector[4]) , &THREE_DIMENSIONAL_VECTOR(0 , TempVector[2]) , &THREE_DIMENSIONAL_VECTOR(TempVector[1]));
		}
		//�����ʒu���^�񒆂�聨�̎�
		else if(position->m_Vector.x > WINDOW_WIDTH / 2)
		{
			//�����x���t�ɂ��ď�����
			BoxClass::Initialize(position , &VELOCITY(0 , -TempVector[0]) ,
				&ACCELARATION(-TempVector[3] , TempVector[4]) , &THREE_DIMENSIONAL_VECTOR(0 , TempVector[2]) , &THREE_DIMENSIONAL_VECTOR(TempVector[1]));
		}
		//�����ʒu���^�񒆂̎�
		else
		{
			//�����x��0�ɂ��ď�����
			BoxClass::Initialize(position , &VELOCITY(0 , -TempVector[0]) ,
				&ACCELARATION() , &THREE_DIMENSIONAL_VECTOR(0 , TempVector[2]) , &THREE_DIMENSIONAL_VECTOR(TempVector[1]));
		}
	}

	//�ړ��̑���������
	m_Speed = TempVector[0];

	//�g����vector���J������
	ReleaseVector(TempVector);

	return true;
}

//////////////////////////////////////////////////////////////////////////////
//�G�̈ʒu���ړ�
//////////////////////////////////////////////////////////////////////////////
void EnemyType2Class::MoveObject()
{
	//�G�ʒu����ʂ�4/5��聫�̎�
	if(m_Position.m_Vector.y < 0.8 * WINDOW_HEIGHT)
	{
		//1�b�o������
		if(TimeCount() > 60)
		{
			//�ʒu���ړ�������
			m_Position.m_Vector += m_Velocity.m_Vector;

			//�����x���瑬�x���o��
			AccelObject();

			//���x�𑬂��ɍ��킹��
			THREE_DIMENSIONAL_VECTOR TempVelocity = GetVelocity().m_Vector;
			TempVelocity.Nomalize();
			SetVelocity(&(TempVelocity * m_Speed));
		}
	}
	else
		//�G�ʒu��ʂ�4/5��聪�̎�
	{
		//���ɐi��
		m_Position.m_Vector += m_Velocity.m_Vector;
	}
}

//////////////////////////////////////////////////////////////////////////////
//�G���e������
//////////////////////////////////////////////////////////////////////////////
void EnemyType2Class::ShotBullet()
{
}


//////////////////////////////////////////////////////////////////////////////
//public�֐�
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//������
//����:
//	wave_manager:�E�F�[�u�}�l�[�W���[
//	position:�G�����ʒu
//�߂�l:
//	true:�G���̃��[�h�ɐ���
//	false:�G���̃��[�h�Ɏ��s
//////////////////////////////////////////////////////////////////////////////
bool EnemyType2Class::Initialize(WaveManagerClass *wave_manager , POSITION* position)
{
	//�G�������[�h
	LoadEnemyStatus(wave_manager , position);
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//�X�V
//////////////////////////////////////////////////////////////////////////////
bool EnemyType2Class::Update(PlayerBulletManagerClass *player_bullet_manager)
{
	//�G���ړ�������
	MoveObject();
	//���_����ݒ肷��
	SetVertex();
	//�����蔻������
	if(CheckHitEnemy_and_PlayerBullet(player_bullet_manager)) return false;
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//�`��
//////////////////////////////////////////////////////////////////////////////
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
//EnemyContextClass
//////////////////////////////////////////////////////////////////////////////

EnemyContextClass::EnemyContextClass(void)
{
	m_EnemyType = nullptr;	//�G���̂�null�|�C���^��˂�����
}


EnemyContextClass::~EnemyContextClass(void)
{

}

//////////////////////////////////////////////////////////////////////////////
//public�֐�
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//�J��
//////////////////////////////////////////////////////////////////////////////
void EnemyContextClass::Release()
{
	//�G�̎��̂�null����Ȃ��Ƃ�
	if(m_EnemyType != nullptr)
	{
		//�G�̎��̂���������
		delete m_EnemyType;
	}

	//�G�̎��̂�null������
	m_EnemyType = nullptr;
}

//////////////////////////////////////////////////////////////////////////////
	//�G����ʓ��ɂ��邩�`�F�b�N����
	//////////////////////////////////////////////////////////////////////////////
bool EnemyContextClass::CheckEnemyIsInScreen()
{
	//�G�̈ʒu����ʂ̉����E���O���ɂ���Ƃ�
	if(m_EnemyType->GetPosition().m_Vector.x < 0 || m_EnemyType->GetPosition().m_Vector.x > WINDOW_WIDTH ||
		m_EnemyType->GetPosition().m_Vector.y < 0)
	{
		//false��Ԃ�
		return false;
	}

	//true��Ԃ�
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//������
//����:
//	wave_manager:�E�F�[�u�}�l�[�W���[
//	enemy_type:�I�^�C�v
//	position:�����ʒu
//�߂�l:
//	true:�G���̃��[�h�ɐ���
//	false:�G���̃��[�h�Ɏ��s
//////////////////////////////////////////////////////////////////////////////
bool EnemyContextClass::Initiarize(WaveManagerClass *wave_manager , int enemy_type , POSITION* position)
{
	//�G�^�C�v�ɂ���Đ�������X�e�[�g��ω�������
	switch (enemy_type)
	{
	case E_ENEMY_TYPE_1:
		m_EnemyType = new EnemyType1Class;
		break;

	case E_ENEMY_TYPE_2:
		m_EnemyType = new EnemyType2Class;
		break;
	}
	
	//�G�̏�����������
	m_EnemyType->Initialize(wave_manager , position);

	return true;
}


//////////////////////////////////////////////////////////////////////////////
//�X�V
//////////////////////////////////////////////////////////////////////////////
bool EnemyContextClass::Update(PlayerBulletManagerClass *player_bullet_manager)
{
	if(!m_EnemyType->Update(player_bullet_manager)) return false;
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//�`��
//////////////////////////////////////////////////////////////////////////////
void EnemyContextClass::Render()
{
	m_EnemyType->Render();
}