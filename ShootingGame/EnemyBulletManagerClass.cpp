#include "EnemyBulletManagerClass.h"


EnemyBulletManagerClass::EnemyBulletManagerClass(void)
{
}


EnemyBulletManagerClass::~EnemyBulletManagerClass(void)
{
}

//////////////////////////////////////////////////////////////////////////////
//public�֐�
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//�e�𐶐�
//����:
//	position:�����ʒu
//	velocity:�e�̑��x
//	accelaration:�e�̉����x
//	semi_long_vector:�e�摜�̑傫���i�������x�N�g���j
//	semi_short_vector:�e�摜�̑傫���i���Z���x�N�g���j
//////////////////////////////////////////////////////////////////////////////
void EnemyBulletManagerClass::CreateBullet(POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , THREE_DIMENSIONAL_VECTOR* semi_long_vector , THREE_DIMENSIONAL_VECTOR* semi_short_vector)
{
	BulletClass NewBullet;
	NewBullet.Initialize(position , velocity , accelaration , semi_long_vector , semi_short_vector);
	m_Bullet.PushBack(NewBullet);
}

//////////////////////////////////////////////////////////////////////////////
//�X�V
//////////////////////////////////////////////////////////////////////////////
bool EnemyBulletManagerClass::Update()
{
	return true;
}