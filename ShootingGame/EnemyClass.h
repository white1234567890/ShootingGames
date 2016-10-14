#pragma once
#include "BoxClass.h"
#include "TimerClass.h"

//使用クラス宣言
class WaveManagerClass;

class EnemyStatePatternClass :
	public BoxClass , public TimerClass
{
protected:
	bool m_ShotFlag;
	int m_ShotCount;

	virtual bool LoadEnemyStatus(WaveManagerClass *wave_manager , POSITION* position) = 0;
	virtual void MoveObject() = 0;
	virtual void ShotBullet() = 0;

public:
	EnemyStatePatternClass();
	~EnemyStatePatternClass();
	
	virtual bool Initialize(WaveManagerClass *wave_manager , POSITION* position) = 0;
	virtual bool Update() = 0;
	virtual void Render() = 0;
};

class EnemyType1Class :
	public EnemyStatePatternClass
{
private:
	bool LoadEnemyStatus(WaveManagerClass *wave_manager , POSITION* position);
	void MoveObject();
	void ShotBullet();

public:
	EnemyType1Class();
	~EnemyType1Class();

	bool Initialize(WaveManagerClass *wave_manager , POSITION* position);
	bool Update();
	void Render();
};

class EnemyType2Class :
	public EnemyStatePatternClass
{
private:
	bool LoadEnemyStatus(WaveManagerClass *wave_manager , POSITION* position);
	void MoveObject();
	void ShotBullet();

public:
	EnemyType2Class();
	~EnemyType2Class();

	bool Initialize(WaveManagerClass *wave_manager , POSITION* position);
	bool Update();
	void Render();
};


class EnemyClass
{
private:
	EnemyStatePatternClass* m_EnemyType;

public:
	enum ENEMY_TYPE
	{
		E_ENEMY_TYPE_1 = 1,
		E_ENEMY_TYPE_2
	};

	EnemyClass(void);
	~EnemyClass(void);

	void Release();
	bool CheckEnemyIsInScreen();

	bool Initiarize(WaveManagerClass *wave_manager , int enemy_type , POSITION* position);
	bool Update();
	void Render();
};