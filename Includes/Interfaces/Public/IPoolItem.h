#pragma once

/// <summary>
/// Interface class that represents an item that can be kept inside a pool container.
/// </summary>
class IPoolItem
{
public:

	virtual ~IPoolItem() = default;

	virtual void Enable() = 0;

	virtual void Disable() = 0;
};