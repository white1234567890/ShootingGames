#pragma once
#include "SingletonClass.h"
#include "SceneClass.h"

class SceneManagerClass :
	public SingletonClass<SceneManagerClass>
{
public:
	friend class SingletonClass<SceneManagerClass>;	//�V���O���g������̃C���X�^���X������������

private:
	static BaseSceneClass *m_Scene;	//�V�[���I�u�W�F�N�g

protected:
	SceneManagerClass(void);
	virtual ~SceneManagerClass(void);

public:
	//�V�[���񋓌^
	enum _SCENE
	{
		E_GAME_TITLE,	//�^�C�g���V�[��
		E_GAME_MAIN,	//���C���V�[��
	};

	static bool ChangeScene(_SCENE scene);	//�V�[���̑J��
	static void Reshape(int x , int y);
	static bool Initiarize();	//�V�[���̏�����
	static void Update(int time);	//�V�[���̍X�V
	static void Render();	//�V�[���̕`��
};

extern SceneManagerClass* cl_SceneManager;