#pragma once
#include "common.h"
#include "CircleClass.h"
#include "BoxClass.h"

//�񋓑̂̐錾
typedef enum HIT
{
	NO_HIT,//�������Ă��Ȃ�
	RIGHT_HIT,//�E�ɓ������Ă���
	UPPER_RIGHT_HIT,//�E��ɓ������Ă���
	TOP_HIT,//��ɓ������Ă���
	UPPER_LEFT_HIT,//����ɓ������Ă���
	LEFT_HIT,//���ɓ������Ă���
	LOWER_LEFT_HIT,//�����ɓ������Ă���
	BOTTOM_HIT,//���ɓ������Ă���
	LOWER_RIGHT_HIT//�E���ɓ������Ă���
};

//�֐��̐錾

///////////////////////////////////////////////////////////////////////////
//�T��:
//	�����𔭐�������
//����:
//	int max_of_randvalue:�����������������̍ő�l
//	int min_of_randvalue:�����������������̍ŏ��l
//�߂�l:��������������
///////////////////////////////////////////////////////////////////////////
int GenerateRandValue(int max_of_randvalue , int min_of_randvalue);

///////////////////////////////////////////////////////////////////////////
//�T��:
//	�~�Ɖ~�̓����蔻��
//����:
//	circle1:�~�̍\���̂ւ̃|�C���^1
//	circle2:�~�̍\���̂ւ̃|�C���^2
//�߂�l:
//	true:��������
//	false:�������Ă��Ȃ�
///////////////////////////////////////////////////////////////////////////
bool CheckHitCircleandCircle(CircleClass *circle1 , CircleClass *circle2);

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	��`�Ƌ�`�̂����蔻��
//����:
//	box1:��`�̍\���̂ւ̃|�C���^1
//	box2:��`�̍\���̂ւ̃|�C���^2
//�߂�l:	
//	int TRUE:��������
//	NO_HIT:������Ȃ�����
//////////////////////////////////////////////////////////////////////////////
bool CheckHitBoxandBox(BoxClass *box1 , BoxClass *box2);

///////////////////////////////////////////////////////////////////////////
//�T��:
//	�~�Ƌ�`�̂����蔻��
//����:
//	circle1:�~�̍\���̂ւ̃|�C���^
//	box1:��`�̍\���̂ւ̃|�C���^
//�߂�l:	
//	true:��������
//	false:������Ȃ�����
//////////////////////////////////////////////////////////////////////////////
bool CheckHitCircleandBox(CircleClass *circle1 , BoxClass *box1);

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	2�_�Ԃ̋��������
//����:
//	POSITION* position1:�_1�̍��W�ւ̃|�C���^
//	POSITION* position2:�_2�̍��W�ւ̃|�C���^
//�߂�l:
//	2�_�Ԃ̋���(double�^)
//////////////////////////////////////////////////////////////////////////////
double GetDistance(POSITION* position1 , POSITION* position2);

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	���όv�Z
//����:
//	*vector1:�x�N�g��1
//	*vector2:�x�N�g��2
//�߂�l:
//	���ς����l
//////////////////////////////////////////////////////////////////////////////
double InnerProduct(THREE_DIMENSIONAL_VECTOR *vector1 , THREE_DIMENSIONAL_VECTOR *vector2);

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	�O�όv�Z
//����:
//	*vector1:�x�N�g��1
//	*vector2:�x�N�g��2
//�߂�l:
//	�O�ς����l
//////////////////////////////////////////////////////////////////////////////
THREE_DIMENSIONAL_VECTOR CrossProduct(THREE_DIMENSIONAL_VECTOR *vector1 , THREE_DIMENSIONAL_VECTOR *vector2);

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	�����蔻������͈͂����肷��
//����:
//	POSITION* objact1:�I�u�W�F�N�g1�̈ʒu�x�N�g��
//	POSITION* object2:�I�u�W�F�N�g2�̈ʒu�x�N�g��
//	double range:���肷��͈͂̔��a
//�߂�l:
//	bool true:�͈͓��ɂ���
//	bool false:�͈͓��ɂ��Ȃ�
//////////////////////////////////////////////////////////////////////////////
bool HitBoxandRangeContact(POSITION* object1 , POSITION* object2 , double range);

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	2�����x�N�g������]�������x�N�g�������߂�
//����:
//	THREE_DIMENSIONAL_VECTOR *vector:���̃x�N�g��
//	double angle:��]������p�x(���W�A��)
//////////////////////////////////////////////////////////////////////////////
THREE_DIMENSIONAL_VECTOR RotateVector2(THREE_DIMENSIONAL_VECTOR *vector , double angle);

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	2�����x�N�g������]������
//����:
//	THREE_DIMENSIONAL_VECTOR &vector:��]������x�N�g��
//	double angle:��]������p�x(���W�A��)
//////////////////////////////////////////////////////////////////////////////
void RotateVector2(THREE_DIMENSIONAL_VECTOR &vector , double angle);

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	�񎟌��x�N�g���̊p�x�����
//����:
//	double x:�x�N�g����x����
//	double y:�x�N�g����y����
//�߂�l:
//	double angle:�x�N�g���̊p�x
//////////////////////////////////////////////////////////////////////////////
double GetVector2Angle(double x , double y);

double InterSectionTime(POSITION* Position_of_Object1 , VELOCITY* Velocity_of_Object1 , POSITION* Position_of_Object2 , VELOCITY* Velocity_of_Object2);

template<typename T>
void ReleaseVector(std::vector<T> &obj)
{
	std::vector<T> NullVector;
	obj.swap(NullVector);
}

double Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesX(double value);

double Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesY(double value);