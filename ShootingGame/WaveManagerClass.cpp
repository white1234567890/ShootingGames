#include "WaveManagerClass.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "system.h"

//���̉�
WaveManagerClass* cl_WaveManager;

//�R���X�g���N�^
WaveManagerClass::WaveManagerClass(void)
{
}

//�f�X�g���N�^
WaveManagerClass::~WaveManagerClass(void)
{
}

//////////////////////////////////////////////////////////////////////////////
//private�֐�
//////////////////////////////////////////////////////////////////////////////

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
bool WaveManagerClass::CreateWave(EnemyManagerClass *enemy_manager , std::string now_stage , std::string now_wave)
{
	//�E�F�[�u�f�[�^�����[�h
	if(!LoadWaveData(enemy_manager , now_stage , now_wave)) return false;
	//���̃E�F�[�u�̏���
	m_WaveCounter++;
	return true;
}

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
bool WaveManagerClass::LoadWaveData(EnemyManagerClass *enemy_manager , std::string now_stage , std::string now_wave)
{
	//�ǂݍ��ރt�@�C�������w��
	std::string NowStageWave = "data/" + now_stage + "/wave/" + now_wave + ".csv"; 

#ifdef DEBUG
	std::cout << NowStageWave << std::endl;
#endif // DEBUG

	//�t�@�C�����I�[�v��
	std::ifstream ifs(NowStageWave);

	//�J���Ȃ�������false
	if(ifs.fail()) return false;

#ifdef DEBUG
	std::cout << "Success!" << std::endl;
#endif // DEBUG

	std::string WaveData;	//�ǂݍ��ރf�[�^
	
	//�ŏ���1�s�͖�������
	std::getline(ifs , WaveData);

	std::vector<double> TempVector;	//�ϊ��f�[�^
	
	//1�s���ǂݍ���
	while (std::getline(ifs , WaveData))
	{
		std::string token;	//�f�[�^���o��
		std::istringstream stream(WaveData);	//�f�[�^�ǂݍ���

		//','�����邽�тɃf�[�^�����o��
		while(getline(stream , token , ','))
		{
			//�������琔�l�֕ϊ�
			TempVector.push_back(std::stod(token));
		}

		//���o�����f�[�^����G�𐶐�
		enemy_manager->CreateEnemy(this , (int)TempVector[0] , &POSITION(TempVector[1] * WINDOW_WIDTH , TempVector[2] * WINDOW_HEIGHT));

		//�ϊ��z�������
		TempVector.clear();
	}

	//�ϊ��z����J��
	ReleaseVector(TempVector);
	
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//�E�F�[�u�̍ő�l�����[�h
//////////////////////////////////////////////////////////////////////////////
bool WaveManagerClass::LoadMaxWave()
{
	//�ǂݍ��ރt�@�C�������w��
	std::string FileName = "data/" + m_NowStage + "/wave/maxwave.txt"; 

	//�t�@�C�����I�[�v��
	std::ifstream ifs(FileName);

#ifdef DEBUG
	std::cout << FileName << std::endl;
#endif // DEBUG

	//�J���Ȃ�������false
	if(ifs.fail()) return false;

#ifdef DEBUG
	std::cout << "Success!" << std::endl;
#endif // DEBUG

	std::string MaxWaveNumber;	//�f�[�^�ǂݍ���

	//�f�[�^�����o��
	std::getline(ifs , MaxWaveNumber);

	//�����𐔒l�ɕϊ�
	m_MaxWave = std::stoi(MaxWaveNumber);

	return true;
}

//////////////////////////////////////////////////////////////////////////////
//public�֐�
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//���̃X�e�[�W�𒲂ׂ�
//�߂�l:
//	���̃X�e�[�W
//////////////////////////////////////////////////////////////////////////////
std::string WaveManagerClass::GetNowStage()
{
	return m_NowStage;
}

//////////////////////////////////////////////////////////////////////////////
//������
//����:
//	now_stage:���̃X�e�[�W�ԍ�
//�߂�l:
//	true:����
//	false:�f�[�^�̃��[�h�Ɏ��s
//////////////////////////////////////////////////////////////////////////////
bool WaveManagerClass::Initiarize(int now_stage)
{
	//���̃X�e�[�W�𕶎���Ƃ��ċL��
	m_NowStage = "stage" + std::to_string(now_stage);

	//�E�F�[�u�ԍ���0��
	m_WaveCounter = 0;

	//�E�F�[�u�̍ő�l���擾
	if(!LoadMaxWave()) return false;
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//�X�V
//����:
//	enemy_manager:�G�l�~�[�}�l�[�W���[
//����:
//	true:�X�V����
//////////////////////////////////////////////////////////////////////////////
bool WaveManagerClass::Update(EnemyManagerClass *enemy_manager)
{
	//30�b���ƂɃE�F�[�u����
	if(GetCounter() == 1800 * m_WaveCounter && m_WaveCounter < m_MaxWave)
	{
		//�E�F�[�u�ԍ��𕶎���Ƃ��ċL��
		m_NowWave = "wave" + std::to_string(m_WaveCounter + 1);

		//�E�F�[�u����
		CreateWave(enemy_manager , m_NowStage , m_NowWave);
	}

	//���Ԃ��J�E���g
	TimeCount();

	return true;
}