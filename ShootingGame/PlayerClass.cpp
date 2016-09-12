#include "PlayerClass.h"
#define _USE_MATH_DEFINES
#include <math.h>

#include <gl\glew.h>
#include <gl\glut.h>

#include "system.h"
#include "ShoulderPartsClass.h"
#include "BackPartsClass.h"
#include "HipPartsClass.h"

//���̉�
PlayerClass TestPlayer;

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
	if(!(m_InputKeyFlag & E_UP_ARROW_KEY || m_InputKeyFlag & E_DOWN_ARROW_KEY)) m_Velocity.m_Vector.y = 0;
	//���L�[�����L�[��������Ă��Ȃ�������x�������̑��x������0�ɂ���
	if(!(m_InputKeyFlag & E_LEFT_ARROW_KEY || m_InputKeyFlag & E_RIGHT_ARROW_KEY)) m_Velocity.m_Vector.x = 0;
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

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	������
//����:
//	*position:�ʒu
//	*velocity:���x
//	*accelaration:�����x
//	*semi_long_vector:�������x�N�g��
//	*semi_short_vector:���Z���x�N�g��
//	flag:�t���O
//�߂�l:
//	true:�Ƃ肠����true��Ԃ�
//////////////////////////////////////////////////////////////////////////////
bool PlayerClass::Initialize(POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , THREE_DIMENSION_VECTOR* semi_long_vector , THREE_DIMENSION_VECTOR* semi_short_vector , ShoulderPartsClass* shoulder_l , ShoulderPartsClass* shoulder_r , BackPartsClass* back , HipPartsClass* hip , bool flag)
{
	m_Position = *position;
	m_Velocity = *velocity;
	m_Accelaration = *accelaration;
	m_SemiLongVector = *semi_long_vector;
	m_SemiShortVector = *semi_short_vector;

	m_SemiLongAxis = m_SemiLongVector.Magnitude();
	m_SemiShortAxis = m_SemiShortVector.Magnitude();

	SetVertex();

	m_Pointer_to_Shoulder_L = shoulder_l;
	m_Pointer_to_Shoulder_R = shoulder_r;
	m_Pointer_to_Back = back;
	m_Pointer_to_Hip = hip;

	SetPlayerSpeed(PLAYER_SPEED_X_ASPECT * WINDOW_WIDTH * WINDOW_HEIGHT / 100000 , PLAYER_SPEED_Y_ASPECT * WINDOW_WIDTH * WINDOW_HEIGHT / 100000);

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