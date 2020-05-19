#pragma once
#ifndef _MINMAXHEAP_H_
#define _MINMAXHEAP_H_

#include <iostream>
#include <stdexcept>

using namespace std;

template <typename  T>
static bool lessCompare(T x, T y);

template <typename  T>
static bool greaterCompare(T x, T y);

template <typename T>
class Heap;

template <typename T>
class MinMaxHeap {
	typedef bool(*fptr)(T, T);
public:
	MinMaxHeap();
	MinMaxHeap(int capacity);
	MinMaxHeap(const MinMaxHeap<T>& other);
	~MinMaxHeap();
	const MinMaxHeap<T>& operator=(const MinMaxHeap<T>& rhs);

	int size();
	void insert(const T& data);
	void dump();
	T deleteMin();
	T deleteMax();
	void locateMin(int position, T& data, int& index);
	void locateMax(int position, T& data, int& index);

private:

	int m_capacityX;
	Heap<T>* HeapX;
	Heap<T>* HeapY;
};
/*
template <typename T>
struct Pair {

  T data;
  int location;

};
*/
template <typename T>
class Heap {
	typedef bool(*fptr)(T, T);
public:
	Heap();
	Heap(int capacity, fptr fPoint);
	~Heap();
	void insert(const T& data);
	void dump();
	void setP(Heap* temp);
	T remove();
	void update();
	void bubbleUp(int index);
	void bubbleDown(int index);
	int getParent(int index);
	int leftChild(int index);
	int rightChild(int index);
	void setTwin(Heap* heapZ);
	void updateIndex(int x, int y);

	int getSize();
	int getCapacity();
	void locateMinH(int position, T& data, int& index);
	void locateMaxH(int position, T& data, int& index);
	void setSize(int size);
	int m_size;

	struct Pair {

		T data;
		int location;

	};

	//Pair getArray() { return arrayHeap; }
	Pair* arrayHeap;

private:


	int m_capacityY;
	fptr compare;
	Heap* heapTemp;
};




#include "MinMaxHeap.cpp"
#endif

