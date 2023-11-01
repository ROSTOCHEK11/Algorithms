#include <iostream>
#include <ctime>

using namespace std;

template<typename T>
class Node
{
public:
    Node* pNext; // указатель на следующий элемент
    Node* pPrev; // указатель на предыдущий элемент
    T data;      // данные элемента / узла

    Node(T data = T(), Node* pNext = nullptr, Node* pPrev = nullptr) {
        this->data = data;
        this->pNext = pNext;
        this->pPrev = pPrev;
    }
};

template<typename T>
class List
{
public:
    List();
    ~List();

    void AddBack(T data);             // a
    void AddFront(T data);            // b
    void DelLast();                   // c
    void DelFirst();                  // d
    T& operator[](const int index);   // e, f
    Node<T>* FindElementData(T data, int (*Comp)(T&, T&));  // g
    void DelInd(int index);           // h
    void Insert(T data, int index);   // i
    void Clear();                     // j
    void Display();                   // k
    
    int GetSize() { return Size; }

    void BubbleSort();

private:

    int Size;
    Node<T>* head;  // первый элемент списка
    Node<T>* tail;  // последний элемент списка

    Node<T>* GetNode(int index);

};

template<typename T>
List<T>::List()
{
    Size = 0;
    head = nullptr;
    tail = nullptr;
}

template<typename T>
List<T>::~List()
{
    Clear();
}



// -------------------------------- INDEX OPERATIONS -------------------------------- \\



template<typename T>
Node<T>* List<T>::GetNode(int index)
{

    if (index < 0 || index >= Size) // проверка на index out bounds
    {  
        return nullptr;
    }

    Node<T>* current;

    // Выбераем откуда начать, хед или тейл
    if (index < Size / 2) 
    {
        current = head;
        for (int i = 0; i < index; i++) 
        {
            current = current->pNext;   // если в первой половине то идём от начала
        }
    }
    else 
    {
        current = tail;
        for (int i = Size - 1; i > index; i--) 
        {
            current = current->pPrev;   // если во второй то идём от конца
        }
    }

    return current;

}



template<typename T>
T& List<T>::operator[](const int index)
{
    Node<T>* current = GetNode(index);

    if (current != nullptr) // если не пустой
    {
        return current->data;
    }
    else
    {
        throw out_of_range("Index out of bounds");
    }
    

}



template<typename T>
void List<T>::Insert(T data, int index)
{
    if (index == 0) 
    {
        AddFront(data);
    }
    else if (index == Size) 
    {
        AddBack(data);
    }
    else 
    {

        Node<T>* current = GetNode(index);

        if (current != nullptr)
        {

            Node<T>* newNode = new Node<T>(data, current, current->pPrev); // создаём новую ноду
            current->pPrev->pNext = newNode;   // предыдущему елементу присваем в указатель некст нашу новую НОДУ
            current->pPrev = newNode; // а тут нашему текущему елементу, то есть следующему от insert елемента ,
            Size++;                         // записываем новую ноду в указатель Прев

        }

    }

}



template<typename T>
void List<T>::DelInd(int index)
{
    if (index == 0) {
        DelFirst();
    }
    else if (index == Size - 1) {
        DelLast();
    }
    else {

        Node<T>* current = GetNode(index);
        if (current != nullptr) 
        {
            Node<T>* DeleteTemp = current;
            current->pPrev->pNext = current->pNext; // предыдущему елементу присваиваем указатель на следующий
            current->pNext->pPrev = current->pPrev; // след елементу присваиваем указатель на предыдущий
            delete DeleteTemp;
            Size--;
        }

    }

}



// -------------------------------- INDEX OPERATIONS -------------------------------- \\




template<typename T>
void List<T>::AddFront(T data)
{
    if (head == nullptr) 
    {
        head = new Node<T>(data); // тут всё понятно
        tail = head;
    }
    else 
    {
        Node<T>* newHead = new Node<T>(data, head); // создаём новый хед и в некст кладём след елемент( старый хед )
        head->pPrev = newHead; // старому хеду в Прев записываем наш новый Хед
        head = newHead; // и новый хед устанавливаем как основной хед
    }

    Size++;
}

