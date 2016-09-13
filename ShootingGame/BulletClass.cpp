#include "BulletClass.h"

#include <gl\glew.h>
#include <gl\glut.h>

#include "system.h"


BulletClass::BulletClass(void) : ListClass<BulletClass>::ListClass()
{
}


BulletClass::~BulletClass(void)
{
}

void BulletClass::Render()
{
	//�F�ݒ�i�j
	glColor3f(0 , 0 , 1.f);

	//�l�p��`��
	glBegin(GL_POLYGON);

	//�e���_
	for(unsigned int i = 0 ; i < m_Vertex.size() ; i++)
	{
		glVertex2d(Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesX(m_Vertex.m_VertexPosition[i].m_Vector.x) ,
			Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesY(m_Vertex.m_VertexPosition[i].m_Vector.y));
	}

	glEnd();
}