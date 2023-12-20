#pragma once
#include <iostream>
using namespace std;



template<typename T>
class BinaryHeap {

private:

	T* heap;
	int capacity;
	int size;



	void Resize(int newCapacity);

	void UpHeapify(int index, int(*comp)(T, T));

	void DownHeapify(int index, int(*comp)(T, T));

	void swap(T* a, T* b)
	{
		T temp = *a;
		*a = *b;
		*b = temp;
	}


public:

	BinaryHeap(T* array, int arraySize, bool useTopDown, int(*comp)(T, T)) : heap(array), size(arraySize), capacity(arraySize) {
		if (useTopDown) {
			for (int i = 1; i < size; ++i) {
				UpHeapify(i, comp);
			}
		}
		else {
			for (int i = (size / 2) - 1; i >= 0; --i) {
				DownHeapify(i, comp);
			}
		}
	}

	void sort(int(*comp)(T, T)) {
		for (int i = size - 1; i > 0; --i) {
			swap(&heap[0], &heap[i]);
			size--;
			DownHeapify(0, comp);
		}
	}


	BinaryHeap() : capacity(10), size(0) {
		heap = new T[capacity];
	}

	~BinaryHeap() {
		delete[] heap;
	}


	void Insert(const T& data, int(*comp)(T, T));

	int RemoveMax(int(*comp)(T, T));

	void Clear();

	void PrintHeap();

	void RepairTopDown(int(*comp)(T, T));

	void RepairBottomUp(int(*comp)(T, T));


};

template<typename T>
void BinaryHeap<T>::RepairTopDown(int(*comp)(T, T)) {
	for (int i = 1; i < size; ++i) {
		UpHeapify(i, comp);
	}
}


template<typename T>
void BinaryHeap<T>::RepairBottomUp(int(*comp)(T, T)) {
	for (int i = (size / 2) - 1; i >= 0; --i) {
		DownHeapify(i, comp);
	}
}


template<typename T>
void BinaryHeap<T>::Resize(int newCapacity)
{
	T* newHeap = new T[newCapacity];
	for (int i = 0; i < size && i < newCapacity; i++) {
		newHeap[i] = heap[i];
	}

	delete[] heap;
	heap = newHeap;
	capacity = newCapacity;
}

template<typename T>
void BinaryHeap<T>::UpHeapify(int index, int(*comp)(T, T))
{

	if (index <= 0) return;

	int parent = (index - 1) / 2;
	if (comp(heap[index], heap[parent]) > 0) {
		swap(&heap[index], &heap[parent]);
		UpHeapify(parent, comp);
	}

}

template<typename T>
void BinaryHeap<T>::DownHeapify(int index, int(*comp)(T, T))
{

	int largest = index;
	int leftChild = 2 * index + 1;
	int rightChild = 2 * index + 2;

	if (leftChild < size && comp(heap[leftChild], heap[largest]) > 0) {
		largest = leftChild;
	}

	if (rightChild < size && comp(heap[rightChild], heap[largest]) > 0) {
		largest = rightChild;
	}

	if (largest != index) {
		swap(&heap[index], &heap[largest]);
		DownHeapify(largest, comp);
	}


}

template<typename T>
void BinaryHeap<T>::Insert(const T& data, int(*comp)(T, T))
{
	if (size >= capacity) {
		Resize(capacity * 2);
	}
	heap[size] = data;
	UpHeapify(size, comp); // Ensure the new element maintains heap property
	size++;

}

template<typename T>
int BinaryHeap<T>::RemoveMax(int(*comp)(T, T))
{
	if (size <= 0) {
		throw std::runtime_error("Heap is empty");
	}

	T maxItem = heap[0];
	heap[0] = heap[size - 1];
	size--;
	DownHeapify(0, comp);

	if (size < capacity / 4 && capacity > 10) {
		Resize(capacity / 2);
	}

	return maxItem;
}

template<typename T>
void BinaryHeap<T>::Clear()
{
	size = 0;
	capacity = 10;
	delete[] heap;
	heap = new T[capacity];
}

template<typename T>
void BinaryHeap<T>::PrintHeap()
{
	cout << "Heap: [";
	for (int i = 0; i < size; ++i) {
		cout << heap[i] << " ";
	}
	cout << "]" << std::endl;
}

template<typename T>
int comp(T a, T b)
{
	if (a < b)
	{
		return -1;
	}
	else if (a > b)
	{
		return 1;
	}
	else
	{
		return 0;
	}

};