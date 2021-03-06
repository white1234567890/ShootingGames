#pragma once
#include "PlayerManagerClass.h"
#include "EnemyManagerClass.h"
#include "PlayerBulletManagerClass.h"
#include "WaveManagerClass.h"

//シーンのステートパターンクラス
class BaseSceneClass
{
public:
	//コンストラクタ
	BaseSceneClass(void);
	//デストラクタ
	virtual ~BaseSceneClass(void);

	//メンバ関数

	//////////////////////////////////////////////////////////////////////////////
	//概略:
	//	描画再定義（純粋仮想関数）
	//////////////////////////////////////////////////////////////////////////////
	virtual void Reshape() = 0;

	//////////////////////////////////////////////////////////////////////////////
	//概略:
	//	初期化(純粋仮想関数)
	//////////////////////////////////////////////////////////////////////////////
	virtual bool Initiarize() = 0;

	//////////////////////////////////////////////////////////////////////////////
	//概略:
	//	更新(純粋仮想関数)

	//////////////////////////////////////////////////////////////////////////////
	virtual bool Update() = 0;

	//////////////////////////////////////////////////////////////////////////////
	//概略:
	//	描画(純粋仮想関数)
	//////////////////////////////////////////////////////////////////////////////
	virtual void Render() = 0;
};

//タイトルシーンステート
class SceneTitleClass :
	public BaseSceneClass , public InputClass
{
public:

	//コンストラクタ
	SceneTitleClass();
	//デストラクタ
	~SceneTitleClass();

	//メンバ関数

	//////////////////////////////////////////////////////////////////////////////
	//概略:
	//	ウィンドウサイズが変化したときに合わせる
	//////////////////////////////////////////////////////////////////////////////
	void Reshape();

	//////////////////////////////////////////////////////////////////////////////
	//概略:
	//	タイトルシーンを初期化する
	//戻り値:
	//	true:初期化成功
	//	false:初期化失敗
	//////////////////////////////////////////////////////////////////////////////
	bool Initiarize();

	//////////////////////////////////////////////////////////////////////////////
	//概略:
	//	タイトルシーンを更新する
	//戻り値:
	//	true:更新成功
	//////////////////////////////////////////////////////////////////////////////
	bool Update();

	//////////////////////////////////////////////////////////////////////////////
	//概略:
	//	タイトルシーンを描画する
	//////////////////////////////////////////////////////////////////////////////
	void Render();
};

//メインシーンステート
class SceneMainClass :
	public BaseSceneClass
{
private:
	PlayerManagerClass *m_PlayerManager;
	EnemyManagerClass *m_EnemyManager;
	PlayerBulletManagerClass *m_PlayerBulletManager;
	WaveManagerClass *m_WaveManager;

public:
	//コンストラクタ
	SceneMainClass ();
	//デストラクタ
	~SceneMainClass ();

	//メンバ関数

	//////////////////////////////////////////////////////////////////////////////
	//概略:
	//	ウィンドウサイズが変化したときに合わせる
	//////////////////////////////////////////////////////////////////////////////
	void Reshape();

	//////////////////////////////////////////////////////////////////////////////
	//概略:
	//	メインシーンを初期化する
	//戻り値:
	//	true:初期化成功
	//	false:初期化失敗
	//////////////////////////////////////////////////////////////////////////////
	bool Initiarize();
	
	//////////////////////////////////////////////////////////////////////////////
	//概略:
	//	メインシーンを更新する
	//戻り値:
	//	true:更新成功
	//////////////////////////////////////////////////////////////////////////////
	bool Update();
	
	//////////////////////////////////////////////////////////////////////////////
	//概略:
	//	メインシーンを描画する
	//////////////////////////////////////////////////////////////////////////////
	void Render();
};