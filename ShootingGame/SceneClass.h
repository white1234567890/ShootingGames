#pragma once
#include "PlayerManagerClass.h"
#include "EnemyManagerClass.h"
#include "PlayerBulletManagerClass.h"

class BaseSceneClass
{
public:
	//�R���X�g���N�^
	BaseSceneClass(void);
	//�f�X�g���N�^
	virtual ~BaseSceneClass(void);

	//�����o�֐�
	virtual void Reshape() = 0;	//��ʂ̍Ē�`
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
	void Reshape();	//��ʂ̍Ē�`
	bool Initiarize();	//�V�[���̏�����
	bool Update();	//�V�[���̍X�V
	void Render();	//�V�[���̕`��
};

class SceneMainClass :
	public BaseSceneClass
{
private:


public:
	//�R���X�g���N�^
	SceneMainClass ();
	//�f�X�g���N�^
	~SceneMainClass ();

	//�����o�֐�
	void Reshape();	//��ʂ̍Ē�`
	bool Initiarize();	//�V�[���̏�����
	bool Update();	//�V�[���̍X�V
	void Render();	//�V�[���̕`��
};