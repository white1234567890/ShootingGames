#pragma once
#include "PlayerClass.h"
#include "BulletManagerClass.h"

class ShoulderPartsClass :
	public BoxClass
{
private:
	THREE_DIMENSIONAL_VECTOR m_ForwardVector;	//�O���x�N�g��

	int m_ShotType;	//�V���b�g�^�C�v
	POSITION m_ShotPosition;	//�V���b�g�̈ʒu
	double m_BarrelRange;	//�V���b�g�̏����ʒu������o�����߂̒���
	VELOCITY m_ShotVelocity;	//�V���b�g�̏���
	ACCELARATION m_ShotAccelaration;	//�V���b�g�̉����x
	THREE_DIMENSIONAL_VECTOR m_ShotSemiLongVector;	//�V���b�g�̉摜�̔�������
	THREE_DIMENSIONAL_VECTOR m_ShotSemiShortVector;	//�V���b�g�̉摜�̔��Z����
	double m_ShotSpeed;	//�V���b�g�̑���

	PlayerClass *m_Pointer_to_Parent;	//�v���C���[�ւ̃|�C���^

	//�������i�p���j
	virtual bool Initialize(POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , THREE_DIMENSIONAL_VECTOR* semi_long_vector , THREE_DIMENSIONAL_VECTOR* semi_short_vector , bool flag = true) final {return true ;}
	
	//�X�V�i�p���j
	virtual bool Update() final{return true;}
	
	//�`��i�p���j
	virtual void Render() final{}

	//////////////////////////////////////////////////////////////////////////////
	//���p�[�c�̃f�[�^�����[�h����
	//����:
	//	shoulder_type:���[�h����p�[�c�^�C�v
	//�߂�l:
	//	true:�f�[�^�����[�h����
	//	false:�f�[�^�̃��[�h�Ɏ��s����
	//////////////////////////////////////////////////////////////////////////////
	bool LoadShoulderPartsData(int shoulder_type);
	
	//////////////////////////////////////////////////////////////////////////////
	//�T��:
	//	�V���b�g�̃p�����[�^��ݒ肷��
	//����:
	//	int shot_type:�V���b�g�̃^�C�v
	//	barrel_range:�����ʒu�����肷�邽�߂̒���
	//	velocity:�V���b�g�̏���
	//	shot_speed:�V���b�g�̑���
	//	accelaration:�V���b�g�̉����x
	//	shot_semi_long_vector:�V���b�g�̉摜�̔������x�N�g��
	//	shot_semishort_vector:�V���b�g�̉摜�̔��Z���x�N�g��
	//////////////////////////////////////////////////////////////////////////////
	void SetShotStatus(int shot_type , double barrel_range , VELOCITY* velocity , double shot_speed , ACCELARATION* accelaration , THREE_DIMENSIONAL_VECTOR* shot_semi_long_vector , THREE_DIMENSIONAL_VECTOR* shot_semi_short_vector);

public:

	ShoulderPartsClass(void);
	~ShoulderPartsClass(void);


	//�Q�b�^�i�ʒu�j
	POSITION GetShotPosition();
	
	//�Q�b�^�i���x�j
	VELOCITY GetShotVelocity();
	
	//�Q�b�^�i�����x�j
	ACCELARATION GetShotAccelaration();
	
	//�Q�b�^�i�������x�N�g���j
	THREE_DIMENSIONAL_VECTOR GetShotSemiLongVector();
	
	//�Q�b�^�i���Z���x�N�g���j
	THREE_DIMENSIONAL_VECTOR GetShotSemiShortVector();
	
	//////////////////////////////////////////////////////////////////////////////
	//�T��:
	//	������
	//����:
	//	shoulder_type:���p�[�c�^�C�v
	//	local_position:�v���C���[���猩���ʒu
	//	local_velocity:�v���C���[���猩�����x
	//	local_accelaration:�v���C���[���猩�������x
	//	player:�v���C���[�ւ̃|�C���^
	//	flag:�`��t���O
	//�߂�l:
	//	true:����
	//	false:���s
	//////////////////////////////////////////////////////////////////////////////
	bool Initialize(int shoulder_type , POSITION* local_position , VELOCITY* local_velocity , ACCELARATION* local_accelaration , PlayerClass* player , bool flag = true);
	
	//////////////////////////////////////////////////////////////////////////////
	//�T��:
	//	�X�V
	//����:
	//	shot_flag:�V���b�g�����������Ȃ����̃t���O
	//////////////////////////////////////////////////////////////////////////////
	bool Update(bool shot_flag);

	//////////////////////////////////////////////////////////////////////////////
	//�T��:
	//	�`��
	//����:
	//	player_world_position:�v���C���[�̈ʒu
	//////////////////////////////////////////////////////////////////////////////
	void Render(POSITION* player_world_positoin);
};