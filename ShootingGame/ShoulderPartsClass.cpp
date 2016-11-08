#include "ShoulderPartsClass.h"

#include <gl\glew.h>
#include <gl\glut.h>

#include "system.h"

#include "PlayerBulletManagerClass.h"
ShoulderPartsClass::ShoulderPartsClass(void)
{
	m_Pointer_to_Parent = NULL;
}


ShoulderPartsClass::~ShoulderPartsClass(void)
{
}

//////////////////////////////////////////////////////////////////////////////
//private�֐�
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//���p�[�c�̃f�[�^�����[�h����
//����:
//	shoulder_type:���[�h����p�[�c�^�C�v
//�߂�l:
//	true:�f�[�^�����[�h����
//	false:�f�[�^�̃��[�h�Ɏ��s����
//////////////////////////////////////////////////////////////////////////////
bool LoadShoulderPartsData(int shoulder_type)
{
}

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	�V���b�g�̃p�����[�^��ݒ肷��
//����:
//	shot_type:�V���b�g�^�C�v
//	barrel_range:�����ʒu�����肷�邽�߂̒���
//	velocity:�V���b�g�̏���
//	shot_speed:�V���b�g�̑���
//	accelaration:�V���b�g�̉����x
//	shot_semi_long_vector:�V���b�g�̉摜�̔������x�N�g��
//	shot_semishort_vector:�V���b�g�̉摜�̔��Z���x�N�g��
//////////////////////////////////////////////////////////////////////////////
void ShoulderPartsClass::SetShotStatus(int shot_type , double barrel_range , VELOCITY* velocity , double shot_speed , ACCELARATION* accelaration , THREE_DIMENSIONAL_VECTOR* shot_semi_long_vector , THREE_DIMENSIONAL_VECTOR* shot_semi_short_vector)
{
	m_ShotType = shot_type;
	m_BarrelRange = barrel_range;
	m_ShotVelocity = *velocity;
	m_ShotSpeed = shot_speed;
	m_ShotAccelaration = *accelaration;
	m_ShotSemiLongVector = *shot_semi_long_vector;
	m_ShotSemiShortVector = *shot_semi_short_vector;
}

//////////////////////////////////////////////////////////////////////////////
//public�֐�
//////////////////////////////////////////////////////////////////////////////

//�Q�b�^�i�ʒu�j
POSITION ShoulderPartsClass::GetShotPosition()
{
	return m_ShotPosition;
}

//�Q�b�^�i���x�j
VELOCITY ShoulderPartsClass::GetShotVelocity()
{
	return m_ShotVelocity;
}
	
//�Q�b�^�i�����x�j
ACCELARATION ShoulderPartsClass::GetShotAccelaration()
{
	return m_ShotAccelaration;
}
	
//�Q�b�^�i�������x�N�g���j
THREE_DIMENSIONAL_VECTOR ShoulderPartsClass::GetShotSemiLongVector()
{
	return m_ShotSemiLongVector;
}
	
//�Q�b�^�i���Z���x�N�g���j
THREE_DIMENSIONAL_VECTOR ShoulderPartsClass::GetShotSemiShortVector()
{
	return m_ShotSemiShortVector;
}

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	������
//����:
//	local_position:�v���C���[���猩���ʒu
//	local_velocity:�v���C���[���猩�����x
//	local_accelaration:�v���C���[���猩�������x
//	semi_long_vector:�摜�̑傫��(��������)
//	semi_short_vector:�摜�̑傫��(���Z����)
//	player:�v���C���[�ւ̃|�C���^
//	flag:�`��t���O
//�߂�l:
//	true:����
//	false:���s
//////////////////////////////////////////////////////////////////////////////
bool ShoulderPartsClass::Initialize(POSITION* local_position , VELOCITY* local_velocity , ACCELARATION* local_accelaration , PlayerClass* player , bool flag)
{
	m_Position = *local_position;
	m_Velocity = *local_velocity;
	m_Accelaration = *local_accelaration;

	m_SemiLongAxis = m_SemiLongVector.Magnitude();
	m_SemiShortAxis = m_SemiShortVector.Magnitude();

	m_ForwardVector.Set(0 , 1);

	SetVertex();

	m_Pointer_to_Parent = player;

	return true;
}

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	�X�V
//����:
//	shot_flag:�V���b�g�����������Ȃ����̃t���O
//////////////////////////////////////////////////////////////////////////////
bool ShoulderPartsClass::Update(bool shot_flag)
{
	//�V���b�g�̈ʒu������o��
	m_ShotPosition.m_Vector = m_Pointer_to_Parent->GetPosition().m_Vector + m_Position.m_Vector + RotateVector2(&m_ForwardVector , m_Angle) * m_BarrelRange;
	
	//�V���b�g�̑��x������o��
	m_ShotVelocity.m_Vector = RotateVector2(&m_ForwardVector , m_Angle) * m_ShotSpeed;

	//�V���b�g�����Ƃ�
	if(shot_flag)
	{
		//�V���b�g�𐶐�����
		cl_PlayerBulletManager->CreateBullet(&m_ShotPosition , &m_ShotVelocity , &m_ShotAccelaration , &m_ShotSemiLongVector , &m_ShotSemiShortVector);
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	�`��
//����:
//	player_world_position:�v���C���[�̈ʒu
//////////////////////////////////////////////////////////////////////////////
void ShoulderPartsClass::Render(POSITION* player_world_positoin)
{
	//�F�ݒ�i�ԁj
	glColor3f(1.f , 0 , 0);

	//�l�p��`��
	glBegin(GL_POLYGON);

	//�e���_
	for(unsigned int i = 0 ; i < m_Vertex.size() ; i++)
	{
		glVertex2d(Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesX(player_world_positoin->m_Vector.x + m_Vertex.m_VertexPosition[i].m_Vector.x) ,
			Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesY(player_world_positoin->m_Vector.y + m_Vertex.m_VertexPosition[i].m_Vector.y));
	}

	glEnd();
}