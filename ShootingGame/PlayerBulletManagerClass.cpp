#include "PlayerBulletManagerClass.h"

//ŽÀ‘Ì‰»
PlayerBulletManagerClass* cl_PlayerBulletManager;

PlayerBulletManagerClass::PlayerBulletManagerClass(void)
{
}


PlayerBulletManagerClass::~PlayerBulletManagerClass(void)
{
}

void PlayerBulletManagerClass::CreateBullet(POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , THREE_DIMENSION_VECTOR* semi_long_vector , THREE_DIMENSION_VECTOR* semi_short_vector)
{
	BulletClass NewBullet;
	NewBullet.Initialize(position , velocity , accelaration , semi_long_vector , semi_short_vector);
	m_Bullet.Add(NewBullet);
}

bool PlayerBulletManagerClass::Update()
{
	if(m_Bullet.ToBegin())
	{
		while (true)
		{
			m_Bullet.GetCurrentNode().Update();
			if(!m_Bullet.Next())
			{
				m_Bullet.GetCurrentNode().Update();
				return true;
			}
		}
	}

	return false;
}