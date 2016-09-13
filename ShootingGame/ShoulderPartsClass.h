#pragma once
#include "PlayerClass.h"
#include "BulletManagerClass.h"

class ShoulderPartsClass :
	public BoxClass
{
private:
	THREE_DIMENSION_VECTOR m_ForwardVector;

	POSITION m_ShotPosition;
	double m_BarrelRange;
	VELOCITY m_ShotVelocity;
	ACCELARATION m_ShotAccelaration;
	THREE_DIMENSION_VECTOR m_ShotSemiLongVector;
	THREE_DIMENSION_VECTOR m_ShotSemiShortVector;
	double m_ShotSpeed;

	PlayerClass *m_Pointer_to_Parent;

	virtual bool Initialize(POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , THREE_DIMENSION_VECTOR* semi_long_vector , THREE_DIMENSION_VECTOR* semi_short_vector , bool flag = true) final {return true ;}
	virtual bool Update() final{return true;}
	virtual void Render() final{}

public:
	ShoulderPartsClass(void);
	~ShoulderPartsClass(void);

	void SetShotStatus(double barrel_range , VELOCITY* velocity , double shot_speed , ACCELARATION* accelaration , THREE_DIMENSION_VECTOR* shot_semi_long_vector , THREE_DIMENSION_VECTOR* shot_semi_short_vector);

	POSITION GetShotPosition();
	VELOCITY GetShotVelocity();
	ACCELARATION GetShotAccelaration();
	THREE_DIMENSION_VECTOR GetShotSemiLongVector();
	THREE_DIMENSION_VECTOR GetShotSemiShortVector();

	bool Initialize(POSITION* local_position , VELOCITY* local_velocity , ACCELARATION* local_accelaration , THREE_DIMENSION_VECTOR* semi_long_vector , THREE_DIMENSION_VECTOR* semi_short_vector , PlayerClass* player , bool flag = true);
	bool Update(bool shot_flag);
	void Render(POSITION* world_position);
};

extern ShoulderPartsClass TestShoulderL;
extern ShoulderPartsClass TestShoulderR;