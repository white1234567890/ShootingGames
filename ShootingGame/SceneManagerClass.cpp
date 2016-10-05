#include "SceneManagerClass.h"

#include <gl\glew.h>
#include <gl\glut.h>

#include "common.h"

//////////////////////////////////////////////////////////////////////////////
//�ÓI�ϐ�
//////////////////////////////////////////////////////////////////////////////

BaseSceneClass *SceneManagerClass::m_Scene;

//////////////////////////////////////////////////////////////////////////////
//���̉�
//////////////////////////////////////////////////////////////////////////////
SceneManagerClass* cl_SceneManager;

SceneManagerClass::SceneManagerClass(void)
{
}


SceneManagerClass::~SceneManagerClass(void)
{
}

//////////////////////////////////////////////////////////////////////////////
//public�֐�
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

	//�r���[�|�[�g�ݒ�
	glViewport(0 , 0 , x , y);

	//�ϊ��s��̏�����
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