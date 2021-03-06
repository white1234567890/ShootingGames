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
	
	//////////////////////////////////////////////////////////////////////////////
	//概略:
	//	弾を作る
	//引数:
	//	*position:発生位置
	//	*velocity:移動速度
	//	*accelaration:移動加速度
	//	*semi_long_vector:半長軸ベクトル
	//	*semi_short_vector:半短軸ベクトル
	//////////////////////////////////////////////////////////////////////////////
	void CreateBullet(POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , THREE_DIMENSIONAL_VECTOR* semi_long_vector , THREE_DIMENSIONAL_VECTOR* semi_short_vector);

	//////////////////////////////////////////////////////////////////////////////
	//更新
	//////////////////////////////////////////////////////////////////////////////
	bool Update();
};

extern PlayerBulletManagerClass* cl_PlayerBulletManager;