#pragma once

#include <stack>
#include <memory>
#include "IPoolItem.h"

template<typename T>
using sptr = std::shared_ptr<T>;

class ObjectPool
{
	std::stack<sptr<IPoolItem>> pool;
	
public:

	inline ObjectPool()
	{
		pool = std::stack<sptr<IPoolItem>>();
	}
	
	inline ~ObjectPool() = default;
	
	inline int Count() { return pool.size(); }

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

	inline void Put(sptr<IPoolItem> _toAdd)
	{
		if (!_toAdd)
			return;

		pool.push(std::move(_toAdd));
	}
};