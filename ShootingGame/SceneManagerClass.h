#pragma once
#include "SingletonClass.h"
#include "SceneClass.h"

class SceneManagerClass :
	public SingletonClass<SceneManagerClass>
{
public:
	friend class SingletonClass<SceneManagerClass>;	//シングルトンからのインスタンス生成を許可する

private:
	static BaseSceneClass *m_Scene;	//シーンオブジェクト

protected:
	SceneManagerClass(void);
	virtual ~SceneManagerClass(void);

public:
	//シーン列挙型
	enum _SCENE
	{
		E_GAME_TITLE,	//タイトルシーン
		E_GAME_MAIN,	//メインシーン
	};

	static bool ChangeScene(_SCENE scene);	//シーンの遷移
	static void Reshape(int x , int y);
	static bool Initiarize();	//シーンの初期化
	static void Update(int time);	//シーンの更新
	static void Render();	//シーンの描画
};

extern SceneManagerClass* cl_SceneManager;