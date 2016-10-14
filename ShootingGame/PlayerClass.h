#pragma once
#include "BoxClass.h"
#include "InputClass.h"
#include <string>

class ShoulderPartsClass;
class BackPartsClass;
class HipPartsClass;

class PlayerClass :
	public BoxClass , public InputClass
{
private:
	ShoulderPartsClass *m_Pointer_to_Shoulder_L;
	ShoulderPartsClass *m_Pointer_to_Shoulder_R;
	BackPartsClass *m_Pointer_to_Back;
	HipPartsClass *m_Pointer_to_Hip;
	double m_PLAYER_X_SPEED;
	double m_PLAYER_Y_SPEED;

	bool m_ShotFlag;

	bool LoadPlayerStatus(std::string file_name);

	void CheckInput();
	void PlayerCanNotOverScreen();
	void MoveObject();
	
	bool InitializeChild();
	bool UpdateChild();
	void RenderChild();

public:

	PlayerClass(void);
	~PlayerClass(void);

	//////////////////////////////////////////////////////////////////////////////
	//�T��:
	//	�v���C���[�̑��x��ݒ肷��
	//����:
	//	x:�������x
	//	y:�c�����x
	//////////////////////////////////////////////////////////////////////////////
	void SetPlayerSpeed(double x , double y);

	//////////////////////////////////////////////////////////////////////////////
	//�T��:
	//	������
	//����:
	//	*position:�ʒu
	//	*velocity:���x
	//	*accelaration:�����x
	//	*semi_long_vector:�������x�N�g��
	//	*semi_short_vector:���Z���x�N�g��
	//	*shoulder_l:�����p�[�c�ւ̃|�C���^
	//	*shoulder_r:�E���p�[�c�ւ̃|�C���^
	//	*back:�w���p�[�c�ւ̃|�C���^
	//	*hip:���p�[�c�ւ̃|�C���^
	//	flag:�t���O
	//�߂�l:
	//	true:�Ƃ肠����true��Ԃ�
	//////////////////////////////////////////////////////////////////////////////
	bool Initialize(std::string file_name , ShoulderPartsClass* shoulder_l , ShoulderPartsClass* shoulder_r , BackPartsClass* back , HipPartsClass* hip , bool flag = true);

	bool Update();

	//////////////////////////////////////////////////////////////////////////////
	//�T��:
	//	�`��
	//////////////////////////////////////////////////////////////////////////////
	void Render();
};