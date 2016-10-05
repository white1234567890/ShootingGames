#include "SceneManagerClass.h"

#include <gl\glew.h>
#include <gl\glut.h>

#include "common.h"

//////////////////////////////////////////////////////////////////////////////
//静的変数
//////////////////////////////////////////////////////////////////////////////

BaseSceneClass *SceneManagerClass::m_Scene;

//////////////////////////////////////////////////////////////////////////////
//実体化
//////////////////////////////////////////////////////////////////////////////
SceneManagerClass* cl_SceneManager;

SceneManagerClass::SceneManagerClass(void)
{
}


SceneManagerClass::~SceneManagerClass(void)
{
}

//////////////////////////////////////////////////////////////////////////////
//public関数
//////////////////////////////////////////////////////////////////////////////

void SceneManagerClass::ChangeScene(_SCENE scene)
{
	static SceneTitleClass SceneTitle;
	static SceneMainClass SceneMain;

	switch (scene)
	{
	case SceneManagerClass::E_GAME_TITLE:
		m_Scene = &SceneTitle;
		break;

	case SceneManagerClass::E_GAME_MAIN:
		m_Scene = &SceneMain;
		break;
	}

	Initiarize();
}

void SceneManagerClass::Reshape(int x , int y)
{
	WINDOW_WIDTH = x;
	WINDOW_HEIGHT = y;

	//ビューポート設定
	glViewport(0 , 0 , x , y);

	//変換行列の初期化
	glLoadIdentity();
}

bool SceneManagerClass::Initiarize()
{
	if(!m_Scene->Initiarize()) return false;
	return true;
}

void SceneManagerClass::Update(int time)
{
	m_Scene->Update();
	glutPostRedisplay();
	glutTimerFunc(16 , Update , 0);
}

void SceneManagerClass::Render()
{
	m_Scene->Render();
}