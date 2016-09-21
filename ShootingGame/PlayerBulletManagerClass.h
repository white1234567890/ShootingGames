#pragma once
#include "bulletmanagerclass.h"
#include "SingletonClass.h"

class PlayerBulletManagerClass :
	public BulletManagerClass , public SingletonClass<PlayerBulletManagerClass>
{
public:
	friend class SingletonClass<PlayerBulletManagerClass>;

protected:
	PlayerBulletManagerClass(void);
	~PlayerBulletManagerClass(void);
	void CreateBullet() final {};

public:
	void CreateBullet(POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , THREE_DIMENSION_VECTOR* semi_long_vector , THREE_DIMENSION_VECTOR* semi_short_vector);
	bool Update();
};

extern PlayerBulletManagerClass* cl_PlayerBulletManager;