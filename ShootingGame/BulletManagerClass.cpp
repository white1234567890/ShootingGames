#include "BulletManagerClass.h"
#include "ShoulderPartsClass.h"


BulletManagerClass::BulletManagerClass(void)
{
}


BulletManagerClass::~BulletManagerClass(void)
{
}

/////////////////////////////////////////////////////////////////////////////
//�T��:
//	������
//////////////////////////////////////////////////////////////////////////////
bool BulletManagerClass::Initiarize()
{
	return true;
}

//�X�V�i�������z�֐��j
bool BulletManagerClass::Update()
{
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	�`��
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

//�e�����i�������z�֐��j
void BulletManagerClass::CreateBullet()
{
}