#pragma once
#include <stdexcept>
template <typename T>
class Container						//Általánosítot dinamikus tömb, ez tárolja a szobákat, vendégeket és foglalásokat
{
private:
	T* elements;					//elemek tömbjére mutató
	unsigned elementCount;			//elemszám	
	unsigned capacity;				//maximális kapacitás
public:
	//Konstruktorok
	Container(unsigned pcapacity = 5)
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

	//értékadó operátor
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

	//új adatot ad hozzá a tömbhöz
	void add(const T& newElement)
	{
		if (capacity == elementCount)					//Ha megtelt a tömb akkor megnövelem a méretét a duplájára
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
			for (unsigned i = 0; i < elementCount; i++)
			{
				newList[i] = elements[i];
			}
			delete[] elements;
			elements = newList;
		}
		elements[elementCount] = newElement;
		elementCount++;
	}

	//Getterek
	unsigned getCapacity() const
	{
		return capacity;
	}
	unsigned getElementCount() const
	{
		return elementCount;
	}

	T& operator[](unsigned index)
	{
		if (index >= elementCount) 
		{
			throw std::out_of_range("Túlindexelés a tömbben");
		}
		return elements[index]; 
	}

	const T& operator[](unsigned index) const
	{
		if (index >= elementCount) 
		{ 
			throw std::out_of_range("Túlindexelés a tömbben");
		}
		return elements[index];
	}

	~Container()
	{
		delete[] elements;
	}
};

