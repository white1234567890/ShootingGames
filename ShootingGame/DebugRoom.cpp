#include "DebugRoom.h"
#include <gl\glew.h>
#include <gl\glut.h>
#include "PlayerClass.h"
#include "ShoulderPartsClass.h"
#include "BackPartsClass.h"
#include "HipPartsClass.h"
#include "PlayerBulletManagerClass.h"

void DebugReshape(int x , int y)
{
	WINDOW_WIDTH = x;
	WINDOW_HEIGHT = y;

	TestPlayer.SetPlayerSpeed(PLAYER_SPEED_X_ASPECT * WINDOW_WIDTH * WINDOW_HEIGHT / 100000 , PLAYER_SPEED_Y_ASPECT * WINDOW_WIDTH * WINDOW_HEIGHT / 100000);

	//ビューポート設定
	glViewport(0 , 0 , x , y);

	//変換行列の初期化
	glLoadIdentity();
}

void DebugInit()
{
	TestPlayer.Initialize(&POSITION(100 , 100) , &VELOCITY() , &ACCELARATION() , &THREE_DIMENSION_VECTOR(0 , 32) ,
		&THREE_DIMENSION_VECTOR(32) , &TestShoulderL , &TestShoulderR , &TestBack , &TestHip);
	TestShoulderL.SetShotStatus(1 , &VELOCITY(0 , 1) , 1 , &ACCELARATION() , &THREE_DIMENSION_VECTOR(5) , &THREE_DIMENSION_VECTOR(0 , 5));
	cl_PlayerBulletManager = SingletonClass<PlayerBulletManagerClass>::GetInstance();
}

void DebugUpdate()
{
	TestPlayer.KeyBoard();
	TestPlayer.Update();
	cl_PlayerBulletManager->Update();
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
}