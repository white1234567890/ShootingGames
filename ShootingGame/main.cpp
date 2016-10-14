#include "common.h"
#include <iostream>
#include <gl\glew.h>
#include <gl\glut.h>

#include "DebugRoom.h"
#include "SceneManagerClass.h"

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
	glutTimerFunc(16 , DebugUpdate , 0);
	glutReshapeFunc(DebugReshape);

#endif // DEBUG
	//cl_SceneManager = SingletonClass<SceneManagerClass>::GetInstance();
	//cl_SceneManager->ChangeScene(SceneManagerClass::E_GAME_TITLE);

	//glutDisplayFunc(SceneManagerClass::Render);
	//glutTimerFunc(16 , SceneManagerClass::Update , 0);
	//glutReshapeFunc(SceneManagerClass::Reshape);	

	//�J���[�o�b�t�@�̏����l
	glClearColor(0 , 0 , 0 , 1.f);

	glutMainLoop();
	
	return 0;//�\�t�g�̏I��
}
