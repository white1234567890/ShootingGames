#pragma once
#include "PlayerClass.h"

class BackPartsClass :
	public BoxClass
{
private:
	PlayerClass *m_Pointer_to_Parent;	//�v���C���[�ւ̃|�C���^
	
	//������(�p��)
	virtual bool Initialize(POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , THREE_DIMENSIONAL_VECTOR* semi_long_vector , THREE_DIMENSIONAL_VECTOR* semi_short_vector , bool flag = true) final {return true ;}
	//�`��(�p��)
	virtual void Render() final{}
	
	//////////////////////////////////////////////////////////////////////////////
	//�w���p�[�c�̃f�[�^�����[�h����
	//����:
	//	���[�h����p�[�c�^�C�v
	//�߂�l:
	//	true:�f�[�^�����[�h����
	//	false:�f�[�^�̃��[�h�Ɏ��s����
	//////////////////////////////////////////////////////////////////////////////
	bool LoadBackPartsData(int back_type);

public:
	BackPartsClass(void);
	~BackPartsClass(void);

	//////////////////////////////////////////////////////////////////////////////
	//�T��:
	//	������
	//����:
	//	back_type:�w���p�[�c�̃^�C�v
	//	local_position:�v���C���[���猩���ʒu
	//	local_velocity:�v���C���[���猩�����x
	//	local_accelaration:�v���C���[���猩�������x
	//	player:�v���C���[�ւ̃|�C���^
	//	flag:�`��t���O
	//�߂�l:
	//	true:����
	//	false:���s
	//////////////////////////////////////////////////////////////////////////////
	bool Initialize(int back_type , POSITION* local_position , VELOCITY* local_velocity , ACCELARATION* local_accelaration , PlayerClass* player , bool flag = true);
	
	//////////////////////////////////////////////////////////////////////////////
	//�T��:
	//	�`��
	//����:
	//	player_world_position:�v���C���[�̈ʒu
	//////////////////////////////////////////////////////////////////////////////
	void Render(POSITION* player_world_position);
};