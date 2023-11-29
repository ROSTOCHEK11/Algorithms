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

	BinaryHeap() : capacity(10), size(0) {
		heap = new T[capacity];
	}

	~BinaryHeap() {
		delete[] heap;
	}


	void Insert(const T& data , int(*comp)(T, T));

	int RemoveMax(int(*comp)(T, T));

	void Clear();

	void PrintHeap();

};


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
	if ( comp(heap[index], heap[parent]) > 0 ) {
		swap(&heap[index], &heap[parent]);
		UpHeapify(parent ,comp);
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
	heap[size++] = data;
	UpHeapify(size - 1, comp);

}

template<typename T>
int BinaryHeap<T>::RemoveMax(int(*comp)(T, T))
{
	if (size <= 0)return false;
	
	T maxItem = heap[0];

	heap[0] = heap[size-1];
	size -= 1;
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


int main()
{
   
	BinaryHeap<int> heap;

	int choice;

	do
	{
		int element = 0;
		int index = 0;

		cout << "1) Add an element to Heap\n";
		cout << "2) Delete Max element\n";
		cout << "3) Print the Heap\n";
		cout << "4) Clear the Heap\n";
		cout << "5) Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice)
		{

		case 1:

			cout << "Adding element to Heap" << endl;
			cout << "Write the numbeer : ";
			cin >> element;
			heap.Insert(element, comp);
			cout << "\nThe element added\n\n";
			break;

		case 2:

			cout << "Deleting max element..." << endl;
			heap.RemoveMax(comp);
			cout << "The Max element removed\n" << endl;;
			
			break;

		case 3:

			heap.PrintHeap(); 
			break;

		case 4:

			cout << "The heap is cleared\n\n";
			heap.Clear();
			break;

		case 5:

			cout << "\nbye bye\n\n";
			break;

		default:

			cout << "TRY AGAIN !!!!!\n\n";
			break;

		}


	} while (choice != 5);




}


