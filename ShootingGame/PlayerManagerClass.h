#pragma once
#include "SingletonClass.h"

#include "PlayerManagerClass.h"
#include "PlayerClass.h"
#include "ShoulderPartsClass.h"
#include "BackPartsClass.h"
#include "HipPartsClass.h"

class PlayerManagerClass :
	public SingletonClass<PlayerManagerClass>
{
public:
	friend class SingletonClass<PlayerManagerClass>;

private:
	PlayerClass m_Player;
	ShoulderPartsClass m_Shoulder_L;
	ShoulderPartsClass m_Shoulder_R;
	BackPartsClass m_Back;
	HipPartsClass m_Hip;

public:
	PlayerManagerClass(void);
	~PlayerManagerClass(void);

	POSITION GetPlayerPosition();
	void WhenReshaped();

	bool Initialize();
	bool Update();
	void Render();
};

extern PlayerManagerClass* cl_PlayerManager;