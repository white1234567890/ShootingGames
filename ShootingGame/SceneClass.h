#pragma once
#include "PlayerClass.h"
#include "ShoulderPartsClass.h"
#include "BackPartsClass.h"
#include "HipPartsClass.h"
#include "PlayerBulletManagerClass.h"

class BaseSceneClass
{
public:
	//コンストラクタ
	BaseSceneClass(void);
	//デストラクタ
	virtual ~BaseSceneClass(void);

	//メンバ関数
	virtual bool Initiarize() = 0;	//シーンの初期化
	virtual bool Update() = 0;	//シーンの更新
	virtual void Render() = 0;	//シーンの描画
};

class SceneTitleClass :
	public BaseSceneClass , public InputClass
{
public:

	//コンストラクタ
	SceneTitleClass();
	//デストラクタ
	~SceneTitleClass();

	//メンバ関数
	bool Initiarize();	//シーンの初期化
	bool Update();	//シーンの更新
	void Render();	//シーンの描画
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
	//コンストラクタ
	SceneMainClass ();
	//デストラクタ
	~SceneMainClass ();

	//メンバ関数
	bool Initiarize();	//シーンの初期化
	bool Update();	//シーンの更新
	void Render();	//シーンの描画
};