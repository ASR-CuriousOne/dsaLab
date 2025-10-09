#include "linkedList.hpp"
#include <iostream>
#include <stdexcept>
#include <utility>
namespace ASR{

	LinkedList::LinkedList(int data){
		head = new Node(data);
	}	

	void LinkedList::InsertBegin(int data){
		if(head == nullptr) std::runtime_error("Head is null");

		Node* newNode = new Node;

		newNode->data = data;
		newNode->next = head;
		head = newNode;
	}

	void LinkedList::InsertEnd(int data){
		if(head == nullptr) std::runtime_error("Head is null");

		Node* newNode = new Node;
		newNode->data = data;

		Node* temp = head;
		while(temp->next != nullptr){
			temp = temp->next;
		}

		temp->next = newNode;
	}

	void LinkedList::InsertAt(int data, int pos){
		if(pos == 0){
			InsertBegin(data); return;
		}

		if(head == nullptr) std::runtime_error("Head is null");

		Node* newNode = new Node;
		newNode-> data = data;

		for(Node* temp = head; temp->next != nullptr; temp = temp->next,pos--){
			if(temp->next == nullptr){
				std::runtime_error("Reached End Of List");
			}
			if(pos == 1){
				newNode->next = temp->next;
				temp->next = newNode;
				return;
			}

		}
	}

	void LinkedList::Print(){
		int pos = 0;
		for(Node* temp = head; temp != nullptr; temp = temp->next,pos++){
			std::cout << "Pos: " << pos << " Data: " << temp->data << " Next: " << temp->next << '\n';
		}
	}

	void LinkedList::DeleteBegin(){
		
		Node* temp = head;
		head = head->next;
		delete temp;
	}

	void LinkedList::DeleteAt(int pos){
		if(pos == 0){
			DeleteBegin();
			return;
		}

		for(Node* temp = head; temp->next != nullptr; temp = temp->next,pos--){
			if(pos==1){
				Node* toBeDeleted = temp->next;
				temp->next = temp->next->next;
				delete toBeDeleted;
				break;
			}
		}

	}

	void LinkedList::DeleteEnd(){
		Node* temp = head;
		for(; temp->next->next != nullptr; temp = temp->next){}
		Node* toBeDeleted = temp->next;
		temp->next = nullptr;
		delete toBeDeleted;
	}

	int LinkedList::Search(int data){
		Node* temp = head;
		int pos = 0;
		for(;temp != nullptr;temp = temp->next,pos++){
			if(temp->data == data) {return pos;}
		}
		return -1;
	}

	void LinkedList::Sort(){
		bool isSorted = true;
		do{
		for(Node* temp = head;temp->next != nullptr;temp = temp->next){
			if(temp->next->data < temp->data){
				std::swap(temp->next->data,temp->data);
				isSorted = false;
			}
			else{isSorted = true;}
		}
		}while(!isSorted);

	}

	void LinkedList::Reverse(){
		Node* prevNode = head;
		Node* currNode = head->next;
		Node* newHead = head->next->next;
		prevNode->next = nullptr;
		while(newHead->next != nullptr){
			currNode->next = prevNode;
			prevNode = currNode;
			currNode = newHead;
			newHead = newHead->next;
		}
		currNode->next = prevNode;
		newHead->next = currNode;

		head = newHead;
		
	}
	
	void LinkedList::MergeAtEnd(const LinkedList& newOne){
		Node* temp = head;
		for(; temp->next != nullptr; temp = temp->next){}
		temp->next = newOne.head;
	}
}
