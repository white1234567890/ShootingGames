#include "DebugRoom.h"
#include <gl\glew.h>
#include <gl\glut.h>
#include "PlayerManagerClass.h"
#include "PlayerBulletManagerClass.h"
#include "WaveManagerClass.h"
#include "TimerClass.h"

#include <iostream>

TimerClass timer;

//////////////////////////////////////////////////////////////////////////////
//画面の再描画
//////////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////////////
//初期化
//////////////////////////////////////////////////////////////////////////////
void DebugInit()
{
	cl_PlayerManager = SingletonClass<PlayerManagerClass>::GetInstance();	//プレイヤーマネージャーのインスタンス生成
	cl_PlayerManager->Initialize();	//初期化
	cl_EnemyManager = SingletonClass<EnemyManagerClass>::GetInstance();	//エネミーマネージャーのインスタンス生成
	cl_EnemyManager->Initiarize();	//初期化
	cl_WaveManager = SingletonClass<WaveManagerClass>::GetInstance();	//ウェーブマネージャーのインスタンス生成
	cl_WaveManager->Initiarize(WaveManagerClass::E_STAGE1);	//初期化
	cl_PlayerBulletManager = SingletonClass<PlayerBulletManagerClass>::GetInstance();	//プレイヤーバレットマネージャーのインスタンス生成
}

//////////////////////////////////////////////////////////////////////////////
//更新
//引数:
//	time:glutTimerFunc用
//////////////////////////////////////////////////////////////////////////////
void DebugUpdate(int time)
{
	cl_WaveManager->Update(cl_EnemyManager);	//ウェーブマネージャーの更新
	cl_PlayerBulletManager->Update();	//プレイヤーバレットマネージャーの更新
	cl_PlayerManager->Update();	//プレイヤーマネージャーの更新
	cl_EnemyManager->Update(cl_PlayerBulletManager);	//エネミーマネージャーの更新

#ifdef DEBUG
	//std::cout << timer.TimeCount() / 60 << std::endl;
#endif // DEBUG

	glutPostRedisplay();	//画面の再描画
	glutTimerFunc(16 , DebugUpdate , 0);	//glutの更新
}

//////////////////////////////////////////////////////////////////////////////
//描画
//////////////////////////////////////////////////////////////////////////////
void DebugDisplay()
{
	//カラーバッファを初期化
	glClear(GL_COLOR_BUFFER_BIT);

	//描画
	cl_PlayerManager->Render();	//プレイヤーを描画
	cl_EnemyManager->Render();	//エネミーを描画
	cl_PlayerBulletManager->Render();	//プレイヤーの弾を描画

	//命令の実行
	glutSwapBuffers();
	glutPostRedisplay();	//画面の再描画


}