#include "EnemyManagerClass.h"

//���̉�
EnemyManagerClass* cl_EnemyManager;


EnemyManagerClass::EnemyManagerClass(void)
{

}


EnemyManagerClass::~EnemyManagerClass(void)
{
}

//////////////////////////////////////////////////////////////////////////////
//public�֐�
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//�G����
//����:
//	wave_manager:�E�F�[�u�}�l�[�W���[
//	enemy_type:�I�^�C�v
//	position:�G�����ʒu
//////////////////////////////////////////////////////////////////////////////
bool EnemyManagerClass::CreateEnemy(WaveManagerClass *wave_manager , int enemy_type , POSITION* position)
{
	EnemyContextClass NewEnemy;	//���X�g�ɒǉ�����p�̓G
	//�G������������
	NewEnemy.Initiarize(wave_manager , enemy_type , position);
	//���X�g�̖����ɒǉ�����
	m_Enemy.PushBack(NewEnemy);
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//������
//////////////////////////////////////////////////////////////////////////////
bool EnemyManagerClass::Initiarize()
{
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//�X�V
//////////////////////////////////////////////////////////////////////////////
bool EnemyManagerClass::Update(PlayerBulletManagerClass *player_bullet_manager)
{
	//�G���X�g�̍ŏ��Ɉړ�
	if(m_Enemy.ToBegin())
	{
		//1��͎��s����
		do
		{
			//�G���X�g�̌��݂̃m�[�h���X�V
			//�G���v���C���[�̒e�ɓ������������
			if(!m_Enemy.GetCurrentNode().Update(player_bullet_manager))
			{
				//�G�̊J��
				m_Enemy.GetCurrentNode().Release();
				//���݂̃m�[�h����菜��
				m_Enemy.RemoveCurrentNode();
			}

			//��ʓ��ɂ��Ȃ��Ƃ�
			else if(!m_Enemy.GetCurrentNode().CheckEnemyIsInScreen())
			{
				//�G���J��
				m_Enemy.GetCurrentNode().Release();
				//���݂̃m�[�h����菜��
				m_Enemy.RemoveCurrentNode();
			}
			//���̃m�[�h��
		} while (m_Enemy.Next());
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////////
//�`��
//////////////////////////////////////////////////////////////////////////////
void EnemyManagerClass::Render()
{
	//�G���X�g�̍ŏ��Ɉړ�����
	if(m_Enemy.ToBegin())
	{
		//1��͎��s����
		do
		{
			//�G���X�g�̌��݂̃m�[�h��`�悷��
			m_Enemy.GetCurrentNode().Render();
			//���̃m�[�h��
		} while (m_Enemy.Next());
	}
}