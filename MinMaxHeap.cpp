#ifndef _MINMAXHEAP_CPP_
#define _MINMAXHEAP_CPP_

#include "MinMaxHeap.h"

static const int START = 1;

using namespace std;

//MinMaxHeap Functions

template<typename T>
MinMaxHeap<T>::MinMaxHeap() {

}

template <typename T>
MinMaxHeap<T>::MinMaxHeap(int capacity)
{
	fptr compare = &lessCompare;
	m_capacityX = capacity;
	HeapX = new Heap<T>(m_capacityX, compare);

	compare = &greaterCompare;
	HeapY = new Heap<T>(m_capacityX, compare);

	HeapX->setP(HeapY);
	HeapY->setP(HeapX);

}

template <typename T>
MinMaxHeap<T>::MinMaxHeap(const MinMaxHeap<T>& other)
{

	fptr compare = &lessCompare;
	HeapX = new Heap<T>(other.HeapX->getCapacity(), compare);
	compare = &greaterCompare;
	HeapY = new Heap<T>(other.HeapY->getCapacity(), compare);

	HeapX->setP(HeapY);
	HeapY->setP(HeapX);

	HeapX->setSize(other.HeapX->getSize());
	HeapY->setSize(other.HeapY->getSize());


	for (int i = 1; i < HeapX->m_size + 1; i++)
	{
		HeapX->arrayHeap[i].data = other.HeapX->arrayHeap[i].data;
		HeapX->arrayHeap[i].location = other.HeapX->arrayHeap[i].location;
	}

	for (int j = 1; j < HeapY->m_size + 1; j++)
	{
		HeapY->arrayHeap[j].data = other.HeapY->arrayHeap[j].data;
		HeapY->arrayHeap[j].location = other.HeapY->arrayHeap[j].location;
	}

}

template <typename T>
MinMaxHeap<T>::~MinMaxHeap() {
	delete HeapX;
	delete HeapY;

}

template <typename T>
const MinMaxHeap<T>& MinMaxHeap<T>::operator=(const MinMaxHeap<T>& rhs) {
	if (this == &rhs) {
		return *this;
	}
	delete HeapX;
	delete HeapY;

	fptr compare = &lessCompare;
	HeapX = new Heap<T>(rhs.HeapX->getCapacity(), compare);
	compare = &greaterCompare;
	HeapY = new Heap<T>(rhs.HeapY->getCapacity(), compare);

	HeapX->setP(HeapY);
	HeapY->setP(HeapX);
	HeapX->setSize(rhs.HeapX->getSize());
	HeapY->setSize(rhs.HeapY->getSize());
	for (int i = 1; i < HeapX->m_size + 1; i++)
	{
		HeapX->arrayHeap[i].data = rhs.HeapX->arrayHeap[i].data;
		HeapX->arrayHeap[i].location = rhs.HeapX->arrayHeap[i].location;
	}

	for (int j = 1; j < HeapY->m_size + 1; j++)
	{
		HeapY->arrayHeap[j].data = rhs.HeapY->arrayHeap[j].data;
		HeapY->arrayHeap[j].location = rhs.HeapY->arrayHeap[j].location;
	}


	return *this;
}
template<typename T>
int MinMaxHeap<T>::size()
{
	return HeapX->getSize();
}

template<typename T>
void MinMaxHeap<T>::insert(const T& data)
{
	//std::cout << "y" << std::endl;
	HeapX->insert(data);
	HeapY->insert(data);

	HeapX->update();
	HeapY->update();
}

template<typename T>
void MinMaxHeap<T>::dump()
{
	cout << endl;
	cout << "... MinMaxHeap::dump() ..." << endl;
	cout << endl;
	cout << "--------Min Heap--------" << endl;
	HeapX->dump();
	cout << "--------Max Heap--------" << endl;
	HeapY->dump();
}

template<typename T>
T MinMaxHeap<T>::deleteMin()
{
	T min;
	min = HeapX->remove();
	return min;
}

template<typename T>
T MinMaxHeap<T>::deleteMax()
{
	T max;
	max = HeapY->remove();
	return max;
}

template<typename T>
void MinMaxHeap<T>::locateMin(int position, T& data, int& index)
{
	HeapX->locateMinH(position, data, index);

}

template<typename T>
void MinMaxHeap<T>::locateMax(int position, T& data, int& index)
{
	HeapY->locateMaxH(position, data, index);
}


// Function Pointer Functions

template <typename T>
bool lessCompare(T x, T y) {
	if (x < y) {
		return true;
	}
	return false;
}

template <typename T>
bool greaterCompare(T x, T y) {
	if (x > y) {
		return true;
	}
	return false;
}


//Heap Functions


template <typename T>
Heap<T>::Heap() {

}

template <typename T>
Heap<T>::Heap(int capacity, fptr fPoint)
{
	m_capacityY = capacity;
	arrayHeap = new Pair[m_capacityY + 1];
	m_size = 0;
	compare = fPoint;


}

template<typename T>
Heap<T>::~Heap()
{
	delete[] arrayHeap;
}

template <typename T>
void Heap<T>::insert(const T& data)
{
	if (m_size == m_capacityY)
	{
		std::cout << "No more space in heap" << std::endl;
	}
	else
	{
		m_size++;
		//Pair<T> temp = new Pair(data, m_size);
		//arrayHeap[m_size] = { data, m_size }; //insert new pair
		arrayHeap[m_size].data = data;
		arrayHeap[m_size].location = m_size;
		//arrayHeap[m_size] = temp;
	}

}

template <typename T>
void Heap<T>::dump() {

	cout << endl;

	cout << "size = " << m_size << " capacity = " << m_capacityY << endl;
	cout << "-------------------" << endl;
	for (int i = 1; i < m_size + 1; i++)
	{
		cout << "Heap[" << i << "] = (" << arrayHeap[i].data << "," << arrayHeap[i].location << ")" << endl;
	}

	cout << endl;

}

template<typename T>
void Heap<T>::setP(Heap* temp)
{
	heapTemp = temp;
}

template<typename T>
T Heap<T>::remove()
{
	T val;
	int heapLocat, locatTemp, otherLocat;
	if (m_size == 0)
	{
		throw std::out_of_range("Heap is empty");
	}

	val = arrayHeap[START].data;
	heapLocat = arrayHeap[START].location;

	arrayHeap[START] = arrayHeap[m_size];
	m_size--;

	locatTemp = arrayHeap[START].location;
	heapTemp->arrayHeap[locatTemp].location = START;
	bubbleDown(START);

	heapTemp->arrayHeap[heapLocat] = heapTemp->arrayHeap[heapTemp->m_size];
	heapTemp->m_size--;

	otherLocat = heapTemp->arrayHeap[heapLocat].location;
	if ((heapLocat > m_size) == false)
	{
		arrayHeap[otherLocat].location = heapLocat;
	}

	heapTemp->bubbleUp(heapLocat);
	return val;

}

template<typename T>
void Heap<T>::update()
{
	bubbleUp(m_size);
}

template<typename T>
void Heap<T>::bubbleUp(int index)
{
	if (index == 0)
	{
		cout << "Nothing in Heap" << endl;
		return;
	}

	//int bounds = m_size - 1;
	int parent = getParent(index);
	//if ((bounds != 0) && (arrayHeap[getParent(m_size)].data > arrayHeap[m_size].data))

	//Switches child with parent if requirements are made
	if (compare(arrayHeap[index].data, arrayHeap[getParent(index)].data))
	{
		Pair temp = arrayHeap[getParent(index)];
		arrayHeap[parent] = arrayHeap[index];
		arrayHeap[index] = temp;


		updateIndex(index, parent); // Twin heap
		bubbleUp(parent);
	}
}

template<typename T>
void Heap<T>::bubbleDown(int index)
{
	int leftC = leftChild(index);
	int rightC = rightChild(index);
	int minChild;

	if (rightC > m_size)
	{
		if (leftC < m_size)
		{
			minChild = leftC;
		}
		else
		{
			return;
		}
	}
	else
	{
		if (compare(arrayHeap[leftC].data, arrayHeap[rightC].data))
		{
			minChild = leftC;
		}
		else
		{
			minChild = rightC;
		}
	}
	//Switches child with parent if requirements are made
	if (compare(arrayHeap[minChild].data, arrayHeap[index].data)) {
		Pair temp = arrayHeap[minChild];
		arrayHeap[minChild] = arrayHeap[index];
		arrayHeap[index] = temp;
		updateIndex(minChild, index);
		bubbleDown(minChild);
	}
}

template<typename T>
//Returns Parent of index spot
int Heap<T>::getParent(int index)
{
	if (index == 1)
	{
		return 1;
	}
	int parent = index / 2;
	return parent;
}

//Returns Left Child
template<typename T>
int Heap<T>::leftChild(int index)
{
	int leftChild = (2 * index);
	return leftChild;
}

//Returns Right Child
template<typename T>
int Heap<T>::rightChild(int index)
{
	int rightChild = (2 * index) + 1;
	return rightChild;
}

template<typename T>
void Heap<T>::setTwin(Heap* heapZ)
{
	//Heap X;
	heapTemp = heapZ;
}

//updates twin index
template<typename T>
void Heap<T>::updateIndex(int x, int y)
{
	int firstP = arrayHeap[y].location;
	int secondP = arrayHeap[x].location;
	heapTemp->arrayHeap[firstP].location = y;
	heapTemp->arrayHeap[secondP].location = x;


}

template<typename T>
int Heap<T>::getSize()
{
	return m_size;
}

template<typename T>
int Heap<T>::getCapacity()
{
	return m_capacityY;
}

//Locates minimum of min heap
template<typename T>
void Heap<T>::locateMinH(int position, T& data, int& index)
{
	data = arrayHeap[position].data;
	index = arrayHeap[position].location;
}

//Locates maximunm on max heap
template<typename T>
void Heap<T>::locateMaxH(int position, T& data, int& index)
{
	data = arrayHeap[position].data;
	index = arrayHeap[position].location;
}

template<typename T>
void Heap<T>::setSize(int size)
{
	m_size = size;
}


#endif 
