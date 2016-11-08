#pragma once
#include "BulletClass.h"
#include "ListClass.h"

class BulletManagerClass
{
public:
	//EnemyClass����̃A�N�Z�X��������
	friend class EnemyStatePatternClass;

protected:
	ListClass<BulletClass> m_Bullet;	//�e�̃��X�g

public:
	BulletManagerClass(void);
	~BulletManagerClass(void);

	//////////////////////////////////////////////////////////////////////////////
	//�T��:
	//	������
	//////////////////////////////////////////////////////////////////////////////
	bool Initiarize();
	
	//�X�V�i�������z�֐��j
	virtual bool Update() = 0;
	
	//////////////////////////////////////////////////////////////////////////////
	//�T��:
	//	�`��
	//////////////////////////////////////////////////////////////////////////////
	void Render();

	//�e�����i�������z�֐��j
	virtual void CreateBullet() = 0;
};