template<typename T>
void List<T>::Clear()
{
    while (head != nullptr) 
    {
        Node<T>* temp = head; // копируем Хед в временную переменную
        head = head->pNext; // переходим на некст елемент
        delete temp; // удаляем ПЕрвый темп елемент
    }

    Size = 0;
    head = nullptr;
    tail = nullptr;
}

template<typename T>
void List<T>::DelFirst()
{
    if (head == nullptr) 
    {
        cout << "YOU CAN'T DELETE NOTHING !!!";
    }
    else 
    {
        Node<T>* temp = head; // копируем Хед в временную переменную
        head = head->pNext; // переходим на некст елемент

        if (head != nullptr) { // если хед не пустой
            head->pPrev = nullptr; // мы отвязываем наш след хед и приписываем в Прев Нул
        }
        else { // а если он пустой, то и тейлу даём ноль
            tail = nullptr;
        }

        delete temp;
        Size--;
    }
}

template<typename T>
void List<T>::DelLast()
{
    if (tail == nullptr)
    {
        cout << "CAN'T delete the LAST element; the list is EMPTY." << endl;
    }
    else 
    {
        if (tail->pPrev != nullptr) // если больше одного елемента
        { 
            Node<T>* current = tail; // создаём темп переменую
            tail = tail->pPrev;   // переходим на елемент назад
            tail->pNext = nullptr; // отвязываем от старого елемента и передаём в Некст Нул
            delete current;
        }
        else 
        {
            Clear();
        }

        Size--;
    }
}

template<typename T>
void List<T>::AddBack(T data)
{
    if (tail == nullptr) 
    {
        AddFront(data);
    }
    else 
    {
        Node<T>* newTail = new Node<T>(data, nullptr, tail); // создаём новый тейл с Некстом на Нул и Превом на старый тейл
        tail->pNext = newTail; // В указатель Некст пред елемента(старого тейла) ставим Новый тейл
        tail = newTail; // ставим новый тейл основным

        Size++;
    }
}

template<typename T>
void List<T>::Display()
{
    if (head == nullptr) 
    {
        cout << "THE LIST IS EMPTY" << endl;
    }
    else 
    {
        Node<T>* current = head;
        cout << endl;
        while (current != nullptr)
        {
            cout << current->data << endl;
            current = current->pNext;
        }
    }
    cout << "Size: " << Size << "\n\n";
}

template<typename T>
int Compare(T& a, T& b)
{
    if (a == b) 
    {
        return 0;
    }
    else 
    {
        return 1;
    }
}



template<typename T>
Node<T>* List<T>::FindElementData(T data, int (*Comparator)(T&, T&))
{
    Node<T>* current = head;

    while (current != nullptr) // пока не дойдём до конца
    {
        if (Comparator(current->data, data) == 0) // карент будет равняться дате выводим текущую дату
        {
            return current;
        }
        current = current->pNext; // если нет идём на некст
    }

   
    return nullptr;
}

template<typename T>
void List<T>::BubbleSort()
{
    if (head == nullptr || head->pNext == nullptr) 
    {
        return; // пустой либо один элемент
    }

    bool swapped;
    Node<T>* current;
    Node<T>* lastSorted = nullptr;

    do {
        swapped = false;
        current = head;

        while (current->pNext != lastSorted) 
        {
            if (current->data > current->pNext->data)
            {
                // меняем местами текущий и следующий элемент
                T temp = current->data;
                current->data = current->pNext->data;
                current->pNext->data = temp;
                swapped = true;
            }
            current = current->pNext;
        }

        lastSorted = current; // мы отсортировались и записали в ласт сортед последний отсортированый елемент, 
                        //далее мы продолжаем сортировать, но уже до Ласт сортед, то есть мы уменьшаем количество проходок, 
                        // разделяя массив на отсортированную и неотсортированную часть

    } while (swapped);
}

int main()
{
    List<int> Lista;
    int Variant;
    Node<int>* FindEl = nullptr;

    do {
        int num = 0;
        int index = 0;

        cout << "1) Add an element to BACK " << endl;
        cout << "2) Add an element to FRONT " << endl;
        cout << "3) INSERT an element " << endl;
        cout << "4) Change an element by INDEX " << endl;
        cout << "5) Delete the FIRST element " << endl;
        cout << "6) Delete the LAST element " << endl;
        cout << "7) Delete an element by INDEX " << endl;
        cout << "8) FIND an element by INDEX " << endl;
        cout << "9) FIND an element by DATA " << endl;
        cout << "10) Clear the list " << endl;
        cout << "11) Display the list " << endl;
        cout << "12) Sort the List " << endl;
        cout << "13) Clean the Console \n" << endl;
        cout << "14) EXIT \n" << endl;

        cout << "Choose an option (num): ";
        cin >> Variant;

        switch (Variant) {

        case 1:

            cout << "Adding element to BACK" << endl;
            cout << "Write the number: ";
            cin >> num;
            Lista.AddBack(num);
            cout << "\nThe number added to back\n\n";
            break;


        case 2:

            cout << "Adding element to FRONT" << endl;
            cout << "Write the number: ";
            cin >> num;
            Lista.AddFront(num);
            cout << "\nThe number added to front\n\n";
            break;


        case 3:

            cout << "Inserting element to list" << endl;
            cout << "Write the number: ";
            cin >> num;
            cout << "\nChoose the index from 1 to " << Lista.GetSize() << " : ";
            cin >> index;
            Lista.Insert(num, index-1);
            cout << "\nThe number inserted in list\n\n";
            break;


        case 4:

            cout << "Changing element by index" << endl;
            cout << "Write the number: ";
            cin >> num;
            cout << "\nChoose the index from 1 to " << Lista.GetSize() << " : ";
            cin >> index;
            Lista[index-1] = num;
            cout << "\nThe number in list changed\n\n";
            break;


        case 5:

            Lista.DelFirst();
            cout << "\nFirst element deleted\n" << endl;
            break;


        case 6:

            Lista.DelLast();
            cout << "\nLast element deleted\n" << endl;
            break;


        case 7:

            cout << "Deleting element by index" << endl;
            cout << "\nChoose the index from 1 to " << Lista.GetSize() << " : ";
            cin >> index;
            Lista.DelInd(index-1);
            cout << "\nThe number deleted\n\n";
            break;


        case 8:

            Lista.Display();
            cout << "Finding element by index" << endl;
            cout << "\nChoose the index from 1 to " << Lista.GetSize() << " : ";
            cin >> index;
            cout << "\nThe founded element is: " << Lista[index-1] << endl << endl;
            break;


        case 9:

            Lista.Display();
            cout << "Finding element by Data" << endl;
            cout << "Write the number: ";
            cin >> num;
            FindEl = Lista.FindElementData(num, Compare);
            if (FindEl != nullptr) {
                cout << "\nThe founded element is: " << FindEl->data << endl << endl;
            }
            break;


        case 10:

            Lista.Clear();
            cout << "The list cleared\n" << endl;
            break;


        case 11:

            Lista.Display();
            break;


        case 12:

            Lista.BubbleSort();
            cout << "The list sorted\n" << endl;
            break;


        case 13:

            system("CLS");
            break;


        case 14:

            cout << "DOWIDZENIA\n" << endl;
            break;


        default:

            cout << "TRY AGAIN !!!!!\n\n";
            break;

        }

    } while (Variant != 14);

    const int MaxOrder = 6;

    for (int o = 0; o < MaxOrder; o++) {
        const double n = pow(10, o);

        clock_t start = clock();
        for (int i = 0; i < n; i++) {
            Lista.AddFront(rand() % 20);
           // cout << Lista[i];
        }
        clock_t end = clock();

        double dur = (end - start) / (double)CLOCKS_PER_SEC;
        cout << dur;
    }
}
