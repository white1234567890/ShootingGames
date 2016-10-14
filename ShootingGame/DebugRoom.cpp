#include "DebugRoom.h"
#include <gl\glew.h>
#include <gl\glut.h>
#include "PlayerManagerClass.h"
#include "PlayerBulletManagerClass.h"
#include "WaveManagerClass.h"
#include "TimerClass.h"

#include <iostream>

TimerClass timer;

void DebugReshape(int x , int y)
{
	WINDOW_WIDTH = x;
	WINDOW_HEIGHT = y;

	cl_PlayerManager->WhenReshaped();

	//ビューポート設定
	glViewport(0 , 0 , x , y);

	//変換行列の初期化
	glLoadIdentity();
}

void DebugInit()
{
	cl_PlayerManager = SingletonClass<PlayerManagerClass>::GetInstance();
	cl_PlayerManager->Initialize();
	cl_EnemyManager = SingletonClass<EnemyManagerClass>::GetInstance();
	cl_EnemyManager->Initiarize();
	cl_WaveManager = SingletonClass<WaveManagerClass>::GetInstance();
	cl_WaveManager->Initiarize(WaveManagerClass::E_STAGE1);
	cl_PlayerBulletManager = SingletonClass<PlayerBulletManagerClass>::GetInstance();
}

void DebugUpdate(int time)
{
	cl_WaveManager->Update(cl_EnemyManager);
	cl_PlayerManager->Update();
	cl_EnemyManager->Update();
	cl_PlayerBulletManager->Update();
	std::cout << timer.TimeCount() / 60 << std::endl;
	glutPostRedisplay();
	glutTimerFunc(16 , DebugUpdate , 0);
}

void DebugDisplay()
{
	//カラーバッファを初期化
	glClear(GL_COLOR_BUFFER_BIT);

	//描画
	cl_PlayerManager->Render();
	cl_EnemyManager->Render();
	cl_PlayerBulletManager->Render();

	//命令の実行
	glutSwapBuffers();
}