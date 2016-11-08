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
#include "CircleClass.h"

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

//////////////////////////////////////////////////////////////////////////////
//�v���C���[�̏������[�h
//����:
//	file_name:���[�h����t�@�C����
//////////////////////////////////////////////////////////////////////////////
bool PlayerClass::LoadPlayerStatus(int player_type)
{
	//�t�@�C����ǂݍ���
	std::ifstream ifs("data/player/playerstatus.csv");

	//���s������false��Ԃ�
	if(ifs.fail()) return false;

	//�f�[�^��ǂݍ��ނ��߂̕�����
	std::string PlayerStatus;
	
	//�ŏ���1�s�͖�������
	std::getline(ifs , PlayerStatus);

	//�����o�������v���C���[���܂ōs��
	for(int i = 0 ; i <= player_type ; i++)
	{
		std::getline(ifs , PlayerStatus);
	}

	std::string token;	//�f�[�^���o���p�̃g�[�N��
	std::istringstream stream(PlayerStatus);	//�f�[�^�����ǂݍ��ޕ�����
	std::vector<double> TempVector;	//�f�[�^�ϊ��p�z��
	
	//','�����邽�тɃg�[�N���ɕ���������o��
	while(getline(stream , token , ','))
	{
		//�g�[�N���̕�����𐔎��ɕϊ�����
		TempVector.push_back(std::stod(token));
	}

	//�����蔻��̐ݒ�
	m_PlayerCollider.Initialize(&m_Position , &m_Velocity , &m_Accelaration ,TempVector[1]);

	//���̕����傫���Ƃ�
	if(TempVector[2] >= TempVector[3])
	{
		m_SemiLongVector = THREE_DIMENSIONAL_VECTOR(TempVector[2]);
		m_SemiShortVector = THREE_DIMENSIONAL_VECTOR(0 , TempVector[3]);
	}
	//�c�̕����傫���Ƃ�
	else
	{
		m_SemiLongVector = THREE_DIMENSIONAL_VECTOR(0 , TempVector[3]);
		m_SemiShortVector = THREE_DIMENSIONAL_VECTOR(TempVector[2]);
	}

	////�V���b�g�摜�̉��̕����傫���Ƃ�
	//if(TempVector[6] >= TempVector[7])
	//{
	//	m_Pointer_to_Shoulder_L->SetShotStatus(TempVector[4] , &VELOCITY() , TempVector[5] , &ACCELARATION() , &THREE_DIMENSIONAL_VECTOR(TempVector[6] / 2) , &THREE_DIMENSIONAL_VECTOR(0 , TempVector[7] / 2));
	//	m_Pointer_to_Shoulder_R->SetShotStatus(TempVector[4] , &VELOCITY() , TempVector[5] , &ACCELARATION() , &THREE_DIMENSIONAL_VECTOR(TempVector[6] / 2) , &THREE_DIMENSIONAL_VECTOR(0 , TempVector[7] / 2));
	//}
	////�V���b�g�摜�̏c�̕����傫���Ƃ�
	//else
	//{
	//	m_Pointer_to_Shoulder_L->SetShotStatus(TempVector[4] , &VELOCITY() , TempVector[5] , &ACCELARATION() , &THREE_DIMENSIONAL_VECTOR(0 , TempVector[7] / 2) , &THREE_DIMENSIONAL_VECTOR(TempVector[6] / 2));
	//	m_Pointer_to_Shoulder_R->SetShotStatus(TempVector[4] , &VELOCITY() , TempVector[5] , &ACCELARATION() , &THREE_DIMENSIONAL_VECTOR(0 , TempVector[7] / 2) , &THREE_DIMENSIONAL_VECTOR(TempVector[6] / 2));
	//}

	//����Ȃ�vector���J������
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


/////////////////////////////////////////////////////////////////////////////
//�ړ�����
//////////////////////////////////////////////////////////////////////////////
void PlayerClass::MoveObject()
{
	//SHIFT�L�[�������Ă���Ƃ������������ɂȂ�
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
//����:
//	shoulder_l_type
//	shoulder_r_type
//	back_type
//	hip_type
//�߂�l:
//	true:�������ɐ���
//	false:�����ꂩ�̃f�[�^�̃��[�h�����s����
//////////////////////////////////////////////////////////////////////////////
bool PlayerClass::InitializeChild(int shoulder_l_type , int shoulder_r_type , int back_type , int hip_type)
{
	//����
	if(!m_Pointer_to_Shoulder_L->Initialize(shoulder_l_type , &POSITION(10 , 32) , &VELOCITY() , &ACCELARATION() , this)) return false;
	//�E��
	if(!m_Pointer_to_Shoulder_R->Initialize(shoulder_r_type , &POSITION(-10 , 32) , &VELOCITY() , &ACCELARATION() , this)) return false;
	//�w��
	if(!m_Pointer_to_Back->Initialize(back_type , &POSITION(0 , 10) , &VELOCITY() , &ACCELARATION() , this)) return false;
	//��
	if(!m_Pointer_to_Hip->Initialize(hip_type , &POSITION(0 , -10) , &VELOCITY() , &ACCELARATION() , this)) return false;
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
	//����
	m_Pointer_to_Shoulder_L->Update(m_ShotFlag);
	//�E��
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

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	�v���C���[�̑��x��ݒ肷��
//����:
//	x:�������x
//	y:�c�����x
//////////////////////////////////////////////////////////////////////////////
void PlayerClass::SetPlayerSpeed(double x , double y)
{
	m_PLAYER_X_SPEED = x;
	m_PLAYER_Y_SPEED = y;
}

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	������
//����:
//	player_type:�v���C���[�L�����N�^�[�̃^�C�v
//	*shoulder_l:�����p�[�c�ւ̃|�C���^
//	shoulder_l_type:�����p�[�c�̃^�C�v
//	*shoulder_r:�E���p�[�c�ւ̃|�C���^
//	shoulder_r_type:�E���p�[�c�̃^�C�v
//	*back:�w���p�[�c�ւ̃|�C���^
//	back_type:�w���p�[�c�̃^�C�v
//	*hip:���p�[�c�ւ̃|�C���^
//	hip_type:���p�[�c�̃^�C�v
//	flag:�t���O
//�߂�l:
//	true:�������ɐ���
//	false:�����ꂩ�̃t�@�C���̃��[�h�����s���Ă���
//////////////////////////////////////////////////////////////////////////////
bool PlayerClass::Initialize(int player_type ,
		ShoulderPartsClass* shoulder_l , int shoulder_l_type ,
		ShoulderPartsClass* shoulder_r , int shoulder_r_type ,
		BackPartsClass* back , int back_type ,
		HipPartsClass* hip , int hip_type ,
		bool flag = true)
{
	//��ʒu�X�^�[�g
	m_Position = POSITION(WINDOW_WIDTH / 2 , WINDOW_HEIGHT / 10);
	//���x0�X�^�[�g
	m_Velocity.m_Vector = THREE_DIMENSIONAL_VECTOR();
	//�����x0�X�^�[�g
	m_Accelaration = ACCELARATION();

	//��������
	m_SemiLongAxis = m_SemiLongVector.Magnitude();
	//���Z����
	m_SemiShortAxis = m_SemiShortVector.Magnitude();

	//���_�̍Đݒ�
	SetVertex();

	//�q�̃|�C���^���L������
	m_Pointer_to_Shoulder_L = shoulder_l;	//����
	m_Pointer_to_Shoulder_R = shoulder_r;	//�E��
	m_Pointer_to_Back = back;	//�w��
	m_Pointer_to_Hip = hip;	//��

	//�v���C���[�̃f�[�^�����[�h����
	if(!LoadPlayerStatus(file_name)) return false;

	//�v���C���[�̑�����ݒ肷��
	SetPlayerSpeed(SPEED_X_ASPECT * WINDOW_WIDTH * WINDOW_HEIGHT / SPEED_ASPECT , SPEED_Y_ASPECT * WINDOW_WIDTH * WINDOW_HEIGHT / SPEED_ASPECT);

	//�q������������
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