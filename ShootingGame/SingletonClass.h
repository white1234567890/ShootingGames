#pragma once

template<class T>
class SingletonClass
{
private:
	void operator = (const SingletonClass& obj) {}	//代入演算子の禁止
	SingletonClass(const SingletonClass &obj) {}	//コピーコンストラクタの禁止
protected:
	SingletonClass() {}	//外部でのインスタンス作成は禁止

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

