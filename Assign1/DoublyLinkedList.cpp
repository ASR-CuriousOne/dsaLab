#include "linkedList.hpp"
#include <iostream>
#include <stdexcept>
#include <utility>
namespace ASR{

	DoublyLinkedList::DoublyLinkedList(int data){
		head = new DoubleNode(data);
	}	

	void DoublyLinkedList::InsertBegin(int data){
		if(head == nullptr) std::runtime_error("Head is null");

		DoubleNode* newNode = new DoubleNode;

		newNode->data = data;
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}

	void DoublyLinkedList::InsertEnd(int data){
		if(head == nullptr) std::runtime_error("Head is null");
		DoubleNode* temp = head;
		for(;temp->next != nullptr;temp = temp->next){
		}
		DoubleNode* newNode = new DoubleNode(data);
		newNode->prev = temp;
		temp->next = newNode;

	}

	void DoublyLinkedList::InsertAt(int data, int pos){
		if(pos == 0){
			InsertBegin(data); return;
		}

		if(head == nullptr) std::runtime_error("Head is null");

		DoubleNode* newNode = new DoubleNode(data);

		for(DoubleNode* temp = head; temp->next != nullptr; temp = temp->next,pos--){
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

	void DoublyLinkedList::PrintForward(){
		int pos = 0;
		for(DoubleNode* temp = head; temp != nullptr; temp = temp->next,pos++){
			std::cout << "Pos: " << pos << " Data: " << temp->data << " Next: " << temp->next << " Prev: " << temp->prev << '\n';
		}
	}
	void DoublyLinkedList::PrintBackward(){
		int pos = 0;
		DoubleNode* temp = head;
		for(; temp->next != nullptr; temp = temp->next,pos++){
			
		}
		for(;temp != nullptr; temp = temp->prev,pos--){
			std::cout << "Pos: " << pos << " Data: " << temp->data << " Next: " << temp->next << " Prev: " << temp->prev << '\n';
		}
	}

	void DoublyLinkedList::DeleteBegin(){
		
		DoubleNode* temp = head;
		head = head->next;
		head->prev = nullptr;
		delete temp;
	}

	void DoublyLinkedList::DeleteAt(int pos){
		if(pos == 0){
			DeleteBegin();
			return;
		}

		for(DoubleNode* temp = head; temp->next->next != nullptr; temp = temp->next,pos--){
			if(pos==1){
				DoubleNode* toBeDeleted = temp->next;
				temp->next = temp->next->next;
				temp->next->prev = temp;
				delete toBeDeleted;
				break;
			}
		}
		if(pos == 1){
			DeleteEnd();
		}

	}

	void DoublyLinkedList::DeleteEnd(){
		DoubleNode* temp = head;
		for(; temp->next->next != nullptr; temp = temp->next){}
		DoubleNode* toBeDeleted = temp->next;
		temp->next = nullptr;
		delete toBeDeleted;
	}

	int DoublyLinkedList::Search(int data){
		DoubleNode* temp = head;
		int pos = 0;
		for(;temp != nullptr;temp = temp->next,pos++){
			if(temp->data == data) {return pos;}
		}
		return -1;
	}

	void DoublyLinkedList::Sort(){
		bool isSorted = true;
		do{
		for(DoubleNode* temp = head;temp->next != nullptr;temp = temp->next){
			if(temp->next->data < temp->data){
				std::swap(temp->next->data,temp->data);
				isSorted = false;
			}
			else{isSorted = true;}
		}
		}while(!isSorted);

	}
	
	void DoublyLinkedList::MergeAtEnd(const DoublyLinkedList& newOne){
		DoubleNode* temp = head;
		for(; temp->next != nullptr; temp = temp->next){}
		temp->next = newOne.head;
		newOne.head->prev = temp;
	}
}

