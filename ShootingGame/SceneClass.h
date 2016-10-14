#pragma once
#include "PlayerManagerClass.h"
#include "EnemyManagerClass.h"
#include "PlayerBulletManagerClass.h"

class BaseSceneClass
{
public:
	//コンストラクタ
	BaseSceneClass(void);
	//デストラクタ
	virtual ~BaseSceneClass(void);

	//メンバ関数
	virtual void Reshape() = 0;	//画面の再定義
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
	void Reshape();	//画面の再定義
	bool Initiarize();	//シーンの初期化
	bool Update();	//シーンの更新
	void Render();	//シーンの描画
};

class SceneMainClass :
	public BaseSceneClass
{
private:


public:
	//コンストラクタ
	SceneMainClass ();
	//デストラクタ
	~SceneMainClass ();

	//メンバ関数
	void Reshape();	//画面の再定義
	bool Initiarize();	//シーンの初期化
	bool Update();	//シーンの更新
	void Render();	//シーンの描画
};