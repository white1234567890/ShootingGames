#include "HipPartsClass.h"

#include <gl\glew.h>
#include <gl\glut.h>

#include <fstream>
#include <sstream>

#include "system.h"
HipPartsClass::HipPartsClass(void)
{
}


HipPartsClass::~HipPartsClass(void)
{
}

//////////////////////////////////////////////////////////////////////////////
//private�֐�
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//���p�[�c�̃f�[�^�����[�h����
//����:
//	���[�h����p�[�c�^�C�v
//�߂�l:
//	true:�f�[�^�����[�h����
//	false:�f�[�^�̃��[�h�Ɏ��s����
//////////////////////////////////////////////////////////////////////////////
bool HipPartsClass::LoadHipPartsData(int hip_type)
{
	//�t�@�C����ǂݍ���
	std::ifstream ifs("data/player/HipPartsParameter.csv");

	//���s������false��Ԃ�
	if(ifs.fail()) return false;

	//�f�[�^��ǂݍ��ނ��߂̕�����
	std::string HipPartsParameters;

	//�ŏ���1�s�͖�������
	std::getline(ifs , HipPartsParameters);

	//�����o�������p�[�c���܂ōs��
	for(int i = 0 ; i <= hip_type ; i++)
	{
		std::getline(ifs , HipPartsParameters);
	}

	std::string token;	//�f�[�^���o���p�̃g�[�N��
	std::istringstream stream(HipPartsParameters);	//�f�[�^�����ǂݍ��ޕ�����
	std::vector<double> TempVector;	//�f�[�^�ϊ��p�z��
	
	//','�����邽�тɃg�[�N���ɕ���������o��
	while(getline(stream , token , ','))
	{
		//�g�[�N���̕�����𐔎��ɕϊ�����
		TempVector.push_back(std::stod(token));
	}

	//�����̐ݒ�
	SPEED_X_ASPECT = TempVector[1];
	SPEED_Y_ASPECT = TempVector[2];

	//�摜�̉��̕����傫���Ƃ�
	if(TempVector[2] >= TempVector[3])
	{
		m_SemiLongVector = THREE_DIMENSIONAL_VECTOR(TempVector[3]);
		m_SemiShortVector = THREE_DIMENSIONAL_VECTOR(0 , TempVector[4]);
	}
	//�摜�̏c�̕����傫���Ƃ�
	else
	{
		m_SemiLongVector = THREE_DIMENSIONAL_VECTOR(0 , TempVector[4]);
		m_SemiShortVector = THREE_DIMENSIONAL_VECTOR(TempVector[3]);
	}

	m_SemiLongAxis = m_SemiLongVector.Magnitude();
	m_SemiShortAxis = m_SemiShortVector.Magnitude();

	SetVertex();

	
	//����Ȃ�vector���J������
	ReleaseVector(TempVector);
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//public�֐�
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	������
//����:
//	hip_type:�������鍘�p�[�c�̃^�C�v
//	local_position:�v���C���[���猩���ʒu
//	local_velocity:�v���C���[���猩�����x
//	local_accelaration:�v���C���[���猩�������x
//	player:�v���C���[�ւ̃|�C���^
//	flag:�`��t���O
//�߂�l:
//	true:����
//	false:���s
//////////////////////////////////////////////////////////////////////////////
bool HipPartsClass::Initialize(int hip_type , POSITION* local_position , VELOCITY* local_velocity , ACCELARATION* local_accelaration , PlayerClass* player , bool flag)
{
	m_Position = *local_position;
	m_Velocity = *local_velocity;
	m_Accelaration = *local_accelaration;

	m_Pointer_to_Parent = player;

	if(!LoadHipPartsData(hip_type)) return false;

	return true;
}

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	�`��
//����:
//	player_world_position:�v���C���[�̈ʒu
//////////////////////////////////////////////////////////////////////////////
void HipPartsClass::Render(POSITION* player_world_positoin)
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

