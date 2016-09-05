#include <gl\glew.h>
#include <gl\glut.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include "BoxClass.h"
#include "system.h"

//////////////////////////////////////////////////////////////////////////////
//�R���X�g���N�^
//////////////////////////////////////////////////////////////////////////////
BoxClass::BoxClass(void)
{
	for(int i = 0 ; i < 4 ; i++)
	{
		m_Vertex.m_VertexPosition.push_back(POSITION());
	}
}

//////////////////////////////////////////////////////////////////////////////
//�f�X�g���N�^
//////////////////////////////////////////////////////////////////////////////
BoxClass::~BoxClass(void)
{
	std::vector<POSITION> Nullvector;
	m_Vertex.m_VertexPosition.swap(Nullvector);
}

//////////////////////////////////////////////////////////////////////////////
//protected�֐�
//////////////////////////////////////////////////////////////////////////////

bool BoxClass::Initialize()
{
	return true;
}

void BoxClass::RotateObject(double angle)
{
	RotateVector2(m_SemiLongVector.x , m_SemiLongVector.y , angle);
	RotateVector2(m_SemiShortVector.x , m_SemiShortVector.y , angle);
}

//////////////////////////////////////////////////////////////////////////////
//public�֐�
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	���_���W���擾����
//�߂�l:
//	m_Vertex:���_���W
//////////////////////////////////////////////////////////////////////////////
VARIABLE_VERTEX BoxClass::GetVertex()
{
	return m_Vertex;
}

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	���_���W���擾����
//����:
//	i:���_�̔z��ԍ�
//�߂�l:
//	m_VertexPosition[i]:���_���W
//////////////////////////////////////////////////////////////////////////////
POSITION BoxClass::GetVertex(unsigned int i)
{
	if(i < m_Vertex.m_VertexPosition.size())
	{
		return m_Vertex.m_VertexPosition[i];
	}
	return m_Vertex.m_VertexPosition[0];
}

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	���_�����擾����
//�߂�l:
//	m_Vertex.m_VertexPosition.size:���_��
//////////////////////////////////////////////////////////////////////////////
int BoxClass::GetVertexSize()
{
	return m_Vertex.m_VertexPosition.size();
}

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	��`�̔������̒������擾����
//�߂�l:
//	m_SemiLongAxis:��`�̔������̒���
//////////////////////////////////////////////////////////////////////////////
double BoxClass::GetSemiLongAxis()
{
	return m_SemiLongAxis;
}

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	��`�̔��Z���̒������擾����
//�߂�l:
//	m_SemiShortAxis:��`�̔��Z���̒���
//////////////////////////////////////////////////////////////////////////////
double BoxClass::GetSemiShortAxis()
{
	return m_SemiShortAxis;
}

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	��`�̔������̃x�N�g�����擾����
//�߂�l:
//	m_SemiLongVector:��`�̔������̃x�N�g��
//////////////////////////////////////////////////////////////////////////////
THREE_DIMENSION_VECTOR BoxClass::GetSemiLongVector()
{
	return m_SemiLongVector;
}

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	��`�̔��Z���̃x�N�g�����擾����
//�߂�l:
//	m_SemiShortVector:��`�̔��Z���̃x�N�g��
//////////////////////////////////////////////////////////////////////////////
THREE_DIMENSION_VECTOR BoxClass::GetSemiShortVector()
{
	return m_SemiShortVector;
}

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	��`��4�̒��_���Z�o����
//////////////////////////////////////////////////////////////////////////////
void BoxClass::SetVertex()
{
	m_Vertex.m_VertexPosition[0].m_Vector.Set(m_Position.m_Vector.x + m_SemiLongVector.x + m_SemiShortVector.x , 
		m_Position.m_Vector.y + m_SemiLongVector.y + m_SemiShortVector.y , 0);
	m_Vertex.m_VertexPosition[1].m_Vector.Set(m_Position.m_Vector.x + m_SemiLongVector.x - m_SemiShortVector.x ,
		m_Position.m_Vector.y + m_SemiLongVector.y - m_SemiShortVector.y , 0);
	m_Vertex.m_VertexPosition[2].m_Vector.Set(m_Position.m_Vector.x - m_SemiLongVector.x - m_SemiShortVector.x ,
		m_Position.m_Vector.y - m_SemiLongVector.y - m_SemiShortVector.y , 0);
	m_Vertex.m_VertexPosition[3].m_Vector.Set(m_Position.m_Vector.x - m_SemiLongVector.x + m_SemiShortVector.x ,
		m_Position.m_Vector.y - m_SemiLongVector.y + m_SemiShortVector.y , 0);
}

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	�X�V
//////////////////////////////////////////////////////////////////////////////
bool BoxClass::Update()
{
	RotateObject(M_PI / 360 * 0.1);
	MoveObject();
	SetVertex();
	AccelObject();
	return true;
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
bool BoxClass::Initialize(POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , THREE_DIMENSION_VECTOR* semi_long_vector , THREE_DIMENSION_VECTOR* semi_short_vector , bool flag)
{
	m_Position = *position;
	m_Velocity = *velocity;
	m_Accelaration = *accelaration;
	m_SemiLongVector = *semi_long_vector;
	m_SemiShortVector = *semi_short_vector;

	m_SemiLongAxis = m_SemiLongVector.Magnitude();
	m_SemiShortAxis = m_SemiShortVector.Magnitude();

	SetVertex();

	return true;
}

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	�`��
//////////////////////////////////////////////////////////////////////////////
void BoxClass::Render()
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
	for(unsigned int i = 0 ; i < m_Vertex.m_VertexPosition.size() ; i++)
	{
		glVertex2d(Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesX(m_Vertex.m_VertexPosition[i].m_Vector.x) ,
			Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesY(m_Vertex.m_VertexPosition[i].m_Vector.y));
	}

	glEnd();
}