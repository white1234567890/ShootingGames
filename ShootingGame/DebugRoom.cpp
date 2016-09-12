#include "DebugRoom.h"
#include <gl\glew.h>
#include <gl\glut.h>
#include "PlayerClass.h"
#include "ShoulderPartsClass.h"
#include "BackPartsClass.h"
#include "HipPartsClass.h"

void DebugReshape(int x , int y)
{
	WINDOW_WIDTH = x;
	WINDOW_HEIGHT = y;

	TestPlayer.SetPlayerSpeed(PLAYER_SPEED_X_ASPECT * WINDOW_WIDTH * WINDOW_HEIGHT / 100000 , PLAYER_SPEED_Y_ASPECT * WINDOW_WIDTH * WINDOW_HEIGHT / 100000);

	//�r���[�|�[�g�ݒ�
	glViewport(0 , 0 , x , y);

	//�ϊ��s��̏�����
	glLoadIdentity();
}


void DebugInit()
{
	TestPlayer.Initialize(&POSITION(100 , 100) , &VELOCITY() , &ACCELARATION() , &THREE_DIMENSION_VECTOR(0 , 32) ,
		&THREE_DIMENSION_VECTOR(32) , &TestShoulderL , &TestShoulderR , &TestBack , &TestHip);
}

void DebugInput(int key , int x , int y)
{
	TestPlayer.SpecialKeyBoardDown(key);
}

void DebugInputUp(int key , int x , int y)
{
	TestPlayer.SpecialKeyBoardUp(key);
}

void DebugUpdate()
{
	TestPlayer.Update();
	glutPostRedisplay();
}

void DebugDisplay()
{
	//�J���[�o�b�t�@��������
	glClear(GL_COLOR_BUFFER_BIT);

	//�`��
	TestPlayer.Render();

	//���߂̎��s
	glutSwapBuffers();
}