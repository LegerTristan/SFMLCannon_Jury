#pragma once

#include <stack>
#include <memory>
#include "IPoolItem.h"

template<typename T>
using sptr = std::shared_ptr<T>;

/// <summary>
/// Implementation of the ObjectPooling pattern.
/// Any objects that we want to store inside this container needs to implement IPoolItem.
/// Items are stored as shared_pointer.
/// </summary>
class ObjectPool
{
	std::stack<sptr<IPoolItem>> pool;
	
public:

#pragma region Constructor/Destructor
	inline ObjectPool() : pool(std::stack<sptr<IPoolItem>>()){}

	inline ~ObjectPool() = default;
#pragma endregion

#pragma region Methods
	inline int Count() { return pool.size(); }

	/// <summary>
	/// Retrieve a reference to an IPoolItem if it exists.
	/// </summary>
	/// <returns>Valid reference if it exists, else nullptr.</returns>
	inline sptr<IPoolItem> Retrieve()
	{
		const size_t _size = pool.size();
		if (_size != 0)
		{
			sptr<IPoolItem> _retrieved = pool.top();
			pool.pop();
			return _retrieved;
		}
	
		return nullptr;
	}

	/// <summary>
	/// Add an instance that implements IPoolItem to the ObjectPool
	/// </summary>
	/// <param name="_toAdd">Instance to add.</param>
	inline void Put(sptr<IPoolItem> _toAdd)
	{
		if (!_toAdd)
			return;

		pool.push(std::move(_toAdd));
	}
#pragma endregion
};