#pragma once
#include "BulletClass.h"
#include "ListClass.h"

class BulletManagerClass
{
protected:
	ListClass<BulletClass> m_Bullet;

public:
	BulletManagerClass(void);
	~BulletManagerClass(void);

	bool Initiarize();
	virtual bool Update() = 0;
	void Render();

	virtual void CreateBullet() = 0;
};