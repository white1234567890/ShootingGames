#include "DebugRoom.h"
#include <gl\glew.h>
#include <gl\glut.h>
#include "PlayerClass.h"

//#include "CircleCharactorClass.h"
//#include "GroundClass.h"

//CircleClass Circle1;
//CircleCharactorClass Circle2;

PlayerClass TestBox;

void DebugInit()
{
	TestBox.Initialize(&POSITION(100 , 100) , &VELOCITY() , &ACCELARATION() , &THREE_DIMENSION_VECTOR(0 , 50) ,
		&THREE_DIMENSION_VECTOR(50 , 0));

	//Circle1.Initialize(&POSITION(10 , 100) , &VELOCITY(1) , &ACCELARATION(0.1) , 5.0);

	//Circle2.Initialize(&POSITION(10 , 200) , &VELOCITY(1) , &ACCELARATION(0.1) , 20.0);

	//GameMode = GAME_PLAY;
}

void DebugInput(int key , int x , int y)
{
	TestBox.SpecialKeyBoardDown(key);
}

void DebugInputUp(int key , int x , int y)
{
	TestBox.SpecialKeyBoardUp(key);
}
void DebugUpdate()
{
	TestBox.Update();
	glutPostRedisplay();
}

void DebugDisplay()
{
	DebugUpdate();

	//�J���[�o�b�t�@��������
	glClear(GL_COLOR_BUFFER_BIT);

	TestBox.Render();

	//���߂̎��s
	glutSwapBuffers();

	//Circle1.Update();
	//Circle2.Update(&Ground);
	//Circle1.Render();
	//Circle2.Render();
	//Ground.Render();
}