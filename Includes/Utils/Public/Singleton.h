#pragma once

#include <memory>
#include <iostream>

/// <summary>
/// Singleton pattern class.
/// Inherits from this class in order to use Singleton pattern and have an unique instance.
/// </summary>
/// <typeparam name="TSingleton">Class that inherits from Singleton pattern.</typeparam>
template<class TSingleton>
class Singleton
{
protected:

	static TSingleton* instance;

public:

#pragma region Constructors/Destructor
	Singleton() = default;
	Singleton(const Singleton&) = delete;
	virtual ~Singleton() = default;
#pragma endregion

	Singleton& operator=(const Singleton&) = delete;

	inline static TSingleton* GetInstance()
	{
		if (!instance)
			instance = new TSingleton();

		return instance;
	}
};

template<typename TSingleton>
TSingleton* Singleton<TSingleton>::instance = nullptr;