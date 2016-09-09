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
	TestBox.Initialize(&POSITION(100 , 100) , &VELOCITY() , &ACCELARATION() , &THREE_DIMENSION_VECTOR(0 , 32) ,
		&THREE_DIMENSION_VECTOR(32 , 0));

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
	//カラーバッファを初期化
	glClear(GL_COLOR_BUFFER_BIT);

	//描画
	TestBox.Render();

	//命令の実行
	glutSwapBuffers();

	//Circle1.Update();
	//Circle2.Update(&Ground);
	//Circle1.Render();
	//Circle2.Render();
	//Ground.Render();
}