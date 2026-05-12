#pragma once
#include <exception>
template <typename T>
class Container
{
private:
	T* elements;
	unsigned elementCount;
	unsigned capacity;
public:
	Container(unsigned pcapacity = 50)
	{
		capacity = pcapacity;
		elementCount = 0;
		elements = new T[capacity];
	}

	Container(const Container& other)
	{
		capacity = other.capacity;
		elementCount = other.elementCount;
		elements = new T[capacity];
		for (unsigned i = 0; i < elementCount; i++)
			elements[i] = other.elements[i];
	}

	Container& operator=(const Container& other)
	{
		if (this != &other)
		{
			delete[] elements;
			capacity = other.capacity;
			elementCount = other.elementCount;
			elements = new T[capacity];
			for (unsigned i = 0; i < elementCount; i++)
				elements[i] = other.elements[i];
		}
		return *this;
	}

	void add(const T& newElement)
	{
		if (capacity == elementCount)
		{
			if (capacity == 0)
			{
				capacity = 1;
			}
			else
			{
				capacity = capacity * 2;
			}
			T* newList = new T[capacity];
			for (int i = 0; i < elementCount; i++)
			{
				newList[i] = elements[i];
			}
			delete[] elements;
			elements = newList;
		}
		elements[elementCount] = newElement;
		elementCount++;
	}

	unsigned getCapacity() const
	{
		return capacity;
	}

	T& operator[](unsigned index)
	{
		if (index>=elementCount)
		{
			throw std::out_of_range("Túlindexelés a tömbben");
		}
		return elemek[index];
	}

	const T& operator[](unsigned index) const 
	{
		if (index >= meret) {
			throw std::out_of_range("Tulindexeles a taroloban!");
		}
		return elemek[index];
	}

	~Container()
	{
		delete[] elements;
	}
};

