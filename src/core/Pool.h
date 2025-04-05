#pragma once
#include "IPool.h"

template <typename T>
class Pool : public IPool<T>
{
public:
	Pool(size_t size)
	{
		objects.resize(size);
		for (auto& obj : objects)
		{
			obj = new T();
			availableObjects.push_back(obj);
		}
	}

	~Pool()
	{
		for (T* obj : objects)
		{
			delete obj;
		}
	}

	T* getObject() override
	{
		if (availableObjects.empty()) return nullptr;

		T* obj = availableObjects.back();
		availableObjects.pop_back();

		activeObjects.push_back(obj);

		return obj;
	}

	void releaseObject(T* obj) override
	{
		auto it = std::find(activeObjects.begin(), activeObjects.end(), obj);
		if (it != activeObjects.end())
		{
			activeObjects.erase(it);
		}

		availableObjects.push_back(obj);
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
	std::vector<T*> objects;
	std::vector<T*> availableObjects;
	std::vector<T*> activeObjects;
};

