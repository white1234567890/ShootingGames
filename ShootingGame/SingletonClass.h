#pragma once

template<class T>
class SingletonClass
{
private:
	void operator = (const SingletonClass& obj) {}	//������Z�q�̋֎~
	SingletonClass(const SingletonClass &obj) {}	//�R�s�[�R���X�g���N�^�̋֎~
protected:
	SingletonClass() {}	//�O���ł̃C���X�^���X�쐬�͋֎~

public:
	virtual ~SingletonClass(void) {};

	static T* GetInstance()
	{
		T *pointer = new T;
		static T *instance;
		instance = pointer;
		delete pointer;
		return instance;
	}
};

