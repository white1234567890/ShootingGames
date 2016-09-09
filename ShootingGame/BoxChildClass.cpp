#include "BoxChildClass.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <gl\glew.h>
#include <gl\glut.h>

#include "system.h"


BoxChildClass::BoxChildClass(void)
{
}


BoxChildClass::~BoxChildClass(void)
{
}

//////////////////////////////////////////////////////////////////////////////
//publicΦ
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//Tͺ:
//	ϊ»
//ψ:
//	*position:Κu
//	*velocity:¬x
//	*accelaration:Α¬x
//	*semi_long_vector:Ό·²xNg
//	*semi_short_vector:ΌZ²xNg
//	flag:tO
//ίθl:
//	true:Ζθ ¦ΈtrueπΤ·
//////////////////////////////////////////////////////////////////////////////
bool BoxChildClass::Initialize(POSITION* position , VELOCITY* velocity , ACCELARATION* accelaration , THREE_DIMENSION_VECTOR* semi_long_vector , THREE_DIMENSION_VECTOR* semi_short_vector , bool flag)
{
	m_LocalPosition = *position;
	m_LocalVelocity = *velocity;
	m_LocalAccelaration = *accelaration;
	m_SemiLongVector = *semi_long_vector;
	m_SemiShortVector = *semi_short_vector;

	m_SemiLongAxis = m_SemiLongVector.Magnitude();
	m_SemiShortAxis = m_SemiShortVector.Magnitude();

	SetVertex();

	return true;
}

//////////////////////////////////////////////////////////////////////////////
//Tͺ:
//	XV
//////////////////////////////////////////////////////////////////////////////
bool BoxChildClass::Update()
{
	SetVertex();
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//Tͺ:
//	`ζ
//////////////////////////////////////////////////////////////////////////////
void BoxChildClass::Render()
{
		//FέθiΤj
	glColor3f(1.f , 0 , 0);

	//lpπ`ζ
	glBegin(GL_POLYGON);

	//eΈ_
	for(unsigned int i = 0 ; i < m_Vertex.size() ; i++)
	{
		glVertex2d(Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesX(m_Vertex.m_VertexPosition[i].m_Vector.x) ,
			Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesY(m_Vertex.m_VertexPosition[i].m_Vector.y));
	}

	glEnd();
}