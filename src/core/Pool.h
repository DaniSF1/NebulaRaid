#pragma once
#include "IPool.h"
#include <memory>
#include <algorithm>

template <typename T>
class Pool : public IPool<T>
{
public:
	Pool() = default;
	Pool(size_t size)
	{
		objects.reserve(size);
		for (size_t i = 0; i < size; ++i)
		{
			objects.push_back(std::make_unique<T>());
			availableObjects.push_back(objects.back().get());
		}
	}

	~Pool() override = default;

	T* getObject() override
	{
		if (availableObjects.empty()) return nullptr;

		T* obj = availableObjects.back();
		availableObjects.pop_back();

		if (std::find(activeObjects.begin(), activeObjects.end(), obj) == activeObjects.end())
		{
			activeObjects.push_back(obj);
		}

		return obj;
	}

	void releaseObject(T* obj) override
	{
		auto it = std::find(activeObjects.begin(), activeObjects.end(), obj);
		if (it != activeObjects.end())
		{
			activeObjects.erase(it);
			availableObjects.push_back(obj);
		}
	}

	void addObject(std::unique_ptr<T> obj)
	{
		availableObjects.push_back(obj.get());
		objects.push_back(std::move(obj));
	}

	int getSize()
	{
		return objects.size();
	}

	const std::vector<T*>& getAllActiveObjects() const
	{
		return activeObjects;
	}

	const std::vector<T*>& getAvailableObjects() const
	{
		return availableObjects;
	}

private:
	std::vector<std::unique_ptr<T>> objects;
	std::vector<T*> availableObjects;
	std::vector<T*> activeObjects;
};

