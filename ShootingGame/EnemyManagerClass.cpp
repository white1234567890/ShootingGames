#include "EnemyManagerClass.h"

//ŽÀ‘Ì‰»
EnemyManagerClass* cl_EnemyManager;


EnemyManagerClass::EnemyManagerClass(void)
{

}


EnemyManagerClass::~EnemyManagerClass(void)
{
}

bool EnemyManagerClass::CreateEnemy(WaveManagerClass *wave_manager , int enemy_type , POSITION* position)
{
	EnemyClass NewEnemy;
	NewEnemy.Initiarize(wave_manager , enemy_type , position);
	m_Enemy.PushBack(NewEnemy);
	return true;
}

bool EnemyManagerClass::Initiarize()
{
	return true;
}

bool EnemyManagerClass::Update()
{
	if(m_Enemy.ToBegin())
	{
		do
		{
			m_Enemy.GetCurrentNode().Update();
			if(!m_Enemy.GetCurrentNode().CheckEnemyIsInScreen())
			{
				m_Enemy.GetCurrentNode().Release();
				m_Enemy.RemoveCurrentNode();
			}
		} while (m_Enemy.Next());
	}

	return true;
}

void EnemyManagerClass::Render()
{
	if(m_Enemy.ToBegin())
	{
		do
		{
			m_Enemy.GetCurrentNode().Render();
		} while (m_Enemy.Next());
	}
}