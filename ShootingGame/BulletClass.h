#pragma once
#include "boxclass.h"
#include "ListClass.h"

class BulletClass :
	public BoxClass
{
public:

	BulletClass(void);
	~BulletClass(void);

	void Render();
};