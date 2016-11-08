#pragma once
#include "bulletmanagerclass.h"
#include "SingletonClass.h"

class EnemyBulletManagerClass :
	public BulletManagerClass , public SingletonClass<EnemyBulletManagerClass>
{
public:
	friend class SingletonClass<EnemyBulletManagerClass>;

protected:
	EnemyBulletManagerClass(void);
	~EnemyBulletManagerClass(void);

	//弾を生成（継承）
	void CreateBullet() final{};

public:
	//////////////////////////////////////////////////////////////////////////////
	//弾を生成
	//引数:
	//	position:生成位置
	//	velocity:弾の速度
	//	accelaration:弾の加速度
	//	semi_long_vector:弾画像の大きさ（半長軸ベクトル）
	//	semi_short_vector:弾画像の大きさ（半短軸ベクトル）
	//////////////////////////////////////////////////////////////////////////////
	void CreateBullet(POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , THREE_DIMENSIONAL_VECTOR* semi_long_vector , THREE_DIMENSIONAL_VECTOR* semi_short_vector);

	//////////////////////////////////////////////////////////////////////////////
	//更新
	//////////////////////////////////////////////////////////////////////////////
	bool Update();
};

