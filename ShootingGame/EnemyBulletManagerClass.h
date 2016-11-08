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

	//�e�𐶐��i�p���j
	void CreateBullet() final{};

public:
	//////////////////////////////////////////////////////////////////////////////
	//�e�𐶐�
	//����:
	//	position:�����ʒu
	//	velocity:�e�̑��x
	//	accelaration:�e�̉����x
	//	semi_long_vector:�e�摜�̑傫���i�������x�N�g���j
	//	semi_short_vector:�e�摜�̑傫���i���Z���x�N�g���j
	//////////////////////////////////////////////////////////////////////////////
	void CreateBullet(POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , THREE_DIMENSIONAL_VECTOR* semi_long_vector , THREE_DIMENSIONAL_VECTOR* semi_short_vector);

	//////////////////////////////////////////////////////////////////////////////
	//�X�V
	//////////////////////////////////////////////////////////////////////////////
	bool Update();
};

