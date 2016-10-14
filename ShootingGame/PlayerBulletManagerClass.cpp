#include "PlayerBulletManagerClass.h"

//���̉�
PlayerBulletManagerClass* cl_PlayerBulletManager;

//�R���X�g���N�^
PlayerBulletManagerClass::PlayerBulletManagerClass(void)
{
}

//�f�X�g���N�^
PlayerBulletManagerClass::~PlayerBulletManagerClass(void)
{
}

//////////////////////////////////////////////////////////////////////////////
//�T��:
//	�e�����
//����:
//	*position:�����ʒu
//	*velocity:�ړ����x
//	*accelaration:�ړ������x
//	*semi_long_vector:�������x�N�g��
//	*semi_short_vector:���Z���x�N�g��
//////////////////////////////////////////////////////////////////////////////
void PlayerBulletManagerClass::CreateBullet(POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , THREE_DIMENSION_VECTOR* semi_long_vector , THREE_DIMENSION_VECTOR* semi_short_vector)
{
	BulletClass NewBullet;
	NewBullet.Initialize(position , velocity , accelaration , semi_long_vector , semi_short_vector);
	m_Bullet.PushBack(NewBullet);
}

bool PlayerBulletManagerClass::Update()
{
	if(m_Bullet.ToBegin())
	{
		do
		{
			m_Bullet.GetCurrentNode().Update();
			if(m_Bullet.GetCurrentNode().GetPosition().m_Vector.x < 0 || m_Bullet.GetCurrentNode().GetPosition().m_Vector.x > WINDOW_WIDTH ||
				m_Bullet.GetCurrentNode().GetPosition().m_Vector.y < 0 || m_Bullet.GetCurrentNode().GetPosition().m_Vector.y > WINDOW_HEIGHT)
			{
				m_Bullet.RemoveCurrentNode();
			}
		} while (m_Bullet.Next());

	}

	return false;
}