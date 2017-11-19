#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <algorithm>
#include "MVC.h"
using namespace std;

template <typename T>
class KMyVectorIterator;

template <typename T>
class KMyVector : public Subject {
public:
	void Accept(Visitor<T>& v)	{
		v.Visit(*this);
	}
	KMyVector() : N(0), MaxSize(1) { Array = new T[MaxSize]; };

	KMyVector(size_t aN) : N(aN), MaxSize(aN) { Array = new T[MaxSize]; };
	/*~KMyVector() { delete[]Array; };*/
	///////////////////////////////////
	void PushBack(T item) {
		if (N < MaxSize) {
			Array[N] = item;
			++N;
		}
		else {
			T* ArrayCopy = new T[2 * N];
			for (size_t i = 0; i < N; ++i) {
				ArrayCopy[i] = Array[i];
			}

			ArrayCopy[N] = item;
			++N;
			MaxSize *= 2;

			delete[]Array;
			Array = ArrayCopy;
		}
		Notify();
	}
	////////////////////////////
	T PopFront() {
		--N;
		++Array;
		++MaxSize;
		Notify();
		return *(Array + N);
	}
	//////////////////////////////////////
	friend ostream & operator << (ostream & os, KMyVector<T> const &v)	{
		for (size_t i = 0; i < v.N; ++i) {
			os << v.Array[i] << " ";
		}
		return os;
	}

	KMyVectorIterator<T> begin(){
		return KMyVectorIterator<T>(Array);
	}
	KMyVectorIterator<T> end() {
		return KMyVectorIterator<T>(Array + N);
	}
private:
	T* Array;
	size_t N;
	size_t MaxSize;
};





template <typename T>
class KMyVectorIterator : public iterator<input_iterator_tag, T> {
public:

	KMyVectorIterator() : Pointer(nullptr) {};
	KMyVectorIterator(T* aPointer) : Pointer(aPointer) {};

	T& operator * () {
		return *Pointer;
	}
	T const& operator * () const	{
		return *Pointer;
	}

	KMyVectorIterator<T>& operator ++()	{
		Pointer += 1;
		return *this;
	}
	KMyVectorIterator<T>& operator ++(int)	{
		T* PointerCopy = Pointer;
		Pointer += 1;
		return KMyVectorIterator<T>(PointerCopy);
	}
	KMyVectorIterator<T>& operator --()	{
		Pointer -= 1;
		return *this;
	}
	KMyVectorIterator<T>& operator --(int)	{
		T* PointerCopy = Pointer;
		Pointer -= 1;
		return KMyVectorIterator<T>(PointerCopy);
	}

	KMyVectorIterator<T>& operator + (int const& x) const {
		T* NewPointer = Pointer;
		NewPointer += x;
		return KMyVectorIterator<T>(NewPointer);
	}
	KMyVectorIterator<T>& operator - (int const& x) const	{
		T* NewPointer = Pointer;
		NewPointer -= x;
		return KMyVectorIterator<T>(NewPointer);
	}

	int operator - (KMyVectorIterator const& it2)	{
		int count = (Pointer - it2.Pointer);
		return count;
	}

	bool operator == (KMyVectorIterator const& it2) const	{
		return Pointer == it2.Pointer;
	}
	bool operator != (KMyVectorIterator const& it2) const	{
		return Pointer != it2.Pointer;
	}
	bool operator < (KMyVectorIterator const& it2) const
	{
		return Pointer < it2.Pointer;
	}

	KMyVectorIterator<T>& operator = (KMyVectorIterator<T> const& it2)	{
		Pointer = it2.Pointer;
		return *this;
	}

private:
	T* Pointer;
};








