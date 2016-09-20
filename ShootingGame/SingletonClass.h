#pragma once

template<class T>
class SingletonClass
{
private:
	void operator = (const SingletonClass& obj) {}	//������Z�q�̋֎~
	SingletonClass(const SingletonClass &obj) {}	//�R�s�[�R���X�g���N�^�̋֎~

protected:
	SingletonClass() {}	//�O���ł̃C���X�^���X�쐬�͋֎~
	virtual ~SingletonClass(void) {};

public:
	static T* GetInstance()
	{
		static T* instance;
		return instance;
	}
};

