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
	if(m_Bullet.ToBegin()) return;

	while (true)
	{
		m_Bullet.GetCurrentNode().Render();

		if(!m_Bullet.Next())
		{
			m_Bullet.GetCurrentNode().Render();
			return;
		}
	}
}

void BulletManagerClass::CreateBullet()
{
	//AddList->Initialize(&m_Pointer_to_Parent->GetShotPosition() , &m_Pointer_to_Parent->GetShotVelocity() , &m_Pointer_to_Parent->GetShotAccelaration() , &m_Pointer_to_Parent->GetShotSemiLongVector() , &m_Pointer_to_Parent->GetShotSemiShortVector());
}