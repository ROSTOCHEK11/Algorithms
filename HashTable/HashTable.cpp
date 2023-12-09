#include <iostream>
#include <string>
#include "LinkedList.h" 

using namespace std;

template<typename T>
class HashTableEntry {
public:
    string key;
    T value;

    HashTableEntry() : key(""), value(T()) {}

    HashTableEntry(string key, T value) {
        this->key = key;
        this->value = value;
    }
};

template<typename T>
class HashTable {

private:

    List<HashTableEntry<T>>* array;
    int capacity;
    int size;


    int HashFunction(string key);

    void Rehash();

    float LoadFactor() const {
        return static_cast<float>(size) / capacity;
    }

    int GetSize() const {
        return size;
    }

public:

    HashTable(int capacity) {
        this->capacity = capacity;
        array = new List<HashTableEntry<T>>[capacity];
        size = 0;
    }

    ~HashTable() {
        delete[] array;
    }

    void Insert(string key, T value);

    T* Find(string key);

    void Display();

    void Remove(string key);

    void Clear() {
        for (int i = 0; i < capacity; i++) {
            array[i].Clear();
        }
        size = 0;
    }

   
};


template<typename T>
int HashTable<T>::HashFunction(string key)
{
    int hash = 0;
    int p = 31; // A prime number
    int p_pow = 1;
    for (char ch : key) {
        hash = (hash + (ch - 'a' + 1) * p_pow) % capacity;
        p_pow = (p_pow * p) % capacity;
    }
    return (hash % capacity + capacity) % capacity;
}


template<typename T>
void HashTable<T>::Rehash()
{
    int oldCapacity = capacity;
    capacity *= 2;
    List<HashTableEntry<T>>* newArray = new List<HashTableEntry<T>>[capacity];

    for (int i = 0; i < oldCapacity; i++) {
        Node<HashTableEntry<T>>* head = array[i].GetHeadNode();
        while (head != nullptr) {
            int index = HashFunction(head->data.key);
            newArray[index].AddFront(HashTableEntry<T>(head->data.key, head->data.value));
            head = head->pNext;
        }
    }

    delete[] array;
    array = newArray;
}


template<typename T>
void HashTable<T>::Insert(string key, T value)
{
    if (capacity <= 0) {
        throw std::runtime_error("Hash table capacity must be greater than zero");
    }

    if (LoadFactor() > 0.75) {
        Rehash();
    }

    int index = HashFunction(key);
    if (index < 0 || index >= capacity) {
        throw std::runtime_error("Invalid hash index computed");
    }

    Node<HashTableEntry<T>>* head = array[index].GetHeadNode();

    while (head != nullptr) {
        if (head->data.key == key) {
            head->data.value = value;
            return;
        }
        head = head->pNext;
    }

    array[index].AddFront(HashTableEntry<T>(key, value));
    size++;
}


template<typename T>
T* HashTable<T>::Find(string key)
{
    int index = HashFunction(key);
    Node<HashTableEntry<T>>* head = array[index].GetHeadNode();

    while (head != nullptr) {
        if (head->data.key == key) {
            return &(head->data.value);
        }
        head = head->pNext;
    }
    return nullptr;
}


template<typename T>
void HashTable<T>::Display()
{
    for (int i = 0; i < min(capacity, 10); i++) { // Only display the first 10 elements
        Node<HashTableEntry<T>>* head = array[i].GetHeadNode();
        if (head != nullptr) {
            cout << "Index " + to_string(i) + ": ";
            while (head != nullptr) {
                cout << "(" + head->data.key + ", " + to_string(head->data.value) + ") ";
                head = head->pNext;
            }
            cout << "\n";
        }
    }
    cout << "\n";
}


template<typename T>
void HashTable<T>::Remove(string key)
{
    int index = HashFunction(key);
    Node<HashTableEntry<T>>* head = array[index].GetHeadNode();
    Node<HashTableEntry<T>>* prev = nullptr;

    while (head != nullptr) {
        if (head->data.key == key) {
            if (prev == nullptr) {
                array[index].DelFirst();
            }
            else {
                prev->pNext = head->pNext;
                delete head;
            }
            size--;
            return;
        }
        prev = head;
        head = head->pNext;
    }
}






int main() {

    HashTable<int> hashTable(5);

    
    hashTable.Insert("key1", 100);
    hashTable.Insert("key2", 200);
    hashTable.Insert("key3", 300);
    hashTable.Insert("key4", 400);
    hashTable.Insert("key5", 500);

    
    cout << "Hash Table Contents:" << endl;
    hashTable.Display();

    
    int* value = hashTable.Find("key3");
    if (value) {
        cout << "Found key3 with value: " << *value << endl << endl;
    }
    else {
        cout << "Key3 not found" << endl;
    }

   
    hashTable.Remove("key2");
    value = hashTable.Find("key2");
    if (value) {
        cout << "Found key2 with value: " << *value << endl;
    }
    else {
        cout << "Removing element( key2 )...\nKey2 not found" << endl << endl;
    }


    cout << "Hash Table Contents:" << endl;
    hashTable.Display();

    
    hashTable.Clear();
    cout << "Hash Table after clearing:" << endl;
    hashTable.Display();

   
    hashTable.Insert("key6", 600);
    hashTable.Insert("key7", 700);
    
    
    cout << "Hash Table after rehashing:" << endl;
    hashTable.Display();

    return 0;
}


