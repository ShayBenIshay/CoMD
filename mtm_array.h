//
//	mtm_array.cpp
// Created by:
//	Shay Ben-Ishay 308052463
//	Liav Eliyahu 311502660
//

#ifndef EX5_MTM_ARRAY_H
#define EX5_MTM_ARRAY_H

#include <utility>
#include <stdexcept>
#include <iostream>

using std::out_of_range;

template <class T, int SIZE>
class Array {
	T *data;
	int array_size;
public:
	explicit Array();	//does explicit mandatory? not mentioned for "set"
	//explicit Array(int size); //not sure if needed.
	Array(const Array&);
	~Array();
	Array& operator=(const Array&);

	T& operator[](int);				    //or should it be: Array& ?
	const T& operator[](int) const; 	//or should it be: Array& ?

	int size() const; //not sure if needed.
	//declarations for "find" and "contains" if needed.

	class iterator {
		const Array<T,SIZE>* array;
		int index;
		friend class Array<T,SIZE>;

	public:
		//constructor:
		iterator(const Array<T,SIZE>* array, int index) :
				array(array),
				index(index)
		{}
		//Operators
		T& operator*() const;
		T* operator->() const;
		iterator& operator++();
		iterator operator++ (int);

		bool operator==(const iterator& iterator) const; //needs implementation
		bool operator!=(const iterator& iterator) const; //needs implementation

		iterator(const iterator&) = default;
		iterator& operator=(const iterator&) = default;
	};

    class const_iterator {
        const Array<T,SIZE>* array;
        int index;
        friend class Array<T,SIZE>;
    public:
        //constructor:
        const_iterator(const Array<T,SIZE>* array, int index) :
                array(array),
                index(index)
        {}

        //Operators
        T const& operator*() const;
        const T* operator->() const;
        const_iterator& operator++();
        const_iterator operator++ (int);

        bool operator==(const const_iterator& const_iterator) const; //needs implementation
        bool operator!=(const const_iterator& const_iterator) const; //needs implementation

        const_iterator(const const_iterator&) = default;
        const_iterator& operator=(const const_iterator&) = default;
    };

	//TODO: Declare Class const_iterator here
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;


};

//Implementations for Array class:

//constructor
template <class T, int SIZE>
Array<T,SIZE>::Array() : data(new T[SIZE]),
						 array_size(SIZE)
{}
//destructor
template <class T, int SIZE>
Array<T,SIZE>::~Array(){
	delete[] data;
}
//copy constructor
template <class T, int SIZE>
Array<T,SIZE>::Array(const Array<T,SIZE>& array):
		data(new T[array.array_size]),
		array_size(array.array_size) {
	for(int i=0 ; i < array_size ; i++){
		data[i]=array.data[i];   //assumes T type has copy constructor
	}
}
//operators:
template <class T, int SIZE>
Array<T,SIZE>& Array<T,SIZE>::operator=(const Array& array){
	if(this == &array){
		return *this;
	}
	delete[] data;
	data = new T[array.array_size];
	array_size = array.array_size;
	for(int i=0;i<array_size;++i){
		data[i]=array.data[i];
	}
	return *this;
}

template <class T, int SIZE>
T& Array<T,SIZE>::operator[](int index){
	if(index>=array_size || index<0){
		//throw exception
		throw std::out_of_range("mtm_array::operator []: index out of range!");
	}
	return data[index];
}

template <class T, int SIZE>
const T& Array<T,SIZE>::operator[](int index) const{
	if(index>=array_size || index<0){
		//throw exception
		throw std::out_of_range("mtm_array::operator []: index out of range!");
	}
	return data[index];
}

//Functions:

//Implementation of "size" function - not clear if mandatory. causes conflicts with field "size".
template <class T, int SIZE>
int Array<T,SIZE>::size() const{
	return array_size;
}

/*
//implementation of "find" and "contains" functions - not clear if mandatory.

template<class T>
int Set<T>::find(const T& elem) const {
for(int i = 0; i < size; i++) {
if (data[i] == elem) {
return i;
}
}
return ELEMENT_NOT_FOUND;
}

template<class T>
bool Set<T>::contains(const T& elem) const {
return find(elem) != ELEMENT_NOT_FOUND;
}

*/

/*
//Should we add operator << for printing?
template <class T, int SIZE>
std::ostream& operator<<(std::ostream& os, const Array<T,SIZE>& array){
	os << "{";
	bool first = true;
	for (typename Set<T>::iterator it = set.begin();
		 it != set.end(); ++it) {
		if (!first) {
			os << ",";
		}
		first = false;
		os << " " << (*it);
	}
	os << " }";
	return os;
}
*/

//ITERATORS:
//"begin" and "end" for iterator
template <class T, int SIZE>
typename Array<T,SIZE>::iterator Array<T,SIZE>::begin(){
		return iterator(this,0);
	}
template <class T, int SIZE>
typename Array<T,SIZE>::iterator Array<T,SIZE>::end(){
		return iterator(this,array_size);
	}
//"begin" and "end" for const_iterator
template <class T, int SIZE>
typename Array<T,SIZE>::const_iterator Array<T,SIZE>::begin() const{
    return const_iterator(this,0);
}
template <class T, int SIZE>
typename Array<T,SIZE>::const_iterator Array<T,SIZE>::end() const{
    return const_iterator(this,array_size);
}

//operators for iterator
template <class T, int SIZE>
T& Array<T,SIZE>::iterator::operator*() const {
	if(index>=array->size() || index<0){
		//throw exception
		throw std::out_of_range("mtm_array::operator*: index out of range!");
	}
	return array->data[index];
}
template <class T, int SIZE>
T* Array<T,SIZE>::iterator::operator->() const {
    if(index>=array->size() || index<0){
        //throw exception
        throw std::out_of_range("mtm_array::operator*: index out of range!");
    }
    return &(array->data[index]);
}
template <class T, int SIZE>
typename Array<T,SIZE>::iterator& Array<T,SIZE>::iterator::operator++() {
	++index;
	return *this;
}
template <class T, int SIZE>
typename Array<T,SIZE>::iterator Array<T,SIZE>::iterator::operator++(int) {
	iterator result = *this;
	++*this;
	return result;
}
template <class T, int SIZE>
bool Array<T,SIZE>::iterator::operator==(const iterator& i) const {
	//assert(array == i.array); //not sure what this assert stands for exactly. might need to add "throw" here
	return (array == i.array && index == i.index);
}
template <class T, int SIZE>
bool Array<T,SIZE>::iterator::operator!=(const iterator& i) const {
	return !(*this == i);
}

//operators for const_iterator
template <class T, int SIZE>
T const& Array<T,SIZE>::const_iterator::operator*() const {
    if(index>=array->size() || index<0){
        //throw exception
        throw std::out_of_range("mtm_array::operator*: index out of range!");
    }
    return array->data[index];
}
template <class T, int SIZE>
const T* Array<T,SIZE>::const_iterator::operator->() const {
    if(index>=array->size() || index<0){
        //throw exception
        throw std::out_of_range("mtm_array::operator*: index out of range!");
    }
    return &(array->data[index]);
}
template <class T, int SIZE>
typename Array<T,SIZE>::const_iterator& Array<T,SIZE>::const_iterator::operator++() {
    ++index;
    return *this;
}
template <class T, int SIZE>
typename Array<T,SIZE>::const_iterator Array<T,SIZE>::const_iterator::operator++(int) {
    const_iterator result = *this;
    ++*this;
    return result;
}
template <class T, int SIZE>
bool Array<T,SIZE>::const_iterator::operator==(const const_iterator& i) const {
    //assert(array == i.array); //not sure what this assert stands for exactly. might need to add "throw" here
    return ( array == i.array && index == i.index);
}
template <class T, int SIZE>
bool Array<T,SIZE>::const_iterator::operator!=(const const_iterator& i) const {
    return !(*this == i);
}

#endif //EX5_MTM_ARRAY_H
