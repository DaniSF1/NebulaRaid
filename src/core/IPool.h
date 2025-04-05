#pragma once
#include <vector>

template <typename T>
class IPool
{
public:
	virtual T* getObject() = 0;
	virtual void releaseObject(T* obj) = 0;
	virtual ~IPool() = default;
};