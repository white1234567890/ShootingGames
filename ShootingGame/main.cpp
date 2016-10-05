#include "common.h"
#include <iostream>
#include <gl\glew.h>
#include <gl\glut.h>

#include "DebugRoom.h"
#include "FileManagerClass.h"

//�ϐ��̎��̉�
GAME_MODE GameMode = GAME_INIT;

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

	cl_FileManager = SingletonClass<FileManagerClass>::GetInstance();

#ifdef DEBUG
	//������
	DebugInit();

	//�R�[���o�b�N�֐��o�^
	glutDisplayFunc(DebugDisplay);
	glutIgnoreKeyRepeat(GL_TRUE);
	glutTimerFunc(100 , DebugUpdate , 0);
	glutReshapeFunc(DebugReshape);

#endif // DEBUG

	//�J���[�o�b�t�@�̏����l
	glClearColor(0 , 0 , 0 , 1.f);

	glutMainLoop();
	
	return 0;//�\�t�g�̏I��
}
