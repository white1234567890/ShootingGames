#include "common.h"
#include <iostream>
#include <gl\glew.h>
#include <gl\glut.h>

#include "DebugRoom.h"
#include "SceneManagerClass.h"

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
	//DebugInit();
	
	//コールバック関数登録
	/*glutDisplayFunc(DebugDisplay);
	glutIgnoreKeyRepeat(GL_TRUE);
	glutTimerFunc(100 , DebugUpdate , 0);
	glutReshapeFunc(DebugReshape);*/

#endif // DEBUG
	cl_SceneManager = SingletonClass<SceneManagerClass>::GetInstance();
	cl_SceneManager->ChangeScene(SceneManagerClass::E_GAME_TITLE);

	glutDisplayFunc(SceneManagerClass::Render);
	glutIgnoreKeyRepeat(GL_TRUE);
	glutTimerFunc(100 , SceneManagerClass::Update , 0);
	glutReshapeFunc(SceneManagerClass::Reshape);	

	//カラーバッファの初期値
	glClearColor(0 , 0 , 0 , 1.f);

	glutMainLoop();
	
	return 0;//ソフトの終了
}
