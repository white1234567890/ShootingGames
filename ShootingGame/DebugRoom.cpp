#include "DebugRoom.h"
#include <gl\glew.h>
#include <gl\glut.h>
#include "PlayerClass.h"

PlayerClass TestPlayer;

void DebugInit()
{
	TestPlayer.Initialize(&POSITION(100 , 100) , &VELOCITY() , &ACCELARATION() ,10);
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
	//カラーバッファを初期化
	glClear(GL_COLOR_BUFFER_BIT);

	//描画
	TestPlayer.Render();

	//命令の実行
	glutSwapBuffers();

	//Circle1.Update();
	//Circle2.Update(&Ground);
	//Circle1.Render();
	//Circle2.Render();
	//Ground.Render();
}