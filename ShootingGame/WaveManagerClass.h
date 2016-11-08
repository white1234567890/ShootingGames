#pragma once

#include "SingletonClass.h"
#include "TimerClass.h"
#include "EnemyManagerClass.h"

class WaveManagerClass :
	public SingletonClass<WaveManagerClass> , public TimerClass
{
public:
	//�t�����h�N���X
	friend class SingletonClass<WaveManagerClass>;

private:
	std::string m_NowStage;	//���̃X�e�[�W
	std::string m_NowWave;	//���̃E�F�[�u
	int m_WaveCounter;	//�E�F�[�u�̃J�E���g
	int m_MaxWave;	//���̃X�e�[�W�̍ő�E�F�[�u��

	//////////////////////////////////////////////////////////////////////////////
	//�E�F�[�u����
	//����:
	//	enemy_manager:�G�l�~�[�}�l�[�W���[
	//	now_stage:���̃X�e�[�W
	//	noe_wave:���̃E�F�[�u
	//�߂�l:
	//	true:��������
	//	false:�������s
	//////////////////////////////////////////////////////////////////////////////
	bool CreateWave(EnemyManagerClass *enemy_manager , std::string now_stage , std::string now_wave);

	//////////////////////////////////////////////////////////////////////////////
	//�E�F�[�u�f�[�^�̃��[�h
	//����:
	//	enemy_manager:�G�l�~�[�}�l�[�W���[
	//	now_stage:���̃X�e�[�W
	//	noe_wave:���̃E�F�[�u
	//�߂�l:
	//	true:��������
	//	false:�������s
	//////////////////////////////////////////////////////////////////////////////
	bool LoadWaveData(EnemyManagerClass *enemy_manager , std::string now_stage , std::string now_wave);

	//////////////////////////////////////////////////////////////////////////////
	//�E�F�[�u�̍ő�l�����[�h
	//////////////////////////////////////////////////////////////////////////////
	bool LoadMaxWave();

protected:
	WaveManagerClass(void);
	virtual ~WaveManagerClass(void);

public:
	
	//�X�e�[�W�ԍ�
	enum STAGE_NUMBER
	{
		E_STAGE1 = 1,	//�X�e�[�W1
		E_STAGE2,	//�X�e�[�W2
		E_STAGE3,	//�X�e�[�W3
		E_STAGE4,	//�X�e�[�W4
		E_STAGE5,	//�X�e�[�W5
		E_STAGE6	//�X�e�[�W6
	};

	//////////////////////////////////////////////////////////////////////////////
	//���̃X�e�[�W�𒲂ׂ�
	//�߂�l:
	//	���̃X�e�[�W
	//////////////////////////////////////////////////////////////////////////////
	std::string GetNowStage();

	//////////////////////////////////////////////////////////////////////////////
	//������
	//����:
	//	now_stage:���̃X�e�[�W�ԍ�
	//�߂�l:
	//	true:����
	//	false:�f�[�^�̃��[�h�Ɏ��s
	//////////////////////////////////////////////////////////////////////////////
	bool Initiarize(int now_stage);

	//////////////////////////////////////////////////////////////////////////////
	//�X�V
	//����:
	//	enemy_manager:�G�l�~�[�}�l�[�W���[
	//����:
	//	true:�X�V����
	//////////////////////////////////////////////////////////////////////////////
	bool Update(EnemyManagerClass *enemy_manager);
};

extern WaveManagerClass* cl_WaveManager;
