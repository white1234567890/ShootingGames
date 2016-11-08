#pragma once
#include "boxclass.h"

class BulletStatePatternClass :
	public BoxClass
{
public:
	BulletStatePatternClass();
	~BulletStatePatternClass();

	//�X�V
	virtual bool Update() = 0;

	//�`��
	virtual void Render() = 0;
};



class PlayerNormalBulletStateClass :
	public BulletStatePatternClass
{
public:
	PlayerNormalBulletStateClass();
	~PlayerNormalBulletStateClass();

	//�X�V
	bool Update();

	//�`��
	void Render();
};

class EnemyNormalBulletStateClass :
	public BulletStatePatternClass
{
public:
	EnemyNormalBulletStateClass();
	~EnemyNormalBulletStateClass();

	//�X�V
	bool Update();

	//�`��
	void Render();
};


class BulletClass
{
private:
	BulletStatePatternClass *m_BulletEntity;

public:
	enum BULLET_TYPE
	{
		E_PLAYER_NORMAL,
		E_PLAYER_WIDE,
		E_PLAYER_HOMING,
		E_PLAYER_LASER,
		E_PLAYER_PENETRATION,
		E_ENEMY_TYPE1,

	};

	BulletClass(void);
	~BulletClass(void);

	//�ʒu�����
	POSITION GetPosition();

	//������
	bool Initialize(int bullet_type , POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , THREE_DIMENSIONAL_VECTOR* semi_long_vector , THREE_DIMENSIONAL_VECTOR* semi_short_vector);

	//�X�V
	bool Update();

	//�`��
	void Render();
};