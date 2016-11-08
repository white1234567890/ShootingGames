#include "PlayerBulletManagerClass.h"

//実体化
PlayerBulletManagerClass* cl_PlayerBulletManager;

//コンストラクタ
PlayerBulletManagerClass::PlayerBulletManagerClass(void)
{
}

//デストラクタ
PlayerBulletManagerClass::~PlayerBulletManagerClass(void)
{
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	弾を作る
//引数:
//	*position:発生位置
//	*velocity:移動速度
//	*accelaration:移動加速度
//	*semi_long_vector:半長軸ベクトル
//	*semi_short_vector:半短軸ベクトル
//////////////////////////////////////////////////////////////////////////////
void PlayerBulletManagerClass::CreateBullet(POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , THREE_DIMENSIONAL_VECTOR* semi_long_vector , THREE_DIMENSIONAL_VECTOR* semi_short_vector)
{
	BulletClass NewBullet;
	NewBullet.Initialize(position , velocity , accelaration , semi_long_vector , semi_short_vector);
	m_Bullet.PushBack(NewBullet);
}

//////////////////////////////////////////////////////////////////////////////
//更新
//////////////////////////////////////////////////////////////////////////////
bool PlayerBulletManagerClass::Update()
{
	//弾リストの先頭へ移動する
	if(m_Bullet.ToBegin())
	{
		//1度は実行する
		do
		{
			//現在のノードを更新する
			m_Bullet.GetCurrentNode().Update();
			//画面内にいないとき
			if(m_Bullet.GetCurrentNode().GetPosition().m_Vector.x < 0 || m_Bullet.GetCurrentNode().GetPosition().m_Vector.x > WINDOW_WIDTH ||
				m_Bullet.GetCurrentNode().GetPosition().m_Vector.y < 0 || m_Bullet.GetCurrentNode().GetPosition().m_Vector.y > WINDOW_HEIGHT)
			{
				//現在のノードを取り除く
				m_Bullet.RemoveCurrentNode();
			}
			//次のノードへ
		} while (m_Bullet.Next());

	}

	return false;
}