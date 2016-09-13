#pragma once
#include "BulletClass.h"

class ShoulderPartsClass;

class BulletManagerClass
{
protected:
	BulletClass m_BulletClass;

public:
	BulletManagerClass(void);
	~BulletManagerClass(void);

	bool Initiarize();
	virtual bool Update() = 0;
	void Render();

	void CreateBullet();
	void PushBackList();
};