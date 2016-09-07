#pragma once

#define SCREEN_HEIGHT_ASPECT 3	//��ʏc��
#define SCREEN_WIDTH_ASPECT 4	//��ʉ���
#define SCREEN_SIZE 200				//��ʃT�C�Y
#include "DebugSwitch.h"

#include <vector>

//�萔�̐錾
const int WINDOW_SIZE_HEIGHT = SCREEN_SIZE * SCREEN_HEIGHT_ASPECT;	//��ʃT�C�Y�c
const int WINDOW_SIZE_WIDTH = SCREEN_SIZE * SCREEN_WIDTH_ASPECT;		//��ʃT�C�Y��
const int SCREEN_HEIGHT = WINDOW_SIZE_HEIGHT;									//�Q�[����ʃT�C�Y�c
const int SCREEN_WIDTH = WINDOW_SIZE_WIDTH / 3 * 2;								//�Q�[����ʃT�C�Y��
const int SCREEN_OVER_LEFT = -100;														//��ʊO��`
const int SCREEN_OVER_RIGHT = SCREEN_WIDTH + 100;								//��ʊO��`
const int SCREEN_OVER_UP = - 100;														//��ʊO��`
const int SCREEN_OVER_DOWN = SCREEN_HEIGHT + 100;								//��ʊO��`
const int maxdot = 1;																			//�o��������h�b�g�̍ő吔
const int MAX_DROP_SPEED = 20;															//�������x�ő�l
const double PLAYER_SPEED = 5;															//�v���C���[�̑���

//�ÓI�ϐ��̐錾

static int WINDOW_HEIGHT = 600;	//�E�B���h�E�T�C�Y�c
static int WINDOW_WIDTH = 800;	//�E�B���h�E�T�C�Y��

//�񋓑̂̐錾
enum GAME_MODE
{
	GAME_INIT,	//�Q�[��������
	GAME_PLAY,	//�Q�[�����C��
	END = 99		//�I��
};

//3�����x�N�g��
typedef struct THREE_DIMENSION_VECTOR
{
	double x;	//x���W
	double y;	//y���W
	double z;	//z���W

	//�R���X�g���N�^
	THREE_DIMENSION_VECTOR(double x = 0 , double y = 0 , double z = 0)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	//�x�N�g���̑����Z
	THREE_DIMENSION_VECTOR operator + (THREE_DIMENSION_VECTOR obj)
	{
		THREE_DIMENSION_VECTOR ret;
		ret.x = this->x + obj.x;
		ret.y = this->y + obj.y;
		ret.z = this->z + obj.z;
		return ret;
	}

	//�x�N�g���̑����Z
	void operator += (THREE_DIMENSION_VECTOR obj)
	{
		this->x = this->x + obj.x;
		this->y = this->y + obj.y;
		this->z = this->z + obj.z;
	}

	//�x�N�g���̈����Z
	THREE_DIMENSION_VECTOR operator - (THREE_DIMENSION_VECTOR obj)
	{
		THREE_DIMENSION_VECTOR ret;
		ret.x = this->x - obj.x;
		ret.y = this->y - obj.y;
		ret.z = this->z - obj.z;
		return ret;
	}

	//�x�N�g���̈����Z
	void operator -= (THREE_DIMENSION_VECTOR obj)
	{
		this->x = this->x - obj.x;
		this->y = this->y - obj.y;
		this->z = this->z - obj.z;
	}

	//�t�x�N�g��
	THREE_DIMENSION_VECTOR operator - ()
	{
		THREE_DIMENSION_VECTOR ret;
		ret.x = -this->x;
		ret.y = -this->y;
		ret.z = -this->z;
		return ret;
	}

	//�X�J���[�{
	THREE_DIMENSION_VECTOR operator * (double obj)
	{
		THREE_DIMENSION_VECTOR ret;
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
	THREE_DIMENSION_VECTOR GetNomalVector()
	{
		THREE_DIMENSION_VECTOR ret;
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
}THREE_DIMENSION_VECTOR;

//�ʒu
typedef struct POSITION
{
	THREE_DIMENSION_VECTOR m_Vector;	//�ʒu�x�N�g��
		
	//�R���X�g���N�^
	POSITION(double x = 0 , double y = 0 , double z = 0) : m_Vector(x , y , z){}
}POSITION;

//���x
typedef struct VELOCITY
{
	THREE_DIMENSION_VECTOR m_Vector;	//���x�x�N�g��

	//�R���X�g���N�^
	VELOCITY(double x = 0 , double y = 0 , double z = 0) : m_Vector(x , y , z){}
}VELOCITY;

//�����x
typedef struct ACCELARATION
{
	THREE_DIMENSION_VECTOR m_Vector;	//�����x�x�N�g��

	//�R���X�g���N�^
	ACCELARATION(double x = 0 , double y = 0 , double z = 0) : m_Vector(x , y , z){}
}ACCELARATION;

//�ϒ����_(�K��l4���_�j
typedef struct VARIABLE_VERTEX
{
	POSITION* m_VertexPosition;	//���_�̍��W�ʒu
	unsigned int FactorSize;	//�v�f��

	VARIABLE_VERTEX()
	{
		this->m_VertexPosition = new POSITION[4];
		FactorSize = 4;
	}

	~VARIABLE_VERTEX()
	{
		delete[] this->m_VertexPosition;
	}

	unsigned int size()
	{
		return FactorSize;
	}
}VARIABLE_VERTEX;


//�ϐ��̐錾
extern GAME_MODE GameMode;		//�Q�[�����[�h�w��p�ϐ