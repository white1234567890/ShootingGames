#pragma once
#include "CharactorClass.h"
#include "InputClass.h"
class PlayerClass :
	public CharactorClass , public InputClass
{
private:
	void CheckInput();

public:
	PlayerClass(void);
	~PlayerClass(void);

	bool Update();
};

