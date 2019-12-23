#pragma once

template <class T>
struct Node
{
	Node(const Node& copyNode);
	Node(T Data = 0);
	T data;
	Node* next;
};

template <class T>
class List
{
public:
	List(const List& copyList);
	List() : begin(nullptr), size(0) {}
	void push_back(T element);
	void pop_back();
	void pop_front();
	List& operator=(const List&);
	T getElement(int index) const;
	int getSize() { return size; }
	void changeElement(int index, T element);
	Node<T>* getBegin() { return begin; }
	~List();
private:
	Node<T>* begin;
	int size;
	Node<T>* getEnd();
};

template <class T>
Node<T>::Node(const Node& copyNode) :
	data(copyNode.data), next(copyNode.next) {}

template <class T>
Node<T>::Node(T Data) : data(Data), next(nullptr) {}

template <class T>
List<T>::List<T>(const List& copyList)
{
	if (copyList.begin == nullptr)
	{
		begin = nullptr;
		size = 0;
	}
	else
	{
		int i = 0;
		size = copyList.size;
		Node<T>* copyTemp = copyList.begin;
		begin = new Node<T>(copyTemp->data);
		Node<T>* temp = begin;
		while (i != size - 1)
		{
			copyTemp = copyTemp->next;
			temp->next = new Node<T>(copyTemp->data);
			temp = temp->next;
			i++;
		}
	}
}

template <class T>
Node<T>* List<T>::getEnd()
{
	if (begin == nullptr)
		throw("List is empty");
	Node<T>* temp = begin;
	while (temp->next != nullptr)
		temp = temp->next;
	return temp;
}

template<class T>
void List<T>::push_back(T element)
{
	if (begin == nullptr)
	{
		begin = new Node<T>(element);
		size++;
	}
	else
	{
		Node<T>* temp = getEnd();
		temp->next = new Node<T>(element);
		size++;
	}
}

template<class T>
void List<T>::pop_back()
{
	if (begin == nullptr)
		throw ("List is empty");
	else
	{
		Node<T>* temp = begin;
		if (temp->next != nullptr)
			while (temp->next->next != nullptr)
				temp = temp->next;
		delete temp->next;
		temp->next = nullptr;
		size--;
		if (size == 0)
			begin = nullptr;
	}
}

template<class T>
void List<T>::pop_front()
{
	if (begin == nullptr)
		throw ("List is empty");
	else
	{
		Node<T>* temp = begin;
		begin = temp->next;
		delete temp;
		size--;
	}
}

template<class T>
List<T>& List<T>::operator=(const List<T>& copyList)
{
	if (this == &copyList)
		return *this;
	if (begin != nullptr)
		delete this;
	size = copyList.size;
	if (copyList.begin == nullptr)
	{
		begin = nullptr;
		return *this;
	}
	int i = 0;
	Node<T>* copyTemp = copyList.begin;
	begin = new Node<T>(copyTemp->data);
	Node<T>* temp = begin;
	while (i != size - 1)
	{
		copyTemp = copyTemp->next;
		temp->next = new Node<T>(copyTemp->data);
		temp = temp->next;
		i++;
	}
	return *this;
}

template<class T>
T List<T>::getElement(int index) const
{

	if (begin == nullptr || index < 0 || index >= size)
		throw("Error");
	Node<T>* temp = begin;
	int i = 0;
	while (i != index)
	{
		temp = temp->next;
		i++;
	}
	return temp->data;
}

template<class T>
void List<T>::changeElement(int index, T element)
{
	if (begin == 0 || index < 0 || index >= size)
		throw("Error");
	Node<T> * temp = begin;
	int i = 0;
	while (i != index)
	{
		temp = temp->next;
		i++;
	}
	temp->data = element;
}

template<class T>
List<T>::~List()
{
	while (begin != nullptr)
		pop_front();
}