#pragma once
#include "SingletonClass.h"
#include "ListClass.h"
#include "EnemyClass.h"

//使用クラス宣言
class WaveManagerClass;

class EnemyManagerClass :
	public SingletonClass<EnemyManagerClass>
{
public:
	friend class SingletonClass<EnemyManagerClass>;	//シングルトンからのインスタンス生成を許可する

private:
	ListClass<EnemyClass> m_Enemy;

	EnemyManagerClass(void);
	~EnemyManagerClass(void);

public:
	enum ENEMY_TYPE
	{
		E_ENEMY_TYPE_1,
		E_ENEMY_TYPE_2
	};

	bool CreateEnemy(WaveManagerClass *wave_manager , int enemy_type , POSITION* position);

	bool Initiarize();
	bool Update();
	void Render();
};

extern EnemyManagerClass* cl_EnemyManager;