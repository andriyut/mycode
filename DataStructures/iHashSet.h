#pragma once

#include <iostream>
#include "iVector.h"

#define SizeStart 2
#define K 1.5

using std::hash;

template<typename T>
class iHashSet
{
public:
	iHashSet();
	~iHashSet();

	void Add(T item);
	bool Find(T item) const;
	size_t Size() const;

	class Iterator
	{
	public:
		Iterator(iVector<T>* hashset, size_t count);
		T operator *() const;
		void operator ++();
		bool operator !=(const Iterator &item);

	private:
		iVector<T>* hashset;

		size_t indexHash;
		size_t indexBucket;

		size_t count;
	};

	Iterator Begin();
	Iterator End();


private:
	iVector<T>* value;
	size_t size;
	size_t count;
	void reSize();
};

template<typename T>
iHashSet<T>::iHashSet()
{
	size = SizeStart;
	value = new iVector<T>[SizeStart];
	count = 0;
}


template<typename T>
iHashSet<T>::~iHashSet() 
{
	delete[] value;
}

template<typename T>
void iHashSet<T>::Add(T item)
{
	size_t _h = hash<T>()(item) % (size);

	if (_h > size) reSize();

	for (size_t i = 0; i < value[_h].Size(); i++)
		if (value[_h][i] == item) return;

	value[_h].Push_back(item);
	count++;

}

template<typename T>
bool iHashSet<T>::Find(T item) const
{
	size_t _h = hash<T>()(item) % (size);

	if (_h < size)
	{
		for (size_t i = 0; i < value[_h].Size(); i++)
			if (value[_h][i] == item) return true;
	}

	return false;
}

template<typename T>
size_t iHashSet<T>::Size() const
{
	return size;
}

template<typename T>
void iHashSet<T>::reSize()
{
	iVector<T> *_value = value;
	size_t _size = size;

	size *= K;
	value = new iVector<T>[size];

	for (size_t i = 0; i < _size; i++)
		for (size_t j = 0; j < _value[i].Size(); i++)
			Add(_value[i][j]);
}

template<typename T>
iHashSet<T>::Iterator::Iterator(iVector<T>* hashset, size_t count)
{
	this->count = count;
	this->hashset = hashset;
	indexHash = 0;
	indexBucket = 0;

	if (hashset->IsEmpty())
	{
		while (hashset[indexHash].Size() == 0)
			indexHash++;
	}
}


template<typename T>
typename T iHashSet<T>::Iterator::operator*() const
{
	return hashset[indexHash][indexBucket];
}

template<typename T>
typename bool iHashSet<T>::Iterator::operator!=(const Iterator& item)
{
	if (count != item.count) return true;

	return false;
}

template<typename T>
typename void iHashSet<T>::Iterator::operator++()
{
	indexBucket++;
	if (hashset[indexHash].Size() == indexBucket)
	{
		indexBucket = 0;
		indexHash++;
		while (hashset[indexHash].Size() == 0) indexHash++;
	}

	count++;
}

template<typename T>
typename iHashSet<T>::Iterator iHashSet<T>::Begin()
{
	return Iterator(value, 0);
}

template<typename T>
typename iHashSet<T>::Iterator iHashSet<T>::End()
{
	return Iterator(value + size, count);
}



