#pragma once
#include "PlayerClass.h"

class ShoulderPartsClass :
	public BoxClass
{
private:
	PlayerClass *m_Pointer_to_Parent;
	virtual bool Initialize(POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , THREE_DIMENSION_VECTOR* semi_long_vector , THREE_DIMENSION_VECTOR* semi_short_vector , bool flag = true) final {return true ;}
	virtual void Render() final{}

public:
	ShoulderPartsClass(void);
	~ShoulderPartsClass(void);

	bool Initialize(POSITION* local_position , VELOCITY* local_velocity , ACCELARATION* local_accelaration , THREE_DIMENSION_VECTOR* semi_long_vector , THREE_DIMENSION_VECTOR* semi_short_vector , PlayerClass* player , bool flag = true);
	void Render(POSITION* world_position);
};

extern ShoulderPartsClass TestShoulderL;
extern ShoulderPartsClass TestShoulderR;