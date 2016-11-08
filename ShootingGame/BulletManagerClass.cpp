#include "BulletManagerClass.h"
#include "ShoulderPartsClass.h"


BulletManagerClass::BulletManagerClass(void)
{
}


BulletManagerClass::~BulletManagerClass(void)
{
}

/////////////////////////////////////////////////////////////////////////////
//概略:
//	初期化
//////////////////////////////////////////////////////////////////////////////
bool BulletManagerClass::Initiarize()
{
	return true;
}

//更新（純粋仮想関数）
bool BulletManagerClass::Update()
{
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	描画
//////////////////////////////////////////////////////////////////////////////
void BulletManagerClass::Render()
{
	if(m_Bullet.ToBegin())
	{
		do
		{
			m_Bullet.GetCurrentNode().Render();
		} while (m_Bullet.Next());
	}
}

//弾を作る（純粋仮想関数）
void BulletManagerClass::CreateBullet()
{
}