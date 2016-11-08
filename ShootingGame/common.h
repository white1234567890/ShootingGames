#pragma once
#include "DebugSwitch.h"

#include <vector>

//�萔�̐錾

const int BASE_WINDOW_HEIGHT = 720;
const int BASE_WINDOW_WIDTH = 960;
const int SPEED_ASPECT = 10000000;


//�ÓI�ϐ��̐錾

static int WINDOW_HEIGHT = BASE_WINDOW_HEIGHT;	//�E�B���h�E�T�C�Y�c
static int WINDOW_WIDTH = BASE_WINDOW_WIDTH;	//�E�B���h�E�T�C�Y��
static double SPEED_Y_ASPECT = 50;	//�v���C���[�̑�����y����
static double SPEED_X_ASPECT = 50;	//�v���C���[�̑�����x����

//3�����x�N�g��
typedef struct THREE_DIMENSIONAL_VECTOR
{
	double x;	//x���W
	double y;	//y���W
	double z;	//z���W

	//�R���X�g���N�^
	THREE_DIMENSIONAL_VECTOR(double x = 0 , double y = 0 , double z = 0)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	//�x�N�g���̑����Z
	THREE_DIMENSIONAL_VECTOR operator + (THREE_DIMENSIONAL_VECTOR obj)
	{
		THREE_DIMENSIONAL_VECTOR ret;
		ret.x = this->x + obj.x;
		ret.y = this->y + obj.y;
		ret.z = this->z + obj.z;
		return ret;
	}

	//�x�N�g���̑����Z
	void operator += (THREE_DIMENSIONAL_VECTOR obj)
	{
		this->x = this->x + obj.x;
		this->y = this->y + obj.y;
		this->z = this->z + obj.z;
	}

	//�x�N�g���̈����Z
	THREE_DIMENSIONAL_VECTOR operator - (THREE_DIMENSIONAL_VECTOR obj)
	{
		THREE_DIMENSIONAL_VECTOR ret;
		ret.x = this->x - obj.x;
		ret.y = this->y - obj.y;
		ret.z = this->z - obj.z;
		return ret;
	}

	//�x�N�g���̈����Z
	void operator -= (THREE_DIMENSIONAL_VECTOR obj)
	{
		this->x = this->x - obj.x;
		this->y = this->y - obj.y;
		this->z = this->z - obj.z;
	}

	//�t�x�N�g��
	THREE_DIMENSIONAL_VECTOR operator - ()
	{
		THREE_DIMENSIONAL_VECTOR ret;
		ret.x = -this->x;
		ret.y = -this->y;
		ret.z = -this->z;
		return ret;
	}

	//�X�J���[�{
	THREE_DIMENSIONAL_VECTOR operator * (double obj)
	{
		THREE_DIMENSIONAL_VECTOR ret;
		ret.x = this->x * obj;
		ret.y = this->y * obj;
		ret.z = this->z * obj;
		return ret;
	}

	//�X�J���[�{
	void operator *= (double obj)
	{
		this->x = this->x * obj;
		this->y = this->y * obj;
		this->z = this->z * obj;
	}

	//�����̐ݒ�
	void Set(double x = 0 , double y = 0 , double z = 0)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	//�x�N�g���̑傫��
	double Magnitude()
	{
		return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	}

	//�P�ʃx�N�g��
	THREE_DIMENSIONAL_VECTOR GetNomalVector()
	{
		THREE_DIMENSIONAL_VECTOR ret;
		ret.x = this->x / this->Magnitude();
		ret.y = this->y / this->Magnitude();
		ret.z = this->z / this->Magnitude();
		return ret;
	}

	//�P�ʉ�
	void Nomalize()
	{
		*this = GetNomalVector();
	}
}THREE_DIMENSIONAL_VECTOR;

//�ʒu
typedef struct POSITION
{
	THREE_DIMENSIONAL_VECTOR m_Vector;	//�ʒu�x�N�g��
		
	//�R���X�g���N�^
	POSITION(double x = 0 , double y = 0 , double z = 0) : m_Vector(x , y , z){}
}POSITION;

//���x
typedef struct VELOCITY
{
	THREE_DIMENSIONAL_VECTOR m_Vector;	//���x�x�N�g��

	//�R���X�g���N�^
	VELOCITY(double x = 0 , double y = 0 , double z = 0) : m_Vector(x , y , z){}
}VELOCITY;

//�����x
typedef struct ACCELARATION
{
	THREE_DIMENSIONAL_VECTOR m_Vector;	//�����x�x�N�g��

	//�R���X�g���N�^
	ACCELARATION(double x = 0 , double y = 0 , double z = 0) : m_Vector(x , y , z){}
}ACCELARATION;

//�ϒ����_(�K��l4���_�j
typedef struct FOUR_VERTEX
{
	POSITION m_VertexPosition[4];	//���_�̍��W�ʒu
	unsigned int FactorSize;	//�v�f��

	FOUR_VERTEX()
	{
		FactorSize = 4;
	}

	unsigned int size()
	{
		return FactorSize;
	}
}FOUR_VERTEX;