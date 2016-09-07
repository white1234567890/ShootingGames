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
	m_Child.Initialize(&POSITION(50 , 50) , &VELOCITY() , &ACCELARATION() , &THREE_DIMENSION_VECTOR(10) , &THREE_DIMENSION_VECTOR(0 , 10));
	m_Child.SetPosition(&(m_Position.m_Vector + m_Child.GetLocalPosition().m_Vector));
	m_Child.SetVertex();
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
	m_Child.SetPosition(&(m_Position.m_Vector + RotateVector2(m_Child.GetLocalPosition().m_Vector.x , m_Child.GetLocalPosition().m_Vector.y , m_Angle)));
	m_Child.Update();
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	�q�I�u�W�F�N�g��`�悷��
//////////////////////////////////////////////////////////////////////////////
void PlayerClass::RenderChild()
{
	m_Child.Render();
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
	m_AngleVelocity = M_PI / 360 * 0.1;

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
	RotateObject(GetAngleVelocity());	//���Ӗ��ɉ�]������
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

	//���S�_��`��
	glBegin(GL_POINTS);
	glVertex2d(Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesX(m_Position.m_Vector.x) ,
		Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesY(m_Position.m_Vector.y));
	glEnd();

	//�l�p��`��
	glBegin(GL_LINE_LOOP);

	//�e���_
	for(unsigned int i = 0 ; i < m_Vertex.size() ; i++)
	{
		glVertex2d(Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesX(m_Vertex.m_VertexPosition[i].m_Vector.x) ,
			Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesY(m_Vertex.m_VertexPosition[i].m_Vector.y));
	}

	glEnd();

	RenderChild();
}