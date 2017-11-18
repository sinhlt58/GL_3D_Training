#pragma once

template <typename T>
class Singleton
{
public:
	static T* GetInstance();
	static void CreateInstance();
	static void DestroyInstance();
private:
	Singleton();
	~Singleton();
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);

	static T* m_instance;
};

template <typename T>
T* Singleton<T>::m_instance = nullptr;

template <typename T>
T* Singleton<T>::GetInstance()
{
	return m_instance;
}

template <typename T>
void Singleton<T>::CreateInstance()
{
	if (!m_instance)
	{
		m_instance = new T();
	}
}

template <typename T>
void Singleton<T>::DestroyInstance()
{
	if (m_instance)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}
