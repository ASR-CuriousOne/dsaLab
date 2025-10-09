#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

namespace ASR {

struct Node{
	int data = 0;
	Node* next = nullptr;
	
	Node(){
		data = 0; next = nullptr;
	}

	Node(int data){
		this->data = data;
	}

	Node(int data,Node* next){
		this->data = data;
		this->next = next;
	}
};

struct DoubleNode{
	int data = 0;
	DoubleNode* prev = nullptr;
	DoubleNode* next = nullptr;

	DoubleNode(): data(0) , next(nullptr), prev(nullptr){}

	DoubleNode(int data): data(data), next(nullptr), prev(nullptr){}
	
	DoubleNode(int data,DoubleNode* next, DoubleNode* prev): data(data), next(next), prev(prev){}
};

class LinkedList{
private:
	Node* head = nullptr;
public:
	LinkedList(int data);

	void InsertBegin(int data);

	void InsertEnd(int data);

	void InsertAt(int data,int pos);

	void DeleteBegin();

	void DeleteEnd();

	void DeleteAt(int pos);

	int Search(int data);

	void Sort();

	void MergeAtEnd(const LinkedList& newOne);

	void Reverse();

	void Print();

	int Count();

	Node* Max();

	Node* Min();
};



class DoublyLinkedList{
private:
	DoubleNode* head = nullptr;
public:
	DoublyLinkedList(int data);

	void InsertBegin(int data);

	void InsertEnd(int data);

	void InsertAt(int data,int pos);

	void DeleteBegin();

	void DeleteEnd();

	void DeleteAt(int pos);

	int Search(int data);

	void Sort();

	void MergeAtEnd(const DoublyLinkedList& newOne);

	void PrintForward();
	void PrintBackward();

	int Count();

	DoubleNode* Max();

	DoubleNode* Min();
};

class SinglyCircularList{
private:
	Node* head = nullptr;
public:
	SinglyCircularList(int dataBegin,int dataEnd);

	Node* GetEnd() const;

	void InsertBegin(int data);

	void InsertEnd(int data);

	void InsertAt(int data,int pos);

	void DeleteBegin();

	void DeleteEnd();

	void DeleteAt(int pos);

	int Search(int data);

	void Sort();

	void MergeAtEnd(const SinglyCircularList& newOne);

	void Reverse();

	void Print();

	int Count();

	DoubleNode* Max();

	DoubleNode* Min();
};

class DoublyCircularList{
private:
	DoubleNode* head = nullptr;
public:
	DoublyCircularList(int dataBeg,int dataEnd);

	void InsertBegin(int data);

	void InsertEnd(int data);

	void InsertAt(int data,int pos);

	void DeleteBegin();

	void DeleteEnd();

	void DeleteAt(int pos);

	int Search(int data);

	void Sort();

	void MergeAtPos(const DoublyCircularList& newOne,const int posInit,const int posSec);

	void PrintForward();
	void PrintBackward();

	int Count();

	DoubleNode* Max();

	DoubleNode* Min();
};

}


#endif
