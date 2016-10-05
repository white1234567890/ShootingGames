#pragma once
#include "boxclass.h"

class BulletClass :
	public BoxClass
{
public:

	BulletClass(void);
	~BulletClass(void);

	void Render();
};