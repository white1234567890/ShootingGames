#include "EnemyBulletManagerClass.h"


EnemyBulletManagerClass::EnemyBulletManagerClass(void)
{
}


EnemyBulletManagerClass::~EnemyBulletManagerClass(void)
{
}

//////////////////////////////////////////////////////////////////////////////
//public関数
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//弾を生成
//引数:
//	position:生成位置
//	velocity:弾の速度
//	accelaration:弾の加速度
//	semi_long_vector:弾画像の大きさ（半長軸ベクトル）
//	semi_short_vector:弾画像の大きさ（半短軸ベクトル）
//////////////////////////////////////////////////////////////////////////////
void EnemyBulletManagerClass::CreateBullet(POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , THREE_DIMENSIONAL_VECTOR* semi_long_vector , THREE_DIMENSIONAL_VECTOR* semi_short_vector)
{
	BulletClass NewBullet;
	NewBullet.Initialize(position , velocity , accelaration , semi_long_vector , semi_short_vector);
	m_Bullet.PushBack(NewBullet);
}

//////////////////////////////////////////////////////////////////////////////
//更新
//////////////////////////////////////////////////////////////////////////////
bool EnemyBulletManagerClass::Update()
{
	return true;
}