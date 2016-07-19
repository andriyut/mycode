#include "iHashSet.h"
#pragma once


#define CapacityStart 2
#define K 1.5

template<typename T>
class iVector
{
public:
	iVector();
	~iVector();

	void Push_back(T item);
	void Pop_back();
	T& operator[] (size_t index);
	const T& operator[] (size_t index) const;
	void Insert(T item, size_t index);
	void Clear();
	void ReSize();
	const size_t Size() const;
	const bool IsEmpty() const;

	class Iterator
	{
	public:
		Iterator(T* vector);

		T& operator*();
		Iterator& operator ++();
		bool operator !=(const Iterator &item);

	private:
		T* vector;
	};

	class ConstIterator
	{
	public:
		ConstIterator(T* vector);

		const T& operator*() const;
		ConstIterator& operator ++();
		bool operator !=(const ConstIterator &item);

	private:
		T* vector;
	};

	Iterator Begin();
	Iterator End();

	ConstIterator ConstBegin();
	ConstIterator ConstEnd();

private:
	T* value;
	size_t capacity;
	size_t size;
};

template<typename T>
inline iVector<T>::iVector()
{
	capacity = CapacityStart;
	size = 0;
	value = new T[capacity];
}

template<typename T>
inline iVector<T>::~iVector()
{
	delete[] value;
}

template<typename T>
void iVector<T>::Push_back(T item)
{
	if (size == capacity)
	{
		ReSize();
		Push_back(item);
	}
	else
	{
		value[size++] = item;
	}
}

template<typename T>
inline void iVector<T>::Pop_back()
{
	if (size > 0) size--;
}

template<typename T>
T& iVector<T>::operator[] (size_t index)
{
	return value[index];
}

template<typename T>
const T& iVector<T>::operator[] (size_t index) const
{
	return value[index];
}


template<typename T>
inline void iVector<T>::Clear()
{
	delete[] value;
	capacity = CapacityStart;
	value = new T[CapacityStart];
	size = 0;
}

template<typename T>
void iVector<T>::Insert(T item, size_t index)
{
	if (size == capacity)
	{
		ReSize();
		Insert(item, index);
	}
	else
	{
		T* _value = value;
		size_t _size = size;

		value = new T[capacity];
		size = 0;

		for (size_t i = 0; i < index; i++)
			Push_back(_value[i]);

		Push_back(item);

		for (size_t i = index + 1; i < _size; i++)
			Push_back(_value[i]);

		delete[] _value;

	}
}


template<typename T>
inline void iVector<T>::ReSize()
{
	capacity *= K;
	T *_value = value;
	size_t _size = size;

	value = new T[capacity];
	size = 0;

	for (size_t i = 0; i < _size; i++)
		Push_back(_value[i]);

	delete[] _value;

}

template<typename T>
inline const size_t iVector<T>::Size() const
{
	return size;
}

template<typename T>
inline const bool iVector<T>::IsEmpty() const
{
	return	size > 0 ? true : false;
}

template<typename T>
iVector<T>::Iterator::Iterator(T* vector)
{
	this->vector = vector;
}

template<typename T>
inline T & iVector<T>::Iterator::operator*()
{
	return *vector;
}

template<typename T>
typename iVector<T>::Iterator& iVector<T>::Iterator::operator++()
{
	vector++;
	return *this;
}




template<typename T>
inline bool iVector<T>::Iterator::operator!=(const Iterator & item)
{
	return vector != item.vector;
}



template<typename T>
typename iVector<T>::Iterator iVector<T>::Begin()
{
	return Iterator(value);
}

template<typename T>
typename iVector<T>::Iterator iVector<T>::End()
{
	return Iterator(value+size);
}



////

template<typename T>
typename const T & iVector<T>::ConstIterator::operator*() const
{
	return *vector;
}

template<typename T>
iVector<T>::ConstIterator::ConstIterator(T* vector)
{
	this->vector = vector;
}


template<typename T>
typename iVector<T>::ConstIterator& iVector<T>::ConstIterator::operator++()
{
	vector++;
	return *this;
}




template<typename T>
bool iVector<T>::ConstIterator::operator!=(const ConstIterator & item)
{
	return vector != item.vector;
}



template<typename T>
typename iVector<T>::ConstIterator iVector<T>::ConstBegin()
{
	return ConstIterator(value);
}

template<typename T>
typename iVector<T>::ConstIterator iVector<T>::ConstEnd()
{
	return ConstIterator(value + size);
}
