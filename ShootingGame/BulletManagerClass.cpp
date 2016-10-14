#include "BulletManagerClass.h"
#include "ShoulderPartsClass.h"


BulletManagerClass::BulletManagerClass(void)
{
}


BulletManagerClass::~BulletManagerClass(void)
{
}

bool BulletManagerClass::Initiarize()
{
	return true;
}

bool BulletManagerClass::Update()
{
	return true;
}

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

void BulletManagerClass::CreateBullet()
{
}