#pragma once

#include "SingletonClass.h"
#include "TimerClass.h"
#include "EnemyManagerClass.h"

class WaveManagerClass :
	public SingletonClass<WaveManagerClass> , public TimerClass
{
public:
	//フレンドクラス
	friend class SingletonClass<WaveManagerClass>;

private:
	std::string m_NowStage;
	std::string m_NowWave;
	int m_WaveCounter;
	int m_MaxWave;

	bool CreateWave(EnemyManagerClass *enemy_manager , std::string now_stage , std::string now_wave);
	bool LoadWaveData(EnemyManagerClass *enemy_manager , std::string now_stage , std::string now_wave);
	bool LoadMaxWave();

protected:
	WaveManagerClass(void);
	virtual ~WaveManagerClass(void);

public:
	
	//ステージ番号
	enum STAGE_NUMBER
	{
		E_STAGE1 = 1,
		E_STAGE2,
		E_STAGE3,
		E_STAGE4,
		E_STAGE5,
		E_STAGE6
	};

	std::string GetNowStage();

	bool Initiarize(int now_stage);
	bool Update(EnemyManagerClass *enemy_manager);
};

extern WaveManagerClass* cl_WaveManager;
