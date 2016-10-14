#include "PlayerClass.h"
#define _USE_MATH_DEFINES
#include <math.h>

#include <gl\glew.h>
#include <gl\glut.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include "system.h"
#include "ShoulderPartsClass.h"
#include "BackPartsClass.h"
#include "HipPartsClass.h"

//�R���X�g���N�^
PlayerClass::PlayerClass(void)
{
	m_Pointer_to_Shoulder_L = NULL;
	m_Pointer_to_Shoulder_R = NULL;
}

//�f�X�g���N�^
PlayerClass::~PlayerClass(void)
{
}

//////////////////////////////////////////////////////////////////////////////
//private�֐�
//////////////////////////////////////////////////////////////////////////////

bool PlayerClass::LoadPlayerStatus(std::string file_name)
{
	
	std::ifstream ifs(file_name);

	if(ifs.fail()) return false;

	std::string PlayerStatus;
	
	for(int i = 0 ; i < 2 ; i++)
	{
		std::getline(ifs , PlayerStatus);
	}

	std::string token;
	std::istringstream stream(PlayerStatus);
	std::vector<double> TempVector;
	
	while(getline(stream , token , ','))
	{
		TempVector.push_back(std::stod(token));
	}

	SPEED_X_ASPECT = TempVector[0];
	SPEED_Y_ASPECT = TempVector[1];

	if(TempVector[2] >= TempVector[3])
	{
		m_SemiLongVector = THREE_DIMENSION_VECTOR(TempVector[2]);
		m_SemiShortVector = THREE_DIMENSION_VECTOR(0 , TempVector[3]);
	}
	else
	{
		m_SemiLongVector = THREE_DIMENSION_VECTOR(0 , TempVector[3]);
		m_SemiShortVector = THREE_DIMENSION_VECTOR(TempVector[2]);
	}

	if(TempVector[6] >= TempVector[7])
	{
		m_Pointer_to_Shoulder_L->SetShotStatus(TempVector[4] , &VELOCITY() , TempVector[5] , &ACCELARATION() , &THREE_DIMENSION_VECTOR(TempVector[6] / 2) , &THREE_DIMENSION_VECTOR(0 , TempVector[7] / 2));
		m_Pointer_to_Shoulder_R->SetShotStatus(TempVector[4] , &VELOCITY() , TempVector[5] , &ACCELARATION() , &THREE_DIMENSION_VECTOR(TempVector[6] / 2) , &THREE_DIMENSION_VECTOR(0 , TempVector[7] / 2));
	}
	else
	{
		m_Pointer_to_Shoulder_L->SetShotStatus(TempVector[4] , &VELOCITY() , TempVector[5] , &ACCELARATION() , &THREE_DIMENSION_VECTOR(0 , TempVector[7] / 2) , &THREE_DIMENSION_VECTOR(TempVector[6] / 2));
		m_Pointer_to_Shoulder_R->SetShotStatus(TempVector[4] , &VELOCITY() , TempVector[5] , &ACCELARATION() , &THREE_DIMENSION_VECTOR(0 , TempVector[7] / 2) , &THREE_DIMENSION_VECTOR(TempVector[6] / 2));
	}

	ReleaseVector(TempVector);

	return true;
}

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	�C���v�b�g�ɂ���ăv���C���[�̋�����ω�������
//////////////////////////////////////////////////////////////////////////////
void PlayerClass::CheckInput()
{
	if(m_InputKeyFlag & E_UP_ARROW_KEY) m_Velocity.m_Vector.y = m_PLAYER_Y_SPEED;	//���L�[
	if(m_InputKeyFlag & E_LEFT_ARROW_KEY) m_Velocity.m_Vector.x = -m_PLAYER_X_SPEED;	//���L�[
	if(m_InputKeyFlag & E_RIGHT_ARROW_KEY) m_Velocity.m_Vector.x = m_PLAYER_X_SPEED;	//���L�[
	if(m_InputKeyFlag & E_DOWN_ARROW_KEY) m_Velocity.m_Vector.y = -m_PLAYER_Y_SPEED;	//���L�[

	//���L�[�����L�[��������Ă��Ȃ�������y�������̑��x������0�ɂ���
	if(!(m_InputKeyFlag & E_UP_ARROW_KEY || m_InputKeyFlag & E_DOWN_ARROW_KEY) || 
		(m_InputKeyFlag & E_UP_ARROW_KEY && m_InputKeyFlag & E_DOWN_ARROW_KEY)) m_Velocity.m_Vector.y = 0;
	//���L�[�����L�[��������Ă��Ȃ�������x�������̑��x������0�ɂ���
	if(!(m_InputKeyFlag & E_LEFT_ARROW_KEY || m_InputKeyFlag & E_RIGHT_ARROW_KEY) ||
		(m_InputKeyFlag & E_LEFT_ARROW_KEY && m_InputKeyFlag & E_RIGHT_ARROW_KEY)) m_Velocity.m_Vector.x = 0;

	if(m_InputKeyFlag & E_Z_KEY) m_ShotFlag = true;	//Z�L�[�ŃV���b�g�t���O�𗧂Ă�
	else m_ShotFlag = false;	//Z�L�[�𗣂��Ə���
}

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	�v���C���[�̈ړ��\�͈͂𐧌�����
//////////////////////////////////////////////////////////////////////////////
void PlayerClass::PlayerCanNotOverScreen()
{
	if(m_Position.m_Vector.y > WINDOW_HEIGHT) m_Position.m_Vector.y = WINDOW_HEIGHT;
	if(m_Position.m_Vector.y < 0) m_Position.m_Vector.y = 0;
	if(m_Position.m_Vector.x > WINDOW_WIDTH) m_Position.m_Vector.x = WINDOW_WIDTH;
	if(m_Position.m_Vector.x < 0) m_Position.m_Vector.x = 0;
}

void PlayerClass::MoveObject()
{
	if(m_InputKeyFlag & E_SHIFT_KEY)
	{
		m_Position.m_Vector += m_Velocity.m_Vector * 0.5;
	}
	else
	{
		m_Position.m_Vector += m_Velocity.m_Vector;
	}
}

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	�q�I�u�W�F�N�g�̏����ݒ�
//�߂�l:
//	true:�Ƃ肠����true��Ԃ�
//////////////////////////////////////////////////////////////////////////////
bool PlayerClass::InitializeChild()
{
	//����
	m_Pointer_to_Shoulder_L->Initialize(&POSITION(10 , 32) , &VELOCITY() , &ACCELARATION() , &THREE_DIMENSION_VECTOR(5) , &THREE_DIMENSION_VECTOR(0 , 5) , this);
	//�E��
	m_Pointer_to_Shoulder_R->Initialize(&POSITION(-10 , 32) , &VELOCITY() , &ACCELARATION() , &THREE_DIMENSION_VECTOR(5) , &THREE_DIMENSION_VECTOR(0 , 5) , this);
	//�w��
	m_Pointer_to_Back->Initialize(&POSITION(0 , 10) , &VELOCITY() , &ACCELARATION() , &THREE_DIMENSION_VECTOR(0 , 10) , &THREE_DIMENSION_VECTOR(5) , this);
	//��
	m_Pointer_to_Hip->Initialize(&POSITION(0 , -10) , &VELOCITY() , &ACCELARATION() , &THREE_DIMENSION_VECTOR(10) , &THREE_DIMENSION_VECTOR(0 , 5) , this);
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	�q�I�u�W�F�N�g���X�V����
//�߂�l:
//	�Ƃ肠����true��Ԃ�
//////////////////////////////////////////////////////////////////////////////
bool PlayerClass::UpdateChild()
{
	m_Pointer_to_Shoulder_L->Update(m_ShotFlag);
	m_Pointer_to_Shoulder_R->Update(m_ShotFlag);
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	�q�I�u�W�F�N�g��`�悷��
//////////////////////////////////////////////////////////////////////////////
void PlayerClass::RenderChild()
{
	//����
	m_Pointer_to_Shoulder_L->Render(&m_Position);
	//�E��
	m_Pointer_to_Shoulder_R->Render(&m_Position);
	//�w��
	m_Pointer_to_Back->Render(&m_Position);
	//��
	m_Pointer_to_Hip->Render(&m_Position);
}


//////////////////////////////////////////////////////////////////////////////
//public�֐�
//////////////////////////////////////////////////////////////////////////////

void PlayerClass::SetPlayerSpeed(double x , double y)
{
	m_PLAYER_X_SPEED = x;
	m_PLAYER_Y_SPEED = y;
}

/////////////////////////////////////////////////////////////////////////////
//�T��:
//	������
//����:
//	*position:�ʒu
//	*velocity:���x
//	*accelaration:�����x
//	*semi_long_vector:�������x�N�g��
//	*semi_short_vector:���Z���x�N�g��
//	*shoulder_l:�����p�[�c�ւ̃|�C���^
//	*shoulder_r:�E���p�[�c�ւ̃|�C���^
//	*back:�w���p�[�c�ւ̃|�C���^
//	*hip:���p�[�c�ւ̃|�C���^
//	flag:�t���O
//�߂�l:
//	true:�Ƃ肠����true��Ԃ�
//////////////////////////////////////////////////////////////////////////////
bool PlayerClass::Initialize(std::string file_name , ShoulderPartsClass* shoulder_l , ShoulderPartsClass* shoulder_r , BackPartsClass* back , HipPartsClass* hip , bool flag)
{
	m_Position = POSITION(WINDOW_WIDTH / 2 , WINDOW_HEIGHT / 10);
	m_Velocity.m_Vector = THREE_DIMENSION_VECTOR();
	m_Accelaration = ACCELARATION();

	m_SemiLongAxis = m_SemiLongVector.Magnitude();
	m_SemiShortAxis = m_SemiShortVector.Magnitude();

	SetVertex();

	m_Pointer_to_Shoulder_L = shoulder_l;
	m_Pointer_to_Shoulder_R = shoulder_r;
	m_Pointer_to_Back = back;
	m_Pointer_to_Hip = hip;

	LoadPlayerStatus(file_name);

	SetPlayerSpeed(SPEED_X_ASPECT * WINDOW_WIDTH * WINDOW_HEIGHT / SPEED_ASPECT , SPEED_Y_ASPECT * WINDOW_WIDTH * WINDOW_HEIGHT / SPEED_ASPECT);

	InitializeChild();

	return true;
}


//////////////////////////////////////////////////////////////////////////////
//�T��:
//	�X�V
//�߂�l:
//	true:�Ƃ肠����true��Ԃ�
//////////////////////////////////////////////////////////////////////////////
bool PlayerClass::Update()
{
	CheckInput();	//�L�[���͂𒲂ׂ�
	MoveObject();	//�ړ�������
	SetVertex();	//���_�̍Čv�Z������
	AccelObject();	//����������
	PlayerCanNotOverScreen();	//�ړ��͈͂𐧌�����

	UpdateChild();
	

	return true;
}

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	�`��
//////////////////////////////////////////////////////////////////////////////
void PlayerClass::Render()
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

	RenderChild();
}