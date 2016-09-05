#include "system.h"
#include <time.h>
#include <math.h>

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
	POSITION Box1Position = box1->GetPosition();	//box1�̈ʒu
	POSITION Box2Position = box2->GetPosition();	//box2�̈ʒu
	VARIABLE_VERTEX Box1Vertex;	//box1�̒��_
	VARIABLE_VERTEX Box2Vertex;	//box2�̒��_
	for(int i = 0 ; i < 4 ; i++)
	{
		Box1Vertex.m_VertexPosition.push_back(Box1Position);
		Box2Vertex.m_VertexPosition.push_back(Box2Position);
	}
	Box1Vertex = box1->GetVertex();
	Box2Vertex = box2->GetVertex();
	THREE_DIMENSION_VECTOR Box1SemiLongVector = box1->GetSemiLongVector();	//box1�̔������x�N�g��
	THREE_DIMENSION_VECTOR Box2SemiLongVector = box2->GetSemiLongVector();	//box2�̔������x�N�g��
	THREE_DIMENSION_VECTOR Box1SemiShortVector = box1->GetSemiShortVector();	//box1�̔��Z���x�N�g��
	THREE_DIMENSION_VECTOR Box2SemiShortVector = box2->GetSemiShortVector();	//box2�̔��Z���x�N�g��

	//���݂���������\�������邩�𔻒肷��
	if(abs(Box1Position.m_Vector.x - Box2Position.m_Vector.x) < box1->GetSemiLongAxis() + box2->GetSemiLongAxis() &&
		abs(Box1Position.m_Vector.y - Box2Position.m_Vector.y) < box1->GetSemiShortAxis() + box2->GetSemiLongAxis())
	{
		POSITION LocalVertex_of_Box1Looking_from_Box2;	//box2���猩��box1�̒��_
		POSITION LocalVertex_of_Box2Looking_from_Box1;	//box1���猩��box2�̒��_
		double length;	//����

		//box2����box1�̒��_������ꍇ
		 length = GetDistance(&Box1Position , &Box2Position);	//box1��box2�̋���

		//�ǂ̒��_����ԋ߂������l����
		for(int i = 0 ; i < 4 ; i++)
		{
			if(length < GetDistance(&Box1Vertex.m_VertexPosition[i], &Box2Position))
			{
				//��ԋ߂����_�̃��[�J�����W���o��
				LocalVertex_of_Box1Looking_from_Box2.m_Vector = Box1Vertex.m_VertexPosition[i].m_Vector - Box2Position.m_Vector;

				//length�̍X�V
				length = GetDistance(&Box1Vertex.m_VertexPosition[i] , &Box2Position);
			}
		}

		//box2���猩��box1�̒��_��x������y�������傫���Ƃ�
		if(abs(LocalVertex_of_Box1Looking_from_Box2.m_Vector.x) > abs(LocalVertex_of_Box1Looking_from_Box2.m_Vector.y))
		{
			//box2���猩��box1�̒��_��x������box2�̔���������菬����
			//����
			//box2���猩��box1�̒��_��y������box2�̔��Z������菬�����Ƃ�
			if(abs(LocalVertex_of_Box1Looking_from_Box2.m_Vector.x) < box2->GetSemiLongAxis() &&
				abs(LocalVertex_of_Box1Looking_from_Box2.m_Vector.y) < box2->GetSemiShortAxis())
			{
				//swap���ă��������J������
				std::vector<POSITION> NullVector1;
				Box1Vertex.m_VertexPosition.swap(NullVector1);
				std::vector<POSITION> NullVector2;
				Box2Vertex.m_VertexPosition.swap(NullVector2);
				//true��Ԃ�
				return true;
			}
		}
		//box2���猩��box1�̒��_��y������x�������傫���Ƃ�
		else
		{
			//box2���猩��box1�̒��_��x������box2�̔��Z������菬����
			//����
			//box2���猩��box1�̒��_��y������box2�̔���������菬�����Ƃ�
			if(abs(LocalVertex_of_Box1Looking_from_Box2.m_Vector.x) < box2->GetSemiShortAxis() &&
				abs(LocalVertex_of_Box1Looking_from_Box2.m_Vector.y) < box2->GetSemiLongAxis())
			{
				//swap���ă��������J������
				std::vector<POSITION> NullVector1;
				Box1Vertex.m_VertexPosition.swap(NullVector1);
				std::vector<POSITION> NullVector2;
				Box2Vertex.m_VertexPosition.swap(NullVector2);
				//true��Ԃ�
				return true;
			}
		}

		//box1����box2�̒��_������ꍇ
		 length = GetDistance(&Box2Position , &Box1Position);	//box1��box2�̋���

		//�ǂ̒��_����ԋ߂������l����
		for(int i = 1 ; i <= 4 ; i++)
		{
			if(length < GetDistance(&Box2Vertex.m_VertexPosition[i], &Box1Position))
			{
				//��ԋ߂����_�̃��[�J�����W���o��
				LocalVertex_of_Box2Looking_from_Box1.m_Vector = Box2Vertex.m_VertexPosition[i].m_Vector - Box1Position.m_Vector;

				//length�̍X�V
				length = GetDistance(&Box2Vertex.m_VertexPosition[i] , &Box1Position);
			}
		}
			
		//box1���猩��box2�̒��_��x������y�������傫���Ƃ�
		if(abs(LocalVertex_of_Box2Looking_from_Box1.m_Vector.x) > abs(LocalVertex_of_Box2Looking_from_Box1.m_Vector.y))
		{
			//box1���猩��box2�̒��_��x������box1�̔���������菬����
			//����
			//box1���猩��box2�̒��_��y������box1�̔��Z������菬�����Ƃ�
			if(abs(LocalVertex_of_Box2Looking_from_Box1.m_Vector.x) < box1->GetSemiLongAxis() &&
				abs(LocalVertex_of_Box2Looking_from_Box1.m_Vector.y) < box1->GetSemiShortAxis())
			{
				//swap���ă��������J������
				std::vector<POSITION> NullVector1;
				Box1Vertex.m_VertexPosition.swap(NullVector1);
				std::vector<POSITION> NullVector2;
				Box2Vertex.m_VertexPosition.swap(NullVector2);
				//true��Ԃ�
				return true;
			}
		}
		//box1���猩��box2�̒��_��y������x�������傫���Ƃ�
		else
		{
			//box1���猩��box2�̒��_��x������box1�̔��Z������菬����
			//����
			//box1���猩��box2�̒��_��y������box1�̔���������菬�����Ƃ�
			if(abs(LocalVertex_of_Box2Looking_from_Box1.m_Vector.x) < box1->GetSemiShortAxis() &&
				abs(LocalVertex_of_Box2Looking_from_Box1.m_Vector.y) < box1->GetSemiLongAxis())
			{
				//swap���ă��������J������
				std::vector<POSITION> NullVector1;
				Box1Vertex.m_VertexPosition.swap(NullVector1);
				std::vector<POSITION> NullVector2;
				Box2Vertex.m_VertexPosition.swap(NullVector2);
				//true��Ԃ�
				return true;
			}
		}

	}
	//swap���ă��������J������
	std::vector<POSITION> NullVector1;
	Box1Vertex.m_VertexPosition.swap(NullVector1);
	std::vector<POSITION> NullVector2;
	Box2Vertex.m_VertexPosition.swap(NullVector2);
	//false��Ԃ�
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
		VARIABLE_VERTEX Box1Vertex;
		for(int i = 0 ; i < 4 ; i++)
		{
			Box1Vertex.m_VertexPosition.push_back(Box1Position);
		}
		Box1Vertex = box1->GetVertex();
		THREE_DIMENSION_VECTOR Box1SemiLongVector = box1->GetSemiLongVector();
		THREE_DIMENSION_VECTOR Box1SemiShortVector = box1->GetSemiShortVector();

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

			//	switch (i)
			//	{
			//	case 1:
			//		if(length < GetDistance(&box1->m_vertex.vertex1 , &circle1->m_position))
			//		{
			//			//box1.vertex1�̔���
			//			//box1.vertex1�̃��[�J�����W���o��
			//			LocalVertex_of_Box1Looking_from_Circle1.x = box1->m_vertex.vertex1.x - circle1->m_position.x;	//x���W
			//			LocalVertex_of_Box1Looking_from_Circle1.y = box1->m_vertex.vertex1.y - circle1->m_position.y;	//y���W

			//			//length�̍X�V
			//			length = GetDistance(&box1->m_vertex.vertex1 , &circle1->m_position);
			//		}
			//		break;

			//	case 2:
			//		if(length < GetDistance(&box1->m_vertex.vertex2 , &circle1->m_position))
			//		{
			//			//box1.vertex2�̔���
			//			//box1.vertex2�̃��[�J�����W���o��
			//			LocalVertex_of_Box1Looking_from_Circle1.x = box1->m_vertex.vertex2.x - circle1->m_position.x;	//x���W
			//			LocalVertex_of_Box1Looking_from_Circle1.y = box1->m_vertex.vertex2.y - circle1->m_position.y;	//y���W

			//			//length�̍X�V
			//			length = GetDistance(&box1->m_vertex.vertex2 , &circle1->m_position);
			//		}
			//		break;

			//	case 3:
			//		if(length < GetDistance(&box1->m_vertex.vertex3 , &circle1->m_position))
			//		{
			//			//box1.vertex3�̔���
			//			//box1.vertex3�̃��[�J�����W���o��
			//			LocalVertex_of_Box1Looking_from_Circle1.x = box1->m_vertex.vertex3.x - circle1->m_position.x;	//x���W
			//			LocalVertex_of_Box1Looking_from_Circle1.y = box1->m_vertex.vertex3.y - circle1->m_position.y;	//y���W

			//			//length�̍X�V
			//			length = GetDistance(&box1->m_vertex.vertex3 , &circle1->m_position);		//		}
			//		break;

			//	case 4:
			//		if(length < GetDistance(&box1->m_vertex.vertex4 , &circle1->m_position))
			//		{
			//			//box1.vertex4�̔���
			//			//box1.vertex4�̃��[�J�����W���o��
			//			LocalVertex_of_Box1Looking_from_Circle1.x = box1->m_vertex.vertex4.x - circle1->m_position.x;	//x���W
			//			LocalVertex_of_Box1Looking_from_Circle1.y = box1->m_vertex.vertex4.y - circle1->m_position.y;	//y���W

			//			//length�̍X�V
			//			length = GetDistance(&box1->m_vertex.vertex4 , &circle1->m_position);
			//		}
			//		break;
			//	}
		}

		//���_�Ɠ������Ă��邩�m�F����
		if(LocalVertex_of_Box1Looking_from_Circle1.m_Vector.Magnitude() < circle1->GetRadius())
		{
			std::vector<POSITION> NullVector;
			Box1Vertex.m_VertexPosition.swap(NullVector);
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
				std::vector<POSITION> NullVector;
				Box1Vertex.m_VertexPosition.swap(NullVector);
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
				std::vector<POSITION> NullVector;
				Box1Vertex.m_VertexPosition.swap(NullVector);
				return true;
			}
		}
		
		std::vector<POSITION> NullVector;
		Box1Vertex.m_VertexPosition.swap(NullVector);
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
double InnerProduct(THREE_DIMENSION_VECTOR *vector1 , THREE_DIMENSION_VECTOR *vector2)
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
THREE_DIMENSION_VECTOR CrossProduct(THREE_DIMENSION_VECTOR *vector1 , THREE_DIMENSION_VECTOR *vector2)
{
	THREE_DIMENSION_VECTOR ret;
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
//	2�����x�N�g������]������
//����:
//	double& x:�x�N�g����x����
//	double& y:�x�N�g����y����
//	double angle:��]������p�x(���W�A��)
//////////////////////////////////////////////////////////////////////////////
void RotateVector2(double& x ,double& y ,double angle)
{
	double TempX = x;	//�ꎞ�I��x���W�����邽�߂̕ϐ�
	double TempY = y;	//�ꎞ�I��y���W�����邽�߂̕ϐ�

	//�s��v�Z
	x = TempX * cos(angle) - TempY * sin(angle);
	y = TempX * sin(angle) + TempY * cos(angle);
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

template<class T>
void ReleaseVector(std::vector<T> &obj)
{
	std::vector<T> NullVector;
	obj.swap(NullVector);
}

double Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesX(double value)
{
	return 2.0 * value / WINDOW_WIDTH - 1.0;
}

double Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesY(double value)
{
	return 2.0 * value / WINDOW_HEIGHT - 1.0;
}