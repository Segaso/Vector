#include "Vector.h"

//Purpose: Delegated Constructor. Each consturctor bases itself off this 
//constructor.
template <class T>
vector<T>::vector(const int C, const int S) : Capacity(C), Size(S) {
	if(Capacity < 0) {
		throw std::length_error("vector cannot have a negative capacity");
	}
	else {
		Values = new T[Capacity];
	}
}

//Purpose: Copy Constructor.
template<class T>
vector<T>::vector(const vector<T>& other) : vector(other.capacity(), other.size()) {
	std::copy(other.cbegin(), other.cend(), Values);
}

//Purpose: Accepts initializer lists during consturctions (basically arrays on the fly)
//Example: vector<int> test = {1, 2, 3, 4, 5}; 
template <class T>
vector<T>::vector(std::initializer_list<T>&& list) : vector(list.size(), list.size()) {
	std::move(list.begin(), list.end(), Values);
}

//Purpose: Solves another copying issue (ptrs pointing to same point in memory)
template <class T>
void vector<T>::operator=(const vector<T>& other) {
	Size = other.size();
	Capacity = other.capacity();
	
	delete[] Values;
	Values = new T[Capacity];

	std::copy(other.cbegin(), other.cend(), Values);
}

//Purpose: gives the ability to assign an on the fly array 
//Example: vector<int> test; test = {1, 2, 3, 4, 5};
template <class T>
void vector<T>::operator=(std::initializer_list<T>&& list) {
	Size = list.size();
	Capacity = list.size();

	delete[] Values;
	Values = new T[Capacity];

	std::move(list.begin(), list.end(), Values);
}

//Purpose: gives the user the ability to get random access to the Values array
//Example: vector<int> test = {1, 2, 3, 4, 5}; test[0];
template<class T> 
T& vector<T>::operator[](const int index) {
	if (index < 0 || index > Capacity) //Bounds Checking
	{
		throw std::out_of_range("request was out of range of the vector");
	}

	return Values[index];
}

//Purpose: insert gives the ability to insert a value anywhere within the current vector size.
template<class T>
void vector<T>::insert(const int index, const T& value) {
	if (index < 0 || index > Size) {
		throw std::out_of_range("request was out of range of the vector");
	}
	else if (index == 0) {    //Insert is really doing a push_front
		push_front(value);
	}
	else if (index == Size) { //Insert is really doing a push_back
		push_back(value);
	}
	else {
		push_back(value);	 //Add Value to end then shift array (rotate)
		std::rotate(this->begin() + index, this->end() - 1, this->end());
	}
}

//Purpose: Appends a value to the vector, and it may call the resize (reserve)
//function to increase the capacity if the size is equal to capacity.
template<class T>
void vector<T>::push_back(const T& value) {
	if (Size == Capacity) reserve(); 
	Values[Size] = value;

	Size++;
}

//Purpose: inserts a value to the front of the array.
template<class T>
void vector<T>::push_front(const T& value) {
	push_back(value); //Append to end of array then shift (rotate) array
	std::rotate(this->begin(), this->end() - 1, this->end());
}

//Purpose: grows the array's capacity. Growth rate of 1.5 insures that the vector
//grows fast enough to avoid too many allocs. too many allocs would hinder the vector.
template <class T>
void vector<T>::reserve() {
	int tmpCapacity = (Capacity == 1) ? 2 : static_cast<int>(Capacity * 1.5);

	auto tmpValues = new T[tmpCapacity];
	std::move(begin(), end(), tmpValues);

	delete [] Values;

	Values = tmpValues;
	Capacity = tmpCapacity;
}


//Purpose: allows the vector to be allocated, so if the user of vector class
//knows how much space they'll use then they can avoid a lot of allocs from reserve();
template <class T>
bool vector<T>::reserve(const int capacity) {
	bool result;

	if(capacity < 0) {
		throw std::length_error("Vector::reserve() cannot be negative.");
	}
	else if (capacity <= Capacity) { //vector is already larger than 
		result = false;				 //or equal to attempted reserve
	}
	else {
		T *tmpValues = new T[capacity];
		std::move(begin(), end(), tmpValues);
		
		delete [] Values;

		Values = tmpValues;

		Capacity = capacity;
		result = true;
	}

	return result;
}