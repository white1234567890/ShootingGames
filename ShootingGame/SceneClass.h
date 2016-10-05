#pragma once
#include "PlayerClass.h"
#include "ShoulderPartsClass.h"
#include "BackPartsClass.h"
#include "HipPartsClass.h"
#include "PlayerBulletManagerClass.h"

class BaseSceneClass
{
public:
	//�R���X�g���N�^
	BaseSceneClass(void);
	//�f�X�g���N�^
	virtual ~BaseSceneClass(void);

	//�����o�֐�
	virtual bool Initiarize() = 0;	//�V�[���̏�����
	virtual bool Update() = 0;	//�V�[���̍X�V
	virtual void Render() = 0;	//�V�[���̕`��
};

class SceneTitleClass :
	public BaseSceneClass , public InputClass
{
public:

	//�R���X�g���N�^
	SceneTitleClass();
	//�f�X�g���N�^
	~SceneTitleClass();

	//�����o�֐�
	bool Initiarize();	//�V�[���̏�����
	bool Update();	//�V�[���̍X�V
	void Render();	//�V�[���̕`��
};

class SceneMainClass :
	public BaseSceneClass
{
private:
	PlayerClass m_Player;
	ShoulderPartsClass m_Shoulder_L;
	ShoulderPartsClass m_Shoulder_R;
	BackPartsClass m_Back;
	HipPartsClass m_Hip;

	

public:
	//�R���X�g���N�^
	SceneMainClass ();
	//�f�X�g���N�^
	~SceneMainClass ();

	//�����o�֐�
	bool Initiarize();	//�V�[���̏�����
	bool Update();	//�V�[���̍X�V
	void Render();	//�V�[���̕`��
};