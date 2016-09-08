#include "common.h"
#include <iostream>
#include <gl\glew.h>
#include <gl\glut.h>

#ifdef DEBUG
#include "DebugRoom.h"
#endif // DEBUG

#include "GameMain.h"


//�ϐ��̎��̉�
GAME_MODE GameMode = GAME_INIT;

void reshape(int x , int y)
{
	WINDOW_WIDTH = x;
	WINDOW_HEIGHT = y;

	//�r���[�|�[�g�ݒ�
	glViewport(0 , 0 , x , y);

	//�ϊ��s��̏�����
	glLoadIdentity();
}

int main(int argc , char** argv)
{
	//glut�̏�����
	glutInit(&argc , argv);

	//�E�B���h�E�T�C�Y�̌���
	glutInitWindowSize(WINDOW_WIDTH , WINDOW_HEIGHT);

	//�f�B�X�v���C���[�h�̐ݒ�
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	//�E�B���h�E�̍쐬
	glutCreateWindow("Shooting Game");

#ifdef DEBUG
	//������
	DebugInit();

	//�R�[���o�b�N�֐��o�^
	glutDisplayFunc(DebugDisplay);
	glutSpecialFunc(DebugInput);
	glutSpecialUpFunc(DebugInputUp);
	glutIgnoreKeyRepeat(GL_TRUE);
	glutIdleFunc(DebugUpdate);
	glutReshapeFunc(reshape);

#endif // DEBUG

#ifdef noDEBUG
	//������
	Init();
	
	//�R�[���o�b�N�֐��o�^
	glutDisplayFunc(Display);
	glutSpecialFunc(InputSpetialKeyDown);
	glutSpecialUpFunc(InputSpetialKeyUp);
	glutIgnoreKeyRepeat(GL_TRUE);
	glutIdleFunc(Update);
	glutReshapeFunc(reshape);

#endif // noDEBUG

	//�J���[�o�b�t�@�̏����l
	glClearColor(0 , 0 , 0 , 1.f);

	glutMainLoop();
	
	return 0;//�\�t�g�̏I��
}
