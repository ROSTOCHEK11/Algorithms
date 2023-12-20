#include <iostream>
#include "BinaryHeap.h"
using namespace std;


template<typename T>
void HeapSort(T* arr, int n, int(*comp)(T, T)) {
    BinaryHeap<T> heap;
    for (int i = 0; i < n; i++) {
        heap.Insert(arr[i], comp);
    }

    for (int i = n - 1; i >= 0; i--) {
        arr[i] = heap.RemoveMax(comp); 
    }
}



void CountingSort(int* arr, int n, int maxVal) {
    
    int* count = new int[maxVal + 1] {0};
    int* output = new int[n];

    // записываем в массив каунт +1 под таким же индексом что и само число, 
    // и при его повторе добавляем +1 под тем же индексом
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }

     
    for (int i = 1; i <= maxVal; i++) {
        count[i] += count[i - 1];
    }

   
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    delete[] count;
    delete[] output;
}




void BucketSort(int* arr, int n, int m) {
    
    int maxVal = arr[0];
    int minVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) maxVal = arr[i];
        if (arr[i] < minVal) minVal = arr[i];
    }

    
    int** buckets = new int* [m];
    int* bucketSizes = new int[m] {0};

    // Инициализируем каждую корзину
    for (int i = 0; i < m; ++i) {
        buckets[i] = new int[n];
    }

    // Распределяем элементы по корзинам
    for (int i = 0; i < n; i++) {
        int index;
        if (maxVal == minVal) { 
            index = 0;
        }
        else {
            index = (int)((long long)(arr[i] - minVal) * (m - 1) / (maxVal - minVal));
        }
        buckets[index][bucketSizes[index]++] = arr[i];
    }

    // Сортируем каждую корзину и объединяем
    int idx = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 1; j < bucketSizes[i]; j++) {
            int key = buckets[i][j];
            int k = j - 1;
            while (k >= 0 && buckets[i][k] > key) {
                buckets[i][k + 1] = buckets[i][k];
                k--;
            }
            buckets[i][k + 1] = key;
        }

        for (int j = 0; j < bucketSizes[i]; j++) {
            arr[idx++] = buckets[i][j];
        }
        delete[] buckets[i];
    }

    delete[] buckets;
    delete[] bucketSizes;
}


struct MyObject {
    int data;
    double key;

    MyObject() : data(0), key(0.0) {}

    MyObject(int d, double k) : data(d), key(k) {}
    
    friend ostream& operator<<(ostream& os, const MyObject& obj) {
        os << "(" << obj.data << ", " << obj.key << ")";
        return os;
    }
};

double getObjectKey(const MyObject& obj) {
    return obj.key;
}

int compareMyObjects(const MyObject& a, const MyObject& b) {
    return (a.data < b.data) ? -1 : (a.data > b.data);
}

template <typename T>
void BucketSort(T* arr, int n, int m, double (*getKey)(const T&), int (*comp)(const T&, const T&)) {
   
    T** buckets = new T * [m];
    int* bucketSizes = new int[m] {0};

    
    for (int i = 0; i < m; ++i) {
        buckets[i] = new T[n];
    }

    
    for (int i = 0; i < n; ++i) {
        int index = static_cast<int>(m * getKey(arr[i]));
        buckets[index][bucketSizes[index]++] = arr[i];
    }

    
    int idx = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 1; j < bucketSizes[i]; ++j) {
            T key = buckets[i][j];
            int k = j - 1;
            while (k >= 0 && comp(buckets[i][k], key) > 0) {
                buckets[i][k + 1] = buckets[i][k];
                k--;
            }
            buckets[i][k + 1] = key;
        }
        for (int j = 0; j < bucketSizes[i]; ++j) {
            arr[idx++] = buckets[i][j];
        }
    }

    
    for (int i = 0; i < m; ++i) {
        delete[] buckets[i];
    }
    delete[] buckets;
    delete[] bucketSizes;
}

template <typename T>
void printArray(T* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}





int main()
{
    

    // Test Heap Sort
    int intArray[] = { 15, 3, 12, 6, 9, 8, 11, 10 };
    int n = sizeof(intArray) / sizeof(intArray[0]);
    
    HeapSort(intArray, n, comp<int>);
    cout << "Heap Sorted Array: ";
    printArray(intArray, n);


    // Test Counting Sort
    int intArray1[] = { 15, 3, 12, 7, 6, 9, 7, 8, 10 };
    int n1 = sizeof(intArray1) / sizeof(intArray1[0]);
    
    CountingSort(intArray1, n1, 16);  // Assuming max value is less than 16
    cout << "Counting Sorted Array: ";
    printArray(intArray1, n1);


    // Test Bucket Sort for Integers
    int intArray2[] = { 15, 3, 12, 16, 16, 6, 9, 8, 10 };
    int n2 = sizeof(intArray2) / sizeof(intArray2[0]);
    
    BucketSort(intArray2, n2, 10);  
    cout << "Bucket Sorted Array (Integers): ";
    printArray(intArray2, n2);



    // Testing Custom Data Type Array

    MyObject objArray[] = { MyObject(4, 0.25), MyObject(1, 0.05), MyObject(3, 0.15), MyObject(2, 0.10), MyObject(2, 0.10), MyObject(5, 0.2) };
    int objArraySize = sizeof(objArray) / sizeof(objArray[0]);


    // Test Bucket Sort for Generic Types
    BucketSort(objArray, objArraySize, 10, getObjectKey, compareMyObjects);
    cout << "Bucket Sorted Array (Generic): ";
    printArray(objArray, objArraySize);


}


