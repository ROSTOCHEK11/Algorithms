#pragma once
#include <iostream>

using namespace std;



template<typename T>
class Node
{
public:
	Node* pNext; // указатель на след елемент
	T data; // данные елемента / узла 

	Node(T data = T(), Node* pNext = nullptr) {  // конструктор который создадёт сам узел

		this->data = data;
		this->pNext = pNext;

	}

	
};


template<typename T>
class List
{
public:
	List();
	~List();

	void AddBack(T data);			
	void AddFront(T data);			
	void DelLast();					
	void DelFirst();				
	T& operator[](const int index); 
	Node<T>* FindElement(T data);   
	void DelInd(int index);			
	void Insert(T data, int index); 
	void Clear();						
	void Display();					

	
	int GetSize() { return Size; }

	Node<T>* GetHeadNode() const {
		return head;
	}

	


private:


	int Size;
	Node<T>* head; // первый елемент листа


};


template<typename T>
List<T>::List()
{

	Size = 0;
	head = nullptr;

}

template<typename T>
List<T>::~List()
{
	Clear();
}


template<typename T>
void List<T>::DelInd(int index)
{

	if (index == 0)
	{
		DelFirst();
	}
	else
	{

		Node<T>* previous = this->head;

		for (int i = 0; i < index - 1; i++) {
			previous = previous->pNext;
		}

		Node<T>* DeleteTemp = previous->pNext;

		previous->pNext = DeleteTemp->pNext;

		delete DeleteTemp;

		Size--;

	}
}


template<typename T>
void List<T>::Insert(T data, int index)
{

	if (index == 0)
	{
		AddFront(data);
	}
	else
	{

		Node<T>* previous = this->head;

		for (int i = 0; i < index - 1; i++) {
			previous = previous->pNext;
		}
		// предыдущему елементу присваиваем указатель на новый
		previous->pNext = new Node<T>(data, previous->pNext); // присваиваем новому елементу указатель на след елемент,
		//то есть указатель пред елемента на след елемент
		Size++;

	}

}


template<typename T>
void List<T>::AddFront(T data)
{

	head = new Node<T>(data, head); // создаём новый хед и в качестве указателя на след елемент ставим старый хед
	Size++;


}


template<typename T>
void List<T>::Clear()
{

	while (head != nullptr) // когда САйз будет 0 для вайла это будет фолс
	{
		Node<T>* temp = head;
		head = head->pNext;
		delete temp;
	}
	Size = 0;
}


template<typename T>
void List<T>::DelFirst()
{
	if (head == nullptr)
	{
		cout << "YOU CANT DELETE NOTHING !!!";
	}
	else
	{
		Node<T>* temp = head;
		head = head->pNext; // делаем хедом след елемент
		delete temp;
		Size--;
	}
}


template<typename T>
void List<T>::DelLast()
{

	if (head == nullptr) {
		cout << "CAN`T delete the LAST element; the list is EMPTY." << endl;
	}
	else if (head->pNext == nullptr) {
		// один елемент в листе
		Clear();
	}
	else {

		Node<T>* current = this->head;
		while (current->pNext->pNext != nullptr) {
			current = current->pNext;
		}
		delete current->pNext;
		current->pNext = nullptr;
		Size--;
	}

}


template<typename T>
void List<T>::AddBack(T data)
{

	if (head == nullptr) {

		head = new Node<T>(data); // создание узла первым елементом

	}
	else
	{

		Node<T>* current = this->head; // временная переменная

		while (current->pNext != nullptr) {

			current = current->pNext; // присваивание врем.пер указатель на след елемент пока не дойдём до НУЛЛА

		}
		current->pNext = new Node<T>(data); // и тут когда мы дошли док конца - мы присваеваем адрес новой ноды указателю

	}

	Size++;
}


template<typename T>
void List<T>::Display()
{
	if (head == nullptr)
	{
		cout << "THE LIST IS EMPTY\n";
	}
	else
	{
		Node<T>* current = this->head;
		cout << "\n";
		while (current != nullptr)
		{
			cout << current->data << endl;
			current = current->pNext;
		}
	}
	cout << "\nSize : " << Size << "\n\n";
}




//template<typename T>
//int Compare( T& a,T& b)
//{
//	if (a == b)
//	{
//		return 0;
//	}
//	else
//	{
//		return 1;
//	}
//}


template<typename T>
T& List<T>::operator[](const int index)
{

	int counter = 0;
	Node<T>* current = this->head;

	while (current != nullptr) {

		if (counter == index) {

			return current->data;

		}
		current = current->pNext; // в текущий елемент присваиваем адресс следущего елемента
		counter++;

	}
}

template<typename T>
Node<T>* List<T>::FindElement(T data)
{

	Node<T>* current = head;

	while (current != nullptr)
	{
		if (current->data == data)
		{
			return current;
		}
		else
		{
			current = current->pNext;
		}

	}

	cout << "ELEMENT NOT FOUND" << endl;
	return nullptr;
}


