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
	static T* GetInstance()
	{
		if(instance != NULL)
		{
			delete instance;
		}
		
		instance = new T();

		return instance;
	}
};

template<typename T>
T* SingletonClass<T>::instance = NULL;