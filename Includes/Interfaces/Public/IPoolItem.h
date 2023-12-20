#pragma once

class IPoolItem
{
public:

	virtual ~IPoolItem() = default;

	virtual void Enable() = 0;

	virtual void Disable() = 0;
};