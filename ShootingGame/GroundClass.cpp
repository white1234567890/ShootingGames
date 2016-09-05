#include "GroundClass.h"

//íËêîêÈåæ
const double GroundClass::GROUND_HEIGHT = 20;

GroundClass Ground;

GroundClass::GroundClass(void)
{
	for(int i = 0 ; i < 4 ; i++)
	{
		m_Vertex.m_VertexPosition.push_back(POSITION());
	}
	m_Accelaration = ACCELARATION();
	m_Velocity = VELOCITY();
	m_Coefficient_of_Restitution = 0;
	m_Flag = true;
	m_GravityVelocity = THREE_DIMENSION_VECTOR();
	m_SemiLongVector.Set(SCREEN_WIDTH , 0 , 0);
	m_SemiShortVector.Set(0 , 20 , 0);
	m_SemiLongAxis = m_SemiLongVector.Magnitude();
	m_SemiShortAxis = m_SemiShortVector.Magnitude();
	m_Position.m_Vector.Set(SCREEN_WIDTH / 2 , SCREEN_HEIGHT , 0);
	m_NomalVector .Set(0 , m_SemiLongVector.y + m_SemiShortVector.y);
	SetVertex();
}


GroundClass::~GroundClass(void)
{
	std::vector<POSITION> Nullvector;
	m_Vertex.m_VertexPosition.swap(Nullvector);
}

bool GroundClass::Initialize(POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , THREE_DIMENSION_VECTOR* semi_long_vector , THREE_DIMENSION_VECTOR* semi_short_vector , bool flag)
{
	return true;
}