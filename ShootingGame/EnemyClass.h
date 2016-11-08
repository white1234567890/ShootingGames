#pragma once
#include "BoxClass.h"
#include "TimerClass.h"
#include "PlayerBulletManagerClass.h"

//使用クラス宣言
class WaveManagerClass;

//////////////////////////////////////////////////////////////////////////////
//敵のステートパターン
//////////////////////////////////////////////////////////////////////////////
class EnemyStatePatternClass :
	public BoxClass , public TimerClass
{
protected:
	POSITION m_ShotPosition;	//ショットの位置
	double m_BarrelRange;	//ショットの初期位置を割り出すための長さ
	VELOCITY m_ShotVelocity;	//ショットの初速
	ACCELARATION m_ShotAccelaration;	//ショットの加速度
	THREE_DIMENSIONAL_VECTOR m_ShotSemiLongVector;	//ショットの画像の半長軸長
	THREE_DIMENSIONAL_VECTOR m_ShotSemiShortVector;	//ショットの画像の半短軸長
	double m_ShotSpeed;	//ショットの速さ
	bool m_ShotFlag;	//弾を撃つフラグ
	int m_ShotCount;	//弾を撃つフレームカウント数

	//敵情報をロード（純粋仮想関数）
	virtual bool LoadEnemyStatus(WaveManagerClass *wave_manager , POSITION* position) = 0;

	//敵の位置を移動（純粋仮想関数）
	virtual void MoveObject() = 0;

	//敵が弾を撃つ（純粋仮想関数）
	virtual void ShotBullet() = 0;

	//////////////////////////////////////////////////////////////////////////////
	//敵とプレイヤーの弾の当たり判定
	//////////////////////////////////////////////////////////////////////////////
	bool CheckHitEnemy_and_PlayerBullet(PlayerBulletManagerClass *player_bullet_manager);

public:
	EnemyStatePatternClass();
	~EnemyStatePatternClass();
	
	//初期化（純粋仮想関数）
	virtual bool Initialize(WaveManagerClass *wave_manager , POSITION* position) = 0;

	//更新（純粋仮想関数）
	virtual bool Update(PlayerBulletManagerClass *player_bullet_manager) = 0;

	//描画（純粋仮想関数）
	virtual void Render() = 0;
};

//////////////////////////////////////////////////////////////////////////////
//敵ステートクラス１
//////////////////////////////////////////////////////////////////////////////
class EnemyType1Class :
	public EnemyStatePatternClass
{
private:
	int m_BulletType;	//弾のタイプ

	//////////////////////////////////////////////////////////////////////////////
	//敵情報をロード
	//引数:
	//	wave_manager:ウェーブマネージャー
	//	position:敵生成位置
	//	true:敵情報のロードに成功
	//	false:敵情報のロードに失敗
	//////////////////////////////////////////////////////////////////////////////
	bool LoadEnemyStatus(WaveManagerClass *wave_manager , POSITION* position);

	//////////////////////////////////////////////////////////////////////////////
	//敵の位置を移動
	//////////////////////////////////////////////////////////////////////////////
	void MoveObject();

	//////////////////////////////////////////////////////////////////////////////
	//敵が弾を撃つ
	//////////////////////////////////////////////////////////////////////////////
	void ShotBullet();

public:
	EnemyType1Class();
	~EnemyType1Class();

	//////////////////////////////////////////////////////////////////////////////
	//初期化
	//引数:
	//	wave_manager:ウェーブマネージャー
	//	position:敵生成位置
	//戻り値:
	//	true:敵情報のロードに成功
	//	false:敵情報のロードに失敗
	//////////////////////////////////////////////////////////////////////////////
	bool Initialize(WaveManagerClass *wave_manager , POSITION* position);

	//////////////////////////////////////////////////////////////////////////////
	//更新
	//////////////////////////////////////////////////////////////////////////////
	bool Update(PlayerBulletManagerClass *player_bullet_manager);

	//////////////////////////////////////////////////////////////////////////////
	//描画
	//////////////////////////////////////////////////////////////////////////////
	void Render();
};

//////////////////////////////////////////////////////////////////////////////
//敵ステートクラス2
//////////////////////////////////////////////////////////////////////////////
class EnemyType2Class :
	public EnemyStatePatternClass
{
private:
	int BulletType;	//弾タイプ
	
	//////////////////////////////////////////////////////////////////////////////
	//敵情報をロード
	//引数:
	//	wave_manager:ウェーブマネージャー
	//	position:敵生成位置
	//	true:敵情報のロードに成功
	//	false:敵情報のロードに失敗
	//////////////////////////////////////////////////////////////////////////////
	bool LoadEnemyStatus(WaveManagerClass *wave_manager , POSITION* position);
	
	//////////////////////////////////////////////////////////////////////////////
	//敵の位置を移動
	//////////////////////////////////////////////////////////////////////////////
	void MoveObject();
	
	//////////////////////////////////////////////////////////////////////////////
	//敵が弾を撃つ
	//////////////////////////////////////////////////////////////////////////////
	void ShotBullet();

public:
	EnemyType2Class();
	~EnemyType2Class();

	//////////////////////////////////////////////////////////////////////////////
	//初期化
	//引数:
	//	wave_manager:ウェーブマネージャー
	//	position:敵生成位置
	//戻り値:
	//	true:敵情報のロードに成功
	//	false:敵情報のロードに失敗
	//////////////////////////////////////////////////////////////////////////////
	bool Initialize(WaveManagerClass *wave_manager , POSITION* position);

	//////////////////////////////////////////////////////////////////////////////
	//更新
	//////////////////////////////////////////////////////////////////////////////
	bool Update(PlayerBulletManagerClass *player_bullet_manager);

	//////////////////////////////////////////////////////////////////////////////
	//敵が弾を撃つ
	//////////////////////////////////////////////////////////////////////////////
	void Render();
};

//////////////////////////////////////////////////////////////////////////////
//敵コンテキストクラス
//////////////////////////////////////////////////////////////////////////////
class EnemyContextClass
{
private:
	EnemyStatePatternClass* m_EnemyType;	//敵実体

public:
	//敵タイプ
	enum ENEMY_TYPE
	{
		E_ENEMY_TYPE_1 = 1,
		E_ENEMY_TYPE_2
	};

	EnemyContextClass(void);
	~EnemyContextClass(void);

	//////////////////////////////////////////////////////////////////////////////
	//開放
	//////////////////////////////////////////////////////////////////////////////
	void Release();

	//////////////////////////////////////////////////////////////////////////////
	//敵が画面内にいるかチェックする
	//////////////////////////////////////////////////////////////////////////////
	bool CheckEnemyIsInScreen();

	//////////////////////////////////////////////////////////////////////////////
	//初期化
	//引数:
	//	wave_manager:ウェーブマネージャー
	//	enemy_type:的タイプ
	//	position:生成位置
	//戻り値:
	//	true:敵情報のロードに成功
	//	false:敵情報のロードに失敗
	//////////////////////////////////////////////////////////////////////////////
	bool Initiarize(WaveManagerClass *wave_manager , int enemy_type , POSITION* position);

	//////////////////////////////////////////////////////////////////////////////
	//更新
	//////////////////////////////////////////////////////////////////////////////
	bool Update(PlayerBulletManagerClass *player_bullet_manager);

	//////////////////////////////////////////////////////////////////////////////
	//描画
	//////////////////////////////////////////////////////////////////////////////
	void Render();
};