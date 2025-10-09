#include "linkedList.hpp"
#include <iostream>
#include <stdexcept>
#include <utility>
namespace ASR{

	DoublyCircularList::DoublyCircularList(int dataBeg,int dataEnd){
		head = new DoubleNode(dataBeg);
		DoubleNode* end = new DoubleNode(dataEnd);
		head->next = end;
		head->prev = end;

		end->next = head;
		end->prev = head;
	}	

	void DoublyCircularList::InsertBegin(int data){
		if(head == nullptr) std::runtime_error("Head is null");

		DoubleNode* newNode = new DoubleNode;

		newNode->data = data;
		newNode->next = head;
		newNode->prev = head->prev;
		head->prev->next = newNode;
		head->prev = newNode;
		head = newNode;
	}

	void DoublyCircularList::InsertEnd(int data){
		if(head == nullptr) std::runtime_error("Head is null");

		InsertBegin(data);
		head = head->next;
	}

	void DoublyCircularList::InsertAt(int data, int pos){
		if(pos == 0){
			InsertBegin(data); return;
		}

		if(head == nullptr) std::runtime_error("Head is null");

		DoubleNode* newNode = new DoubleNode(data);

		for(DoubleNode* temp = head; temp->next != head; temp = temp->next,pos--){
			if(temp->next == nullptr){
				std::runtime_error("Reached End Of List");
			}
			if(pos == 1){
				newNode->next = temp->next;
				temp->next = newNode;
				newNode->next->prev = newNode;
				newNode->prev = temp;
				return;
			}

		}
	}

	void DoublyCircularList::PrintForward(){
		int pos = 0;
		bool isFirst = true;
		for(DoubleNode* temp = head; temp != head || isFirst; temp = temp->next,pos++){
			std::cout << "Pos: " << pos << " Data: " << temp->data << " Next: " << temp->next << '\n';
			isFirst = false;
		}
	}
	void DoublyCircularList::PrintBackward(){
		int pos = 0;
		DoubleNode* temp = head->prev;
		for(;temp != head; temp = temp->prev,pos--){
			std::cout << "Pos: " << pos << " Data: " << temp->data << " Next: " << temp->next << '\n';
		}
	}

	void DoublyCircularList::DeleteBegin(){
		
		DoubleNode* temp = head;
		head = head->next;
		head->prev = temp->prev;
		head->prev->next = head;
		delete temp;
	}

	void DoublyCircularList::DeleteAt(int pos){
		if(pos == 0){
			DeleteBegin();
			return;
		}

		for(DoubleNode* temp = head; temp->next != head; temp = temp->next,pos--){
			if(pos==1){
				DoubleNode* toBeDeleted = temp->next;
				temp->next = temp->next->next;
				temp->next->prev = temp;
				delete toBeDeleted;
			}
		}

	}

	void DoublyCircularList::DeleteEnd(){
		DoubleNode* toBeDeleted = head->prev;
		toBeDeleted->prev->next = head;
		head->prev = toBeDeleted->prev;
		delete toBeDeleted;
	}

	int DoublyCircularList::Search(int data){
		DoubleNode* temp = head;
		int pos = 0;
		for(;temp != head;temp = temp->next,pos++){
			if(temp->data == data) {return pos;}
		}
		return pos;
	}

	void DoublyCircularList::Sort(){
		bool isSorted = true;
		do{
		for(DoubleNode* temp = head;temp->next != head;temp = temp->next){
			if(temp->next->data < temp->data){
				std::swap(temp->next->data,temp->data);
				isSorted = false;
			}
			else{isSorted = true;}
		}
		}while(!isSorted);

	}
	
	void DoublyCircularList::MergeAtPos(const DoublyCircularList& newOne,const int posInit,const int posSec){
		DoubleNode* temp = head;
		for(; temp->next != nullptr; temp = temp->next){}
		temp->next = newOne.head;
		newOne.head->prev = temp;
	}
}


