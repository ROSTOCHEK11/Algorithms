#include <iostream>
#include <time.h>
using namespace std;




template <typename T>
class DynamicArray {

public:
   
    DynamicArray(int newCapacity = 2.0);
    ~DynamicArray();


    void AddBack(const T& element); // a
    T& operator[](int index);       // b, c
    void Clear();                   // d
    void Print();                   // e
    void BubbleSort(int(*comparator)(T a, T b)); // f
                


private:

    T* data;
    int currentSize;
    int maxCapacity;
    

    void EnlargeSize();


};

template<typename T>
DynamicArray<T>::DynamicArray(int newCapacity)
{

    currentSize = 0;
    maxCapacity = newCapacity;
    data = new T[maxCapacity];

}

template<typename T>
DynamicArray<T>::~DynamicArray() 
{
    delete[] data;
}


template<typename T>
void DynamicArray<T>::AddBack(const T& element) 
{
    if (currentSize == maxCapacity) {
        EnlargeSize();
    }
    data[currentSize] = element;
    currentSize++;
}

template<typename T>
T& DynamicArray<T>::operator[](int index)
{

    if (index < 0 || index >= currentSize) 
    {
        throw out_of_range("Indeks poza zakresem");
    }
    return data[index];
        
}

template<typename T>
void DynamicArray<T>::Clear()
{
    currentSize = 0;
}

template<typename T>
void DynamicArray<T>::Print()
{
    cout << "\nSize : " << currentSize << endl;
    cout << "\nCapacity : " << maxCapacity << endl;
    for (int i = 0; i < currentSize; i++)
    {
        cout << data[i] << " ";
    }
    cout << endl;

}

template<typename T>
void DynamicArray<T>::BubbleSort(int(*comparator)(T a, T b))
{

    for (int i = 0; i < currentSize - 1; i++)
    {
        // äîðàáîòàòü  ÒÐÓ ÔÎËÑ
        for (int j = 0; j < currentSize - i - 1; j++)
        {
            if (comparator(data[j], data[j + 1]) == 1)
            {
              
                T temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;

            }
        }
    }

}

template <typename T>
int Compare(T a, T b)
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

template<typename T>
void DynamicArray<T>::EnlargeSize()
{

    int new_capacity = maxCapacity * 2;
    T* new_data = new T[new_capacity];

    for (int i = 0; i < currentSize; i++) 
    {
        new_data[i] = data[i];
    }

    delete[] data;
    data = new_data;
    maxCapacity = new_capacity;

}




int main()
{
    DynamicArray<int> Array;
    int choice;

    do
    {
        int element = 0;
        int index = 0;

        cout << "1) Add an element to Array\n";
        cout << "2) Get element by index\n";
        cout << "3) Set element by index\n";
        cout << "4) Clear the array\n";
        cout << "5) Print the array\n";
        cout << "6) Sort the array\n";
        cout << "7) Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {

        case 1:

            cout << "Adding element to BACK" << endl;
            cout << "Write the element : ";
            cin >> element;
            Array.AddBack(element);
            cout << "\nThe number added\n\n";
            break;

        case 2:

            Array.Print();
            cout << "Finding element by index" << endl;
            cout << "\nWrite the index ";
            cin >> index;
            cout << "\nThe founded element is: " << Array[index] << endl << endl;
            break;

        case 3:

            cout << "Setting element by index" << endl;
            cout << "Write the element: ";
            cin >> element;
            cout << "\nWrite the index ";
            cin >> index;
            Array[index] = element;
            cout << "\nThe number in list changed\n\n";
            break;

        case 4:

            cout << "Array cleared\n\n";
            Array.Clear();
            break;

        case 5:

            Array.Print();
            break;

        case 6:

            cout << "Array is sorted\n\n";
            Array.BubbleSort(Compare);
            break;

        case 7:

            cout << "\nbye bye\n\n";
            break;

        default:

            cout << "TRY AGAIN !!!!!\n\n";
            break;

        }


    } while (choice != 7);



    DynamicArray<int> TimeTestArray;

    const int order = 7; 
    const int n = pow(10, order); 

    clock_t t1 = clock();

    double max_time_per_element = 0.0;

    int max_time_index = -1;

    for (int i = 0; i < n; i++) 
    {
        int so = 457; 

        clock_t t1_element = clock();

        TimeTestArray.AddBack(so);
        
        clock_t t2_element = clock();

        double time_per_element = static_cast<double>(t2_element - t1_element) / CLOCKS_PER_SEC;

        if (time_per_element > max_time_per_element) {
            max_time_per_element = time_per_element;
            max_time_index = i;
        }
    }

    clock_t t2 = clock();

    double total_time = static_cast<double>(t2 - t1) / CLOCKS_PER_SEC;
    cout << "Total time taken: " << total_time << " seconds" << endl;

    cout << "Worst-case time for adding an element occurred at index " << max_time_index << ": " << max_time_per_element << " seconds" << endl;





}


