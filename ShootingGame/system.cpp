#include "system.h"
#include <time.h>
#include <math.h>
#include <random>

//////////////////////////////////////////////////////////////////////////
//�T��:
//	�����𔭐�������
//����:
//	int max_of_randvalue:�����������������̍ő�l
//	int min_of_randvalue:�����������������̍ŏ��l
//�߂�l:��������������
//////////////////////////////////////////////////////////////////////////
int GenerateRandValue(int max_of_randvalue , int min_of_randvalue)
{
	static unsigned int randvalue = 0;			//���������������l��ۑ����Ă������߂̕ϐ�
	static unsigned int randcount = 0;				//���������闐���l�̋K�����𗐂����߂̕ϐ�
	
	//�����̃V�[�h�l�ݒ�
	if(randvalue == 0)
	{
		srand((unsigned int)time(NULL));
	}
	//�������g�p���ăV�[�h�l���Đݒ�
	else
	{
		srand((unsigned int)(randvalue + randcount++));
	}

	//����������������ۑ�����
	randvalue = rand();

	if(min_of_randvalue >= 0)
	{
		return randvalue % ((max_of_randvalue + 1) - min_of_randvalue) + min_of_randvalue;
	}
	else
	{
		if(rand() % 2 == 0)
		{
			return randvalue % ((max_of_randvalue + 1) - min_of_randvalue) + min_of_randvalue;			
		}
		else
		{
			return -((int)randvalue % ((max_of_randvalue + 1) - min_of_randvalue) + min_of_randvalue);
		}
	}
}

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
bool CheckHitCircleandCircle(CircleClass *circle1 , CircleClass *circle2)
{
	POSITION Circle1Position = circle1->GetPosition();
	POSITION Circle2Position = circle2->GetPosition();
	double Circle1Radius = circle1->GetRadius();
	double Circle2Radius = circle2->GetRadius();

	//�s�^�S���X�̒藝�𗘗p���Ĕ�����s��
	if((Circle2Position.m_Vector.x - Circle1Position.m_Vector.x) * (Circle2Position.m_Vector.x - Circle1Position.m_Vector.x) +
		(Circle2Position.m_Vector.y - Circle1Position.m_Vector.y) * (Circle2Position.m_Vector.y - Circle1Position.m_Vector.y) +
		(Circle2Position.m_Vector.z - Circle1Position.m_Vector.z) * (Circle2Position.m_Vector.z - Circle1Position.m_Vector.z) <=
		(Circle2Radius + Circle1Radius) * (Circle2Radius + Circle1Radius))
	{
		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	��`�Ƌ�`�̂����蔻��
//����:
//	BOX* box1:��`�̍\���̂ւ̃|�C���^1
//	BOX* box2:��`�̍\���̂ւ̃|�C���^2
//�߂�l:	
//	int TRUE:��������
//	NO_HIT:������Ȃ�����
//////////////////////////////////////////////////////////////////////////////
bool CheckHitBoxandBox(BoxClass *box1 , BoxClass *box2)
{
	//�����蔻������ׂ������ׂ�
	THREE_DIMENSIONAL_VECTOR SemiDiagonalVector_of_Box1 = box1->GetSemiLongVector() + box1->GetSemiShortVector();
	THREE_DIMENSIONAL_VECTOR SemiDiagonalVector_of_Box2 = box2->GetSemiLongVector() + box2->GetSemiShortVector();

	//�����蔻������ׂ������ׂ�
	if(GetDistance(&box1->GetPosition() , &box2->GetPosition()) <= SemiDiagonalVector_of_Box1.Magnitude() + SemiDiagonalVector_of_Box2.Magnitude())
	{
		//box1����݂�box2�𒲂ׂ�
		double TempDistance = 0;	//�ꎞ�I�ɋ���������ϐ�
		THREE_DIMENSIONAL_VECTOR TempVector;	//�ꎞ�I�Ƀx�N�g��������ϐ�
		int ExcludeVertex = -1;	//��ԉ������_���L������ϐ�

		//��ԉ������_�����O����
		for(int i = 0 ; i < 4 ; i++)
		{
			//box1�̈ʒu��box2�̒��_�̋������ׂ�
			if(GetDistance(&box1->GetPosition() , &box2->GetVertex(i)) > TempDistance)
			{
				//��ԉ����_�̋�����ۑ�����
				TempDistance = GetDistance(&box1->GetPosition() , &box2->GetVertex(i));

				//��ԉ����_�̔z��ԍ���ۑ�����
				ExcludeVertex = i;
			}
		}
		
		//box2�̒��_��box1�̖ʐϓ��ɂ��邩���ׂ�
		for(int i = 0 ; i < 4 ; i++)
		{
			//���O�������_����Ȃ��Ƃ�
			if(i != ExcludeVertex)
			{
				TempVector = box2->GetVertex(i).m_Vector - box1->GetPosition().m_Vector;

				//box1����]���Ă��Ȃ��Ƃ�
				if(box1->GetAngle() != 0)
				{
					//�c�̕��������Ƃ�
					if(box1->GetSemiLongVector().x == 0)
					{
						//box1�̒��S����box2�̒��_�ւ̃x�N�g����x,y������
						//box1�̔��������A���Z������菬�������Ƃ𒲂ׂ�
						if(abs(TempVector.x) <= box1->GetSemiShortAxis() && abs(TempVector.y) <= box1->GetSemiLongAxis())
						{
							return true;
						}
					}
					//���̕��������Ƃ�
					else
					{
						//box1�̒��S����box2�̒��_�ւ̃x�N�g����x,y������
						//box1�̔��������A���Z������菬�������Ƃ𒲂ׂ�
						if(abs(TempVector.x) <= box1->GetSemiLongAxis() && abs(TempVector.y) <= box1->GetSemiShortAxis())
						{
							return true;
						}
					}
				}
				//box�P����]���Ă���Ƃ�
				else
				{
					//box1�̒��S����box�Q�̒��_�ւ̃x�N�g������]������
					THREE_DIMENSIONAL_VECTOR RotatedVector = RotateVector2(&TempVector , -box1->GetAngle());
					//box�P�̔������x�N�g������]������
					THREE_DIMENSIONAL_VECTOR RotatedSemiLongVector = RotateVector2(&box1->GetSemiLongVector() , -box1->GetAngle());

					//�c�̕��������Ƃ�
					if(RotatedSemiLongVector.x == 0)
					{
						//box1�̒��S����box2�̒��_�ւ̃x�N�g����x,y������
						//box1�̔��������A���Z������菬�������Ƃ𒲂ׂ�
						if(abs(RotatedVector.x) <= box1->GetSemiShortAxis() && abs(RotatedVector.y) <= box1->GetSemiLongAxis())
						{
							return true;
						}
					}
					//���̕��������Ƃ�
					else
					{
						//box1�̒��S����box2�̒��_�ւ̃x�N�g����x,y������
						//box1�̔��������A���Z������菬�������Ƃ𒲂ׂ�
						if(abs(RotatedVector.x) <= box1->GetSemiLongAxis() && abs(RotatedVector.y) <= box1->GetSemiShortAxis())
						{
							return true;
						}
					}
				}
			}
		}

		//box2����݂�box1�𒲂ׂ�
		TempDistance = 0;	//�ꎞ�I�ɋ���������ϐ�
		ExcludeVertex = -1;	//��ԉ������_���L������ϐ�

		//��ԉ������_�����O����
		for(int i = 0 ; i < 4 ; i++)
		{
			//box2�̈ʒu��box1�̒��_�̋������ׂ�
			if(GetDistance(&box2->GetPosition() , &box1->GetVertex(i)) > TempDistance)
			{
				//��ԉ����_�̋�����ۑ�����
				TempDistance = GetDistance(&box2->GetPosition() , &box1->GetVertex(i));

				//��ԉ����_�̔z��ԍ���ۑ�����
				ExcludeVertex = i;
			}
		}

		//box2�̒��_��box1�̖ʐϓ��ɂ��邩���ׂ�
		for(int i = 0 ; i < 4 ; i++)
		{
			//���O�������_����Ȃ��Ƃ�
			if(i != ExcludeVertex)
			{
				TempVector = box2->GetVertex(i).m_Vector - box1->GetPosition().m_Vector;

				//box2����]���Ă��Ȃ��Ƃ�
				if(box2->GetAngle() != 0)
				{
					//�c�̕��������Ƃ�
					if(box2->GetSemiLongVector().x == 0)
					{
						//box2�̒��S����box1�̒��_�ւ̃x�N�g����x,y������
						//box2�̔��������A���Z������菬�������Ƃ𒲂ׂ�
						if(abs(TempVector.x) <= box2->GetSemiShortAxis() && abs(TempVector.y) <= box2->GetSemiLongAxis())
						{
							return true;
						}
					}
					//���̕��������Ƃ�
					else
					{
						//box2�̒��S����box1�̒��_�ւ̃x�N�g����x,y������
						//box2�̔��������A���Z������菬�������Ƃ𒲂ׂ�
						if(abs(TempVector.x) <= box2->GetSemiLongAxis() && abs(TempVector.y) <= box2->GetSemiShortAxis())
						{
							return true;
						}
					}
				}
				//box2����]���Ă���Ƃ�
				else
				{
					//box2�̒��S����box1�̒��_�ւ̃x�N�g������]������
					THREE_DIMENSIONAL_VECTOR RotatedVector = RotateVector2(&TempVector , -box2->GetAngle());
					//box2�̔������x�N�g������]������
					THREE_DIMENSIONAL_VECTOR RotatedSemiLongVector = RotateVector2(&box2->GetSemiLongVector() , -box2->GetAngle());

					//�c�̕��������Ƃ�
					if(RotatedSemiLongVector.x == 0)
					{
						//box2�̒��S����box1�̒��_�ւ̃x�N�g����x,y������
						//box2�̔��������A���Z������菬�������Ƃ𒲂ׂ�
						if(abs(RotatedVector.x) <= box2->GetSemiShortAxis() && abs(RotatedVector.y) <= box2->GetSemiLongAxis())
						{
							return true;
						}
					}
					//���̕��������Ƃ�
					else
					{
						//box2�̒��S����box1�̒��_�ւ̃x�N�g����x,y������
						//box2�̔��������A���Z������菬�������Ƃ𒲂ׂ�
						if(abs(RotatedVector.x) <= box2->GetSemiLongAxis() && abs(RotatedVector.y) <= box2->GetSemiShortAxis())
						{
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////
//�T��:
//	�~�Ƌ�`�̂����蔻��
//����:
//	CIRCLE* circle1:�~
//	BOX* box1:��`
//�߂�l:	
//	int TRUE:��������
//	NO_HIT:������Ȃ�����
///////////////////////////////////////////////////////////////////////////
bool CheckHitCircleandBox(CircleClass *circle1 , BoxClass *box1)
{
	//���݂���������\�������邩�𔻒肷��
	if(HitBoxandRangeContact(&circle1->GetPosition() , &box1->GetPosition() , circle1->GetRadius() + box1->GetSemiLongAxis()))
	{
		POSITION Circle1Position = circle1->GetPosition();

		POSITION Box1Position = box1->GetPosition();
		FOUR_VERTEX Box1Vertex;

		Box1Vertex = box1->GetVertex();
		THREE_DIMENSIONAL_VECTOR Box1SemiLongVector = box1->GetSemiLongVector();
		THREE_DIMENSIONAL_VECTOR Box1SemiShortVector = box1->GetSemiShortVector();

		POSITION LocalVertex_of_Box1Looking_from_Circle1;
		double length;

		//circle1����box1�̒��_������
		length = GetDistance(&Circle1Position , &Box1Position);

		//���_�Ɠ������Ă��邩�m�F����
		//��ԋ߂����_�𒲂ׂ�
		for(int i = 1 ; i <= 4 ; i++)
		{
			if(length < GetDistance(&Box1Vertex.m_VertexPosition[i] , &Circle1Position))
			{
				//���_�̃��[�J�����W���o��
				LocalVertex_of_Box1Looking_from_Circle1.m_Vector.x = Box1Vertex.m_VertexPosition[i].m_Vector.x - Circle1Position.m_Vector.x;	//x���W
				LocalVertex_of_Box1Looking_from_Circle1.m_Vector.y = Box1Vertex.m_VertexPosition[i].m_Vector.y - Circle1Position.m_Vector.y;	//y���W

				//length�̍X�V
				length = GetDistance(&Box1Vertex.m_VertexPosition[i] , &Circle1Position);
			}
		}

		//���_�Ɠ������Ă��邩�m�F����
		if(LocalVertex_of_Box1Looking_from_Circle1.m_Vector.Magnitude() < circle1->GetRadius())
		{
			return true;
		}

		//�ӂƓ������Ă��邩�m�F����
		//�㉺�ӂƂ̂����蔻����m�F����
		if(Circle1Position.m_Vector.x < Box1Position.m_Vector.x + abs(Box1SemiLongVector.x + Box1SemiShortVector.x) &&
			Circle1Position.m_Vector.x > Box1Position.m_Vector.x - abs(Box1SemiLongVector.x + Box1SemiShortVector.x))
		{
			if((Circle1Position.m_Vector.y - Box1Position.m_Vector.y) * (Circle1Position.m_Vector.y - Box1Position.m_Vector.y) <
				(circle1->GetRadius() + abs(Box1SemiLongVector.y + Box1SemiShortVector.y)) *
				(circle1->GetRadius() + abs(Box1SemiLongVector.y + Box1SemiShortVector.y)))
			{
				return true;
			}
		}
		//���E�ӂƂ̂����蔻����m�F����
		else if(Circle1Position.m_Vector.y < Box1Position.m_Vector.y + abs(Box1SemiLongVector.y + Box1SemiShortVector.y) &&
			Circle1Position.m_Vector.y > Box1Position.m_Vector.y - abs(Box1SemiLongVector.y + Box1SemiShortVector.y))
		{
			if((Circle1Position.m_Vector.x - Box1Position.m_Vector.x) * (Circle1Position.m_Vector.x - Box1Position.m_Vector.x) <
				(circle1->GetRadius() + abs(Box1SemiLongVector.x + Box1SemiShortVector.x)) *
				(circle1->GetRadius() + abs(Box1SemiLongVector.x + Box1SemiShortVector.x)))
			{
				return true;
			}
		}
				
		return false;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	2�_�Ԃ̋��������
//����:
//	position1:�_1�̍��W�ւ̃|�C���^
//	position2:�_2�̍��W�ւ̃|�C���^
//�߂�l:
//	2�_�Ԃ̋���
//////////////////////////////////////////////////////////////////////////////
double GetDistance(POSITION *position1 , POSITION *position2)
{
	return sqrt((position1->m_Vector.x - position2->m_Vector.x) * (position1->m_Vector.x - position2->m_Vector.x) +
		(position1->m_Vector.y - position2->m_Vector.y) * (position1->m_Vector.y - position2->m_Vector.y) +
		(position1->m_Vector.z - position2->m_Vector.z) * (position1->m_Vector.z - position2->m_Vector.z));
}

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	���όv�Z
//����:
//	*vector1:�x�N�g��1
//	*vector2:�x�N�g��2
//�߂�l:
//	���ς����l
//////////////////////////////////////////////////////////////////////////////
double InnerProduct(THREE_DIMENSIONAL_VECTOR *vector1 , THREE_DIMENSIONAL_VECTOR *vector2)
{
	return vector1->x * vector2->x + vector1->y * vector2->y + vector1->z *vector2->z;
}

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	�O�όv�Z
//����:
//	*vector1:�x�N�g��1
//	*vector2:�x�N�g��2
//�߂�l:
//	�O�ς����l
//////////////////////////////////////////////////////////////////////////////
THREE_DIMENSIONAL_VECTOR CrossProduct(THREE_DIMENSIONAL_VECTOR *vector1 , THREE_DIMENSIONAL_VECTOR *vector2)
{
	THREE_DIMENSIONAL_VECTOR ret;
	ret.x = vector1->y * vector2->z - vector1->z * vector2->y;
	ret.y = vector1->z * vector2->x - vector1->x * vector2->z;
	ret.z = vector1->x * vector2->y - vector1->y * vector2->x;
	return ret;
}

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
bool HitBoxandRangeContact(POSITION* object1 , POSITION* object2 , double range)
{
	if(GetDistance(object1 , object2) > range)
	{
		return false;
	}
	else
	{
		return true;
	}
}

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	2�����x�N�g������]�������x�N�g�������߂�
//����:
//	THREE_DIMENSIONAL_VECTOR *vector:���̃x�N�g��
//	double angle:��]������p�x(���W�A��)
//////////////////////////////////////////////////////////////////////////////
THREE_DIMENSIONAL_VECTOR RotateVector2(THREE_DIMENSIONAL_VECTOR *vector , double angle)
{
	double TempX = vector->x;	//�ꎞ�I��x���W�����邽�߂̕ϐ�
	double TempY = vector->y;	//�ꎞ�I��y���W�����邽�߂̕ϐ�
	THREE_DIMENSIONAL_VECTOR ret;

	//�s��v�Z
	ret.x = TempX * cos(angle) - TempY * sin(angle);
	ret.y = TempX * sin(angle) + TempY * cos(angle);

	return ret;
}

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	2�����x�N�g������]������
//����:
//	THREE_DIMENSIONAL_VECTOR &vector:��]������x�N�g��
//	double angle:��]������p�x(���W�A��)
//////////////////////////////////////////////////////////////////////////////
void RotateVector2(THREE_DIMENSIONAL_VECTOR &vector , double angle)
{
	double TempX = vector.x;	//�ꎞ�I��x���W�����邽�߂̕ϐ�
	double TempY = vector.y;	//�ꎞ�I��y���W�����邽�߂̕ϐ�

	//�s��v�Z
	vector.x = TempX * cos(angle) - TempY * sin(angle);
	vector.y = TempX * sin(angle) + TempY * cos(angle);
}

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	�񎟌��x�N�g���̊p�x�����
//����:
//	double x:�x�N�g����x����
//	double y:�x�N�g����y����
//�߂�l:
//	double angle:�x�N�g���̊p�x
//////////////////////////////////////////////////////////////////////////////
double GetVector2Angle(double x , double y)
{
	return atan2(y , x);
}


double InterSectionTime(POSITION* Position_of_Object1 , VELOCITY* Velocity_of_Object1 , POSITION* Position_of_Object2 , VELOCITY* Velocity_of_Object2)
{
	double det = 0;
	if((det = Velocity_of_Object1->m_Vector.y * Velocity_of_Object2->m_Vector.x - Velocity_of_Object1->m_Vector.x * Velocity_of_Object2->m_Vector.y) == 0) return -1;
	double con = Velocity_of_Object2->m_Vector.x * (Position_of_Object2->m_Vector.y - Position_of_Object1->m_Vector.y) - Velocity_of_Object2->m_Vector.y * (Position_of_Object2->m_Vector.x - Position_of_Object1->m_Vector.x);

	double t = con / det;

	return t;
}

double Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesX(double value)
{
	return 2.0 * value / WINDOW_WIDTH - 1.0;
}

double Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesY(double value)
{
	return 2.0 * value / WINDOW_HEIGHT - 1.0;
}