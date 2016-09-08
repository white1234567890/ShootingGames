#include "common.h"
#include <iostream>
#include <gl\glew.h>
#include <gl\glut.h>

#ifdef DEBUG
#include "DebugRoom.h"
#endif // DEBUG

#include "GameMain.h"


//変数の実体化
GAME_MODE GameMode = GAME_INIT;

void reshape(int x , int y)
{
	WINDOW_WIDTH = x;
	WINDOW_HEIGHT = y;

	//ビューポート設定
	glViewport(0 , 0 , x , y);

	//変換行列の初期化
	glLoadIdentity();
}

int main(int argc , char** argv)
{
	//glutの初期化
	glutInit(&argc , argv);

	//ウィンドウサイズの決定
	glutInitWindowSize(WINDOW_WIDTH , WINDOW_HEIGHT);

	//ディスプレイモードの設定
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	//ウィンドウの作成
	glutCreateWindow("Shooting Game");

#ifdef DEBUG
	//初期化
	DebugInit();

	//コールバック関数登録
	glutDisplayFunc(DebugDisplay);
	glutSpecialFunc(DebugInput);
	glutSpecialUpFunc(DebugInputUp);
	glutIgnoreKeyRepeat(GL_TRUE);
	glutIdleFunc(DebugUpdate);
	glutReshapeFunc(reshape);

#endif // DEBUG

#ifdef noDEBUG
	//初期化
	Init();
	
	//コールバック関数登録
	glutDisplayFunc(Display);
	glutSpecialFunc(InputSpetialKeyDown);
	glutSpecialUpFunc(InputSpetialKeyUp);
	glutIgnoreKeyRepeat(GL_TRUE);
	glutIdleFunc(Update);
	glutReshapeFunc(reshape);

#endif // noDEBUG

	//カラーバッファの初期値
	glClearColor(0 , 0 , 0 , 1.f);

	glutMainLoop();
	
	return 0;//ソフトの終了
}
