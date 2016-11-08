#pragma once

template<class T>
class SingletonClass
{
private:
	SingletonClass& operator = (const SingletonClass& obj) {}	//������Z�q�̋֎~
	SingletonClass(const T& obj) {}	//�R�s�[�R���X�g���N�^�̋֎~
	static T* instance;

protected:
	SingletonClass() {}	//�O���ł̃C���X�^���X�쐬�͋֎~
	virtual ~SingletonClass(void) {};

public:

	//////////////////////////////////////////////////////////////////////////////
	//�C���X�^���X����
	//////////////////////////////////////////////////////////////////////////////
	static T* GetInstance()
	{
		//���̂�null�|�C���^�������ĂȂ�������
		if(instance != nullptr)
		{
			//���̂���x����
			delete instance;
		}
		
		//���̂�V������������
		instance = new T();

		//���̃|�C���^��Ԃ�
		return instance;
	}

	//////////////////////////////////////////////////////////////////////////////
	//�i�������𖳑ʂɂ��Ȃ����߂Ɂj�C���X�^���X��j�󂷂�
	//////////////////////////////////////////////////////////////////////////////
	static T* Destroy()
	{
		//���̂�null�|�C���^�������ĂȂ�������
		if(instance != nullptr)
		{
			//���̂�����
			delete instance;
		}

		//null�|�C���^��˂�����
		instance = nullptr;

		//null�|�C���^��Ԃ�
		return instance;
	}
};

//�Ƃ肠����null�|�C���^�ŏ���������
template<typename T>
T* SingletonClass<T>::instance = nullptr;