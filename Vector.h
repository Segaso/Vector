/*  Author: Leonard A. Kelley III
//	Class: CSI 240 - 04
//	Description:
//		The purpose of this class container is to explore how std::vector works.
//		std::vector is a lot better and industry tested, so it will always be preferable.
//		I reinvented the wheel of education purposes, use std::vector in any real application.
//	Certification of Authenticity:
//	I certify that this assignment is entirely my own work.
*/

#ifndef VECTOR_H
#define VECTOR_H
 
#include <algorithm>  
#include <initializer_list>
#include <stdexcept>

template <class T>
class vector
{
public:
	//Iterator Stuff (STL usability and range based for loops)
	typedef T* iterator;
	typedef const T* const_iterator;

	iterator begin() { return Values; };
	iterator end() { return &Values[Size]; };
	const_iterator cbegin() const { return Values; };
	const_iterator cend() const { return &Values[Size]; };

	//Generic functions for inserting/manipulating the vector
	void insert(const int, const T&);
	void push_back(const T&);
	void push_front(const T&);
	bool reserve(const int);

	//Random Access
	T& operator[](const int);

	//Setting vector to other vectors/init lists
	void operator=(std::initializer_list<T>&& other);
	void operator=(const vector<T>& other);

	//Accessors
	int size() const { return Size; };
	int capacity() const { return Capacity;};

	//Constructors/Destructor
	vector() : vector(1, 0) {};
	vector(const int capacity) : vector(capacity, 0) {};
	vector(const vector<T>& other);
	vector(std::initializer_list<T>&&);
	~vector() { delete[] Values; };

private:
	T* Values;
	int Capacity, Size;

	void reserve();

	//Delegated Constructor
	vector(const int, const int);
};

#include "Vector.inl"
#endif