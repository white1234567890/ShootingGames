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
void PlayerBulletManagerClass::CreateBullet(POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , THREE_DIMENSIONAL_VECTOR* semi_long_vector , THREE_DIMENSIONAL_VECTOR* semi_short_vector)
{
	BulletClass NewBullet;
	NewBullet.Initialize(position , velocity , accelaration , semi_long_vector , semi_short_vector);
	m_Bullet.PushBack(NewBullet);
}

//////////////////////////////////////////////////////////////////////////////
//�X�V
//////////////////////////////////////////////////////////////////////////////
bool PlayerBulletManagerClass::Update()
{
	//�e���X�g�̐擪�ֈړ�����
	if(m_Bullet.ToBegin())
	{
		//1�x�͎��s����
		do
		{
			//���݂̃m�[�h���X�V����
			m_Bullet.GetCurrentNode().Update();
			//��ʓ��ɂ��Ȃ��Ƃ�
			if(m_Bullet.GetCurrentNode().GetPosition().m_Vector.x < 0 || m_Bullet.GetCurrentNode().GetPosition().m_Vector.x > WINDOW_WIDTH ||
				m_Bullet.GetCurrentNode().GetPosition().m_Vector.y < 0 || m_Bullet.GetCurrentNode().GetPosition().m_Vector.y > WINDOW_HEIGHT)
			{
				//���݂̃m�[�h����菜��
				m_Bullet.RemoveCurrentNode();
			}
			//���̃m�[�h��
		} while (m_Bullet.Next());

	}

	return false;
}