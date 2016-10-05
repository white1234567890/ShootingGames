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

	TestPlayer.SetPlayerSpeed(PLAYER_SPEED_X_ASPECT * WINDOW_WIDTH * WINDOW_HEIGHT / PLAYER_SPEED_ASPECT , PLAYER_SPEED_Y_ASPECT * WINDOW_WIDTH * WINDOW_HEIGHT / PLAYER_SPEED_ASPECT);

	//ビューポート設定
	glViewport(0 , 0 , x , y);

	//変換行列の初期化
	glLoadIdentity();
}

void DebugInit()
{
	TestPlayer.Initialize(&POSITION(WINDOW_WIDTH / 2 , WINDOW_HEIGHT / 10) , &VELOCITY(50 , 50) , &ACCELARATION() , &THREE_DIMENSION_VECTOR(0 , 32) ,
		&THREE_DIMENSION_VECTOR(32) , &TestShoulderL , &TestShoulderR , &TestBack , &TestHip);
	TestShoulderL.SetShotStatus(1 , &VELOCITY(0 , 1) , 10 , &ACCELARATION() , &THREE_DIMENSION_VECTOR(5) , &THREE_DIMENSION_VECTOR(0 , 5));
	TestShoulderR.SetShotStatus(1 , &VELOCITY(0 , 1) , 10 , &ACCELARATION() , &THREE_DIMENSION_VECTOR(5) , &THREE_DIMENSION_VECTOR(0 , 5));
	cl_PlayerBulletManager = SingletonClass<PlayerBulletManagerClass>::GetInstance();
}

void DebugUpdate(int time)
{
	TestPlayer.KeyBoard();
	TestPlayer.Update();
	cl_PlayerBulletManager->Update();
	glutPostRedisplay();
	glutTimerFunc(16 , DebugUpdate , 0);
}

void DebugDisplay()
{
	//カラーバッファを初期化
	glClear(GL_COLOR_BUFFER_BIT);

	//描画
	TestPlayer.Render();
	cl_PlayerBulletManager->Render();

	//命令の実行
	glutSwapBuffers();
}