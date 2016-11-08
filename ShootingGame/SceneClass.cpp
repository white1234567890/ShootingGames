#include "SceneManagerClass.h"

#include <gl\glew.h>
#include <gl\glut.h>

#include "common.h"

//////////////////////////////////////////////////////////////////////////////
//BaseSceneClass
//////////////////////////////////////////////////////////////////////////////

//コンストラクタ
BaseSceneClass::BaseSceneClass(void)
{
}

//デストラクタ
BaseSceneClass::~BaseSceneClass(void)
{
}

//////////////////////////////////////////////////////////////////////////////
//public関数
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//概略:
//	描画再定義（純粋仮想関数）
//////////////////////////////////////////////////////////////////////////////
void BaseSceneClass::Reshape()
{
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	初期化(純粋仮想関数)
//////////////////////////////////////////////////////////////////////////////
bool BaseSceneClass::Initiarize()
{
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	更新(純粋仮想関数)
//////////////////////////////////////////////////////////////////////////////
bool BaseSceneClass::Update()
{
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	描画(純粋仮想関数)
//////////////////////////////////////////////////////////////////////////////
void BaseSceneClass::Render()
{
}

//////////////////////////////////////////////////////////////////////////////
//SceneTitleClass
//////////////////////////////////////////////////////////////////////////////

//コンストラクタ
SceneTitleClass::SceneTitleClass()
{
}

//デストラクタ
SceneTitleClass::~SceneTitleClass()
{
}

//////////////////////////////////////////////////////////////////////////////
//public関数
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//概略:
//	ウィンドウサイズが変化したときに合わせる
//////////////////////////////////////////////////////////////////////////////
void SceneTitleClass::Reshape()
{
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	タイトルシーンを初期化する
//戻り値:
//	true:初期化成功
//	false:初期化失敗
//////////////////////////////////////////////////////////////////////////////
bool SceneTitleClass::Initiarize()
{
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	タイトルシーンを更新する
//戻り値:
//	true:更新成功
//////////////////////////////////////////////////////////////////////////////
bool SceneTitleClass::Update()
{
	if(InputKey(InputClass::E_PROHIBIT_PRESS_TWICE) & InputClass::E_Z_KEY)
	{
		if(!SceneManagerClass::ChangeScene(SceneManagerClass::E_GAME_MAIN)) return false;
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	タイトルシーンを描画する
//////////////////////////////////////////////////////////////////////////////
void SceneTitleClass::Render()
{
	//カラーバッファを初期化
	glClear(GL_COLOR_BUFFER_BIT);

	//命令の実行
	glutSwapBuffers();
}

//////////////////////////////////////////////////////////////////////////////
//SceneMainClass
//////////////////////////////////////////////////////////////////////////////

//コンストラクタ
SceneMainClass::SceneMainClass ()
{
}

//デストラクタ
SceneMainClass::~SceneMainClass ()
{
}

//////////////////////////////////////////////////////////////////////////////
//public関数
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//概略:
//	ウィンドウサイズが変化したときに合わせる
//////////////////////////////////////////////////////////////////////////////
void SceneMainClass::Reshape()
{
	//プレイヤーのリシェイプ処理
	cl_PlayerManager->WhenReshaped();
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	メインシーンを初期化する
//戻り値:
//	true:初期化成功
//	false:初期化失敗
//////////////////////////////////////////////////////////////////////////////
bool SceneMainClass::Initiarize()
{
	//プレイヤーマネージャーのインスタンス生成
	cl_PlayerManager = SingletonClass<PlayerManagerClass>::GetInstance();

	//プレイヤーマネージャーの初期化
	cl_PlayerManager->Initialize();

	//エネミーマネージャーのインスタンス生成
	cl_EnemyManager = SingletonClass<EnemyManagerClass>::GetInstance();
	
	//エネミーマネージャーの初期化
	cl_EnemyManager->Initiarize();

	//プレイヤーバレットマネージャーのインスタンス生成
	cl_PlayerBulletManager = SingletonClass<PlayerBulletManagerClass>::GetInstance();
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	メインシーンを更新する
//戻り値:
//	true:更新成功
//////////////////////////////////////////////////////////////////////////////
bool SceneMainClass::Update()
{
	//プレイヤーの更新
	m_PlayerManager->Update();

	//敵の更新
	m_EnemyManager->Update(m_PlayerBulletManager);

	//プレイヤーの弾の更新
	m_PlayerBulletManager->Update();
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	メインシーンを描画する
//////////////////////////////////////////////////////////////////////////////
void SceneMainClass::Render()
{
	//カラーバッファを初期化
	glClear(GL_COLOR_BUFFER_BIT);
	
	//描画

	//プレイヤーの描画
	m_PlayerManager->Render();

	//敵の描画
	m_EnemyManager->Render();

	//プレイヤーの弾の描画
	m_PlayerBulletManager->Render();

	//命令の実行
	glutSwapBuffers();
}