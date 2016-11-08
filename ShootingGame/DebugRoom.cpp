#include "DebugRoom.h"
#include <gl\glew.h>
#include <gl\glut.h>
#include "PlayerManagerClass.h"
#include "PlayerBulletManagerClass.h"
#include "WaveManagerClass.h"
#include "TimerClass.h"

#include <iostream>

TimerClass timer;

//////////////////////////////////////////////////////////////////////////////
//��ʂ̍ĕ`��
//////////////////////////////////////////////////////////////////////////////
void DebugReshape(int x , int y)
{
	WINDOW_WIDTH = x;
	WINDOW_HEIGHT = y;

	cl_PlayerManager->WhenReshaped();

	//�r���[�|�[�g�ݒ�
	glViewport(0 , 0 , x , y);

	//�ϊ��s��̏�����
	glLoadIdentity();
}

//////////////////////////////////////////////////////////////////////////////
//������
//////////////////////////////////////////////////////////////////////////////
void DebugInit()
{
	cl_PlayerManager = SingletonClass<PlayerManagerClass>::GetInstance();	//�v���C���[�}�l�[�W���[�̃C���X�^���X����
	cl_PlayerManager->Initialize();	//������
	cl_EnemyManager = SingletonClass<EnemyManagerClass>::GetInstance();	//�G�l�~�[�}�l�[�W���[�̃C���X�^���X����
	cl_EnemyManager->Initiarize();	//������
	cl_WaveManager = SingletonClass<WaveManagerClass>::GetInstance();	//�E�F�[�u�}�l�[�W���[�̃C���X�^���X����
	cl_WaveManager->Initiarize(WaveManagerClass::E_STAGE1);	//������
	cl_PlayerBulletManager = SingletonClass<PlayerBulletManagerClass>::GetInstance();	//�v���C���[�o���b�g�}�l�[�W���[�̃C���X�^���X����
}

//////////////////////////////////////////////////////////////////////////////
//�X�V
//����:
//	time:glutTimerFunc�p
//////////////////////////////////////////////////////////////////////////////
void DebugUpdate(int time)
{
	cl_WaveManager->Update(cl_EnemyManager);	//�E�F�[�u�}�l�[�W���[�̍X�V
	cl_PlayerBulletManager->Update();	//�v���C���[�o���b�g�}�l�[�W���[�̍X�V
	cl_PlayerManager->Update();	//�v���C���[�}�l�[�W���[�̍X�V
	cl_EnemyManager->Update(cl_PlayerBulletManager);	//�G�l�~�[�}�l�[�W���[�̍X�V

#ifdef DEBUG
	//std::cout << timer.TimeCount() / 60 << std::endl;
#endif // DEBUG

	glutPostRedisplay();	//��ʂ̍ĕ`��
	glutTimerFunc(16 , DebugUpdate , 0);	//glut�̍X�V
}

//////////////////////////////////////////////////////////////////////////////
//�`��
//////////////////////////////////////////////////////////////////////////////
void DebugDisplay()
{
	//�J���[�o�b�t�@��������
	glClear(GL_COLOR_BUFFER_BIT);

	//�`��
	cl_PlayerManager->Render();	//�v���C���[��`��
	cl_EnemyManager->Render();	//�G�l�~�[��`��
	cl_PlayerBulletManager->Render();	//�v���C���[�̒e��`��

	//���߂̎��s
	glutSwapBuffers();
	glutPostRedisplay();	//��ʂ̍ĕ`��


}