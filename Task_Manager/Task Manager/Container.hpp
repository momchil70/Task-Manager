#include <iostream>
#pragma once

template <class T>
class Container
{
private:
	T** data = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	void resize(size_t newCap);
	void moveFrom(Container<T>&& other);
	void copyFrom(const Container<T>& other);
	void free();

	
public:
	Container();

	Container(const Container<T>& other);
	Container(Container<T>&& other) noexcept;

	Container<T>& operator=(const Container<T>&);
	Container<T>& operator=(Container<T>&&) noexcept;

	~Container() noexcept;
	void add(const T& elem);
	void add(T* elem);

	void erase(unsigned index);
	void eraseWithoutDelete(unsigned index);

	const T* operator[](unsigned) const;
	T* operator[](unsigned);
	unsigned getSize() const;
};

template<class T>
Container<T>::Container(const Container<T>& other)
{
	copyFrom(other);
}

template<class T>
Container<T>::Container(Container<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

template<class T>
Container<T>& Container<T>::operator=(const Container<T>& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

template<class T>
Container<T>& Container<T>::operator=(Container<T>&& other) noexcept
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template<class T>
Container<T>::~Container() noexcept
{
	free();
}

template<class T>
Container<T>::Container()
{
	capacity = 8;
	data = new T * [capacity] {nullptr};
	size = 0;
}

template<class T>
void Container<T>::moveFrom(Container<T>&& other)
{
	data = other.data;
	other.data = nullptr;

	size = other.size;
	capacity = other.capacity;

	other.size = other.capacity = 0;
}

template<class T>
void Container<T>::copyFrom(const Container<T>& other)
{
	data = new T * [other.capacity];

	for (int i = 0; i < other.size; i++) {
		data[i] = other.data[i]->clone();
	}

	size = other.size;
	capacity = other.capacity;
}

template<class T>
void Container<T>::free()
{
	for (int i = 0; i < size; i++) {
		delete data[i];
	}

	delete[] data;
}

template<class T>
void Container<T>::add(T* elem)
{
	if (size == capacity) {
		resize(capacity * 2);
	}
	data[size++] = elem;
}

template<class T>
void Container<T>::add(const T& elem)
{
	T* cloned = elem.clone();
	add(cloned);
}

template<class T>
void Container<T>::erase(unsigned index)
{
	if (index >= size)
		throw std::out_of_range("Index out of range");

	delete data[index];

	for (int i = index; i < size - 1; i++)
		data[i] = std::move(data[i + 1]);

	size--;
	
	if (size == capacity / 4)
		resize(capacity / 2);
}

template<class T>
void Container<T>::eraseWithoutDelete(unsigned index)
{
	if (index >= size)
		throw std::out_of_range("Index out of range");
	for (int i = index; i < size - 1; i++)
		data[i] = std::move(data[i + 1]);

	size--;
	if (size == capacity / 4)
		resize(capacity / 2);
}

template<class T>
void Container<T>::resize(size_t newCap)
{
	T** temp = new T * [newCap];
	for (int i = 0; i < size; i++) {
		temp[i] = data[i];
	}

	delete[] data;
	data = temp;
	capacity = newCap;
}

template<class T>
unsigned Container<T>::getSize() const
{
	return size;
}

template<class T>
const T* Container<T>::operator[](unsigned ind) const
{
	return data[ind];
}

template<class T>
T* Container<T>::operator[](unsigned ind)
{
	return data[ind];
}
