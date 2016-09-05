#pragma once
#include "boxclass.h"

class GroundClass :
	public BoxClass
{
private:
	THREE_DIMENSION_VECTOR m_NomalVector;	//法線ベクトル

public:
	static const double GROUND_HEIGHT;

	GroundClass(void);
	~GroundClass(void);

	bool Initialize(POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , THREE_DIMENSION_VECTOR* semi_long_vector , THREE_DIMENSION_VECTOR* semi_short_vector , bool flag = true);
};

extern GroundClass Ground;