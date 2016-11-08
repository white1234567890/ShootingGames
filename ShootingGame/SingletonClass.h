#pragma once

template<class T>
class SingletonClass
{
private:
	SingletonClass& operator = (const SingletonClass& obj) {}	//代入演算子の禁止
	SingletonClass(const T& obj) {}	//コピーコンストラクタの禁止
	static T* instance;

protected:
	SingletonClass() {}	//外部でのインスタンス作成は禁止
	virtual ~SingletonClass(void) {};

public:

	//////////////////////////////////////////////////////////////////////////////
	//インスタンス生成
	//////////////////////////////////////////////////////////////////////////////
	static T* GetInstance()
	{
		//実体にnullポインタが入ってなかったら
		if(instance != nullptr)
		{
			//実体を一度消す
			delete instance;
		}
		
		//実体を新しく生成する
		instance = new T();

		//そのポインタを返す
		return instance;
	}

	//////////////////////////////////////////////////////////////////////////////
	//（メモリを無駄にしないために）インスタンスを破壊する
	//////////////////////////////////////////////////////////////////////////////
	static T* Destroy()
	{
		//実体にnullポインタが入ってなかったら
		if(instance != nullptr)
		{
			//実体を消す
			delete instance;
		}

		//nullポインタを突っ込む
		instance = nullptr;

		//nullポインタを返す
		return instance;
	}
};

//とりあえずnullポインタで初期化する
template<typename T>
T* SingletonClass<T>::instance = nullptr;