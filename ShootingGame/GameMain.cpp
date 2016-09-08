#include "DebugRoom.h"
#include <gl\glew.h>
#include <gl\glut.h>
#include "PlayerClass.h"

PlayerClass Player;

void Init()
{
	Player.Initialize(&POSITION(100 , 100) , &VELOCITY() , &ACCELARATION() ,10);
}

void InputSupecialKeyDown(int key , int x , int y)
{
	Player.SpecialKeyBoardDown(key);
}

void InputSpecialKeyUp(int key , int x , int y)
{
	Player.SpecialKeyBoardUp(key);
}

void Update()
{
	Player.Update();
	glutPostRedisplay();
}

void Display()
{
	//�J���[�o�b�t�@��������
	glClear(GL_COLOR_BUFFER_BIT);

	//�`��
	Player.Render();

	//���߂̎��s
	glutSwapBuffers();

	//Circle1.Update();
	//Circle2.Update(&Ground);
	//Circle1.Render();
	//Circle2.Render();
	//Ground.Render();
}