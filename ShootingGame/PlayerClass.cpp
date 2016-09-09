#include "PlayerClass.h"
#include "system.h"
#define _USE_MATH_DEFINES
#include <math.h>

#include <gl\glew.h>
#include <gl\glut.h>

//�R���X�g���N�^
PlayerClass::PlayerClass(void)
{
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
	if(m_InputKeyFlag & E_UP_ARROW_KEY) m_Velocity.m_Vector.y = 0.1;	//���L�[
	if(m_InputKeyFlag & E_LEFT_ARROW_KEY) m_Velocity.m_Vector.x = -0.1;	//���L�[
	if(m_InputKeyFlag & E_RIGHT_ARROW_KEY) m_Velocity.m_Vector.x = 0.1;	//���L�[
	if(m_InputKeyFlag & E_DOWN_ARROW_KEY) m_Velocity.m_Vector.y = -0.1;	//���L�[

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
	//�E��
	m_Shoulder_R.Initialize(&POSITION(32 , 32) , &VELOCITY() , &ACCELARATION() , &THREE_DIMENSION_VECTOR(5) , &THREE_DIMENSION_VECTOR(0 , 5));
	m_Shoulder_R.SetPosition(&(m_Position.m_Vector + m_Shoulder_R.GetLocalPosition().m_Vector));
	m_Shoulder_R.SetVertex();
	
	//����
	m_Shoulder_L.Initialize(&POSITION(-32 , 32) , &VELOCITY() , &ACCELARATION() , &THREE_DIMENSION_VECTOR(5) , &THREE_DIMENSION_VECTOR(0 , 5));
	m_Shoulder_L.SetPosition(&(m_Position.m_Vector + m_Shoulder_L.GetLocalPosition().m_Vector));
	m_Shoulder_L.SetVertex();
	
	//�w��
	m_Back.Initialize(&POSITION(0 , 15) , &VELOCITY() , &ACCELARATION() , &THREE_DIMENSION_VECTOR(5) , &THREE_DIMENSION_VECTOR(0 , 10));
	m_Back.SetPosition(&(m_Position.m_Vector + m_Back.GetLocalPosition().m_Vector));
	m_Back.SetVertex();

	//��
	m_Hip.Initialize(&POSITION(0 , -5) , &VELOCITY() , &ACCELARATION() , &THREE_DIMENSION_VECTOR(20) , &THREE_DIMENSION_VECTOR(0 , 5));
	m_Hip.SetPosition(&(m_Position.m_Vector + m_Hip.GetLocalPosition().m_Vector));
	m_Hip.SetVertex();
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
	//�E��
	m_Shoulder_R.SetPosition(&(m_Position.m_Vector + RotateVector2(m_Shoulder_R.GetLocalPosition().m_Vector.x , m_Shoulder_R.GetLocalPosition().m_Vector.y , m_Angle)));
	m_Shoulder_R.Update();

	//����
	m_Shoulder_L.SetPosition(&(m_Position.m_Vector + RotateVector2(m_Shoulder_L.GetLocalPosition().m_Vector.x , m_Shoulder_L.GetLocalPosition().m_Vector.y , m_Angle)));
	m_Shoulder_L.Update();

	//�w��
	m_Back.SetPosition(&(m_Position.m_Vector + RotateVector2(m_Back.GetLocalPosition().m_Vector.x , m_Back.GetLocalPosition().m_Vector.y , m_Angle)));
	m_Back.Update();

	//��
	m_Hip.SetPosition(&(m_Position.m_Vector + RotateVector2(m_Hip.GetLocalPosition().m_Vector.x , m_Hip.GetLocalPosition().m_Vector.y , m_Angle)));
	m_Hip.Update();

	return true;
}

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	�q�I�u�W�F�N�g��`�悷��
//////////////////////////////////////////////////////////////////////////////
void PlayerClass::RenderChild()
{
	//�E��
	m_Shoulder_R.Render();

	//����
	m_Shoulder_L.Render();

	//�w��
	m_Back.Render();

	//��
	m_Hip.Render();
}


//////////////////////////////////////////////////////////////////////////////
//public�֐�
//////////////////////////////////////////////////////////////////////////////

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
bool PlayerClass::Initialize(POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , THREE_DIMENSION_VECTOR* semi_long_vector , THREE_DIMENSION_VECTOR* semi_short_vector , bool flag)
{
	m_Position = *position;
	m_Velocity = *velocity;
	m_Accelaration = *accelaration;
	m_SemiLongVector = *semi_long_vector;
	m_SemiShortVector = *semi_short_vector;

	m_SemiLongAxis = m_SemiLongVector.Magnitude();
	m_SemiShortAxis = m_SemiShortVector.Magnitude();

	SetVertex();

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