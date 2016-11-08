#include "EnemyManagerClass.h"

//実体化
EnemyManagerClass* cl_EnemyManager;


EnemyManagerClass::EnemyManagerClass(void)
{

}


EnemyManagerClass::~EnemyManagerClass(void)
{
}

//////////////////////////////////////////////////////////////////////////////
//public関数
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//敵生成
//引数:
//	wave_manager:ウェーブマネージャー
//	enemy_type:的タイプ
//	position:敵生成位置
//////////////////////////////////////////////////////////////////////////////
bool EnemyManagerClass::CreateEnemy(WaveManagerClass *wave_manager , int enemy_type , POSITION* position)
{
	EnemyContextClass NewEnemy;	//リストに追加する用の敵
	//敵を初期化する
	NewEnemy.Initiarize(wave_manager , enemy_type , position);
	//リストの末尾に追加する
	m_Enemy.PushBack(NewEnemy);
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//初期化
//////////////////////////////////////////////////////////////////////////////
bool EnemyManagerClass::Initiarize()
{
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//更新
//////////////////////////////////////////////////////////////////////////////
bool EnemyManagerClass::Update(PlayerBulletManagerClass *player_bullet_manager)
{
	//敵リストの最初に移動
	if(m_Enemy.ToBegin())
	{
		//1回は実行する
		do
		{
			//敵リストの現在のノードを更新
			//敵がプレイヤーの弾に当たったら消す
			if(!m_Enemy.GetCurrentNode().Update(player_bullet_manager))
			{
				//敵の開放
				m_Enemy.GetCurrentNode().Release();
				//現在のノードを取り除く
				m_Enemy.RemoveCurrentNode();
			}

			//画面内にいないとき
			else if(!m_Enemy.GetCurrentNode().CheckEnemyIsInScreen())
			{
				//敵を開放
				m_Enemy.GetCurrentNode().Release();
				//現在のノードを取り除く
				m_Enemy.RemoveCurrentNode();
			}
			//次のノードへ
		} while (m_Enemy.Next());
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////////
//描画
//////////////////////////////////////////////////////////////////////////////
void EnemyManagerClass::Render()
{
	//敵リストの最初に移動する
	if(m_Enemy.ToBegin())
	{
		//1回は実行する
		do
		{
			//敵リストの現在のノードを描画する
			m_Enemy.GetCurrentNode().Render();
			//次のノードへ
		} while (m_Enemy.Next());
	}
}