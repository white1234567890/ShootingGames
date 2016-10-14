#include "WaveManagerClass.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "system.h"

//実体化
WaveManagerClass* cl_WaveManager;

//コンストラクタ
WaveManagerClass::WaveManagerClass(void)
{
}

//デストラクタ
WaveManagerClass::~WaveManagerClass(void)
{
}

//////////////////////////////////////////////////////////////////////////////
//private関数
//////////////////////////////////////////////////////////////////////////////

bool WaveManagerClass::CreateWave(EnemyManagerClass *enemy_manager , std::string now_stage , std::string now_wave)
{
	LoadWaveData(enemy_manager , now_stage , now_wave);
	return true;
}

bool WaveManagerClass::LoadWaveData(EnemyManagerClass *enemy_manager , std::string now_stage , std::string now_wave)
{
	std::string NowStageWave = "data/" + now_stage + "/wave/" + now_wave + ".csv"; 

#ifdef DEBUG
	std::cout << NowStageWave << std::endl;
#endif // DEBUG

	std::ifstream ifs(NowStageWave);

	if(ifs.fail()) return false;

#ifdef DEBUG
	std::cout << "Success!" << std::endl;
#endif // DEBUG

	std::string WaveData;
	
	std::getline(ifs , WaveData);

	std::vector<double> TempVector;
	
	while (std::getline(ifs , WaveData))
	{
		std::string token;
		std::istringstream stream(WaveData);
		while(getline(stream , token , ','))
		{
			TempVector.push_back(std::stod(token));
		}

		enemy_manager->CreateEnemy(TempVector[0] , &POSITION(TempVector[1] * WINDOW_WIDTH , TempVector[2] * WINDOW_HEIGHT));

		TempVector.clear();
	}

	ReleaseVector(TempVector);
	
	return true;
}

bool WaveManagerClass::LoadMaxWave()
{
	std::string FileName = "data/" + m_NowStage + "/wave/maxwave.txt"; 

	std::ifstream ifs(FileName);

#ifdef DEBUG
	std::cout << FileName << std::endl;
#endif // DEBUG

	if(ifs.fail()) return false;

#ifdef DEBUG
	std::cout << "Success!" << std::endl;
#endif // DEBUG

	std::string MaxWaveNumber;

	std::getline(ifs , MaxWaveNumber);

	m_MaxWave = std::stoi(MaxWaveNumber);

	return true;
}

//////////////////////////////////////////////////////////////////////////////
//public関数
//////////////////////////////////////////////////////////////////////////////
bool WaveManagerClass::Initiarize(int now_stage)
{
	m_NowStage = "stage" + std::to_string(now_stage);
	m_WaveCounter = 1;
	m_NowWave = "wave" + std::to_string(m_WaveCounter);
	if(!LoadMaxWave()) return false;
	return true;
}

bool WaveManagerClass::Update(EnemyManagerClass *enemy_manager)
{
	if(TimeCount() )
	{
		CreateWave(enemy_manager , m_NowStage , m_NowWave);
	}

	return true;
}