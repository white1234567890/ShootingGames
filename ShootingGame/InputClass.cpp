#include "InputClass.h"

#include <gl\glew.h>
#include <gl\glut.h>

//コンストラクタ
InputClass::InputClass(void)
{
	m_InputKeyFlag = 0;
}

//デストラクタ
InputClass::~InputClass(void)
{
}

void InputClass::KeyBoardDown(unsigned char key)
{

}

void InputClass::KeyBoardUp(unsigned char key)
{
}

void InputClass::SpecialKeyBoardDown(int key)
{
	if(key == GLUT_KEY_UP) m_InputKeyFlag |= E_UP_ARROW_KEY;
	if(key == GLUT_KEY_LEFT) m_InputKeyFlag |= E_LEFT_ARROW_KEY;
	if(key == GLUT_KEY_RIGHT) m_InputKeyFlag |= E_RIGHT_ARROW_KEY;
	if(key == GLUT_KEY_DOWN) m_InputKeyFlag |= E_DOWN_ARROW_KEY;
}

void InputClass::SpecialKeyBoardUp(int key)
{

	if(key == GLUT_KEY_UP) m_InputKeyFlag &= ~E_UP_ARROW_KEY;
	if(key == GLUT_KEY_LEFT) m_InputKeyFlag &= ~E_LEFT_ARROW_KEY;
	if(key == GLUT_KEY_RIGHT) m_InputKeyFlag &= ~E_RIGHT_ARROW_KEY;
	if(key == GLUT_KEY_DOWN) m_InputKeyFlag &= ~E_DOWN_ARROW_KEY;
}