#include "linkedList.hpp"
#include <iostream>
#include <stdexcept>
#include <utility>
namespace ASR{

	SinglyCircularList::SinglyCircularList(int dataBegin,int dataEnd){
		head = new Node(dataBegin);
		Node* end = new Node(dataEnd);
		head->next = end;
		end->next = head;
	}	

	Node* SinglyCircularList::GetEnd() const{
		Node* end = head;

		while(end->next != head) end = end->next;

		return end;
	}

	void SinglyCircularList::InsertBegin(int data){
		if(head == nullptr) std::runtime_error("Head is null");

		Node* newNode = new Node;
		newNode->data = data;
		newNode->next = head;
		Node* end = GetEnd();
		end->next = newNode;
		head = newNode;
	}

	void SinglyCircularList::InsertEnd(int data){
		if(head == nullptr) std::runtime_error("Head is null");

		Node* newNode = new Node;
		newNode->data = data;

		Node* temp = head;
		while(temp->next != head){
			temp = temp->next;
		}

		temp->next = newNode;
		newNode->next = head;
	}

	void SinglyCircularList::InsertAt(int data, int pos){
		if(pos == 0){
			InsertBegin(data); return;
		}

		if(head == nullptr) std::runtime_error("Head is null");

		Node* newNode = new Node;
		newNode-> data = data;

		for(Node* temp = head; temp->next != head; temp = temp->next,pos--){
			if(pos == 1){
				newNode->next = temp->next;
				temp->next = newNode;
				return;
			}

		}
	}

	void SinglyCircularList::Print(){
		int pos = 0;
		bool isFirst = true;
		for(Node* temp = head; temp != head || isFirst; temp = temp->next,pos++){
			std::cout << "Pos: " << pos << " Data: " << temp->data << " Next: " << temp->next << '\n';
			isFirst = false;
		}
	}

	void SinglyCircularList::DeleteBegin(){
		
		Node* temp = head;
		Node* end = GetEnd();
		head = head->next;
		end->next = head;
		delete temp;
	}

	void SinglyCircularList::DeleteAt(int pos){
		if(pos == 0){
			DeleteBegin();
			return;
		}
		std::cout << pos << '\n';

		for(Node* temp = head; temp->next != head; temp = temp->next,pos--){
			if(pos==1){
				Node* toBeDeleted = temp->next;
				temp->next = temp->next->next;
				delete toBeDeleted;
			}
		}

	}

	void SinglyCircularList::DeleteEnd(){
		Node* temp = head;
		for(; temp->next->next != head; temp = temp->next){}
		Node* toBeDeleted = temp->next;
		temp->next = head;
		delete toBeDeleted;
	}

	int SinglyCircularList::Search(int data){
		Node* temp = head;
		int pos = 0;
		for(;temp->next != head;temp = temp->next,pos++){
			if(temp->data == data) {return pos;}
		}
		return -1;
	}

	void SinglyCircularList::Sort(){
		bool isSorted = true;
		do{
			bool isFirst = true;
		for(Node* temp = head;temp->next != head || isFirst;temp = temp->next){
			if(temp->next->data < temp->data){
				std::swap(temp->next->data,temp->data);
				isSorted = false;
			}
			else{isSorted = true;}
			isFirst = false;
		}
		}while(!isSorted);

	}

	void SinglyCircularList::Reverse(){
		Node* prevNode = head;
		Node* currNode = head->next;
		Node* newHead = head->next->next;
		Node* end = GetEnd();
		head->next = end;
		while(newHead->next != head){
			currNode->next = prevNode;
			prevNode = currNode;
			currNode = newHead;
			newHead = newHead->next;
		}
		currNode->next = prevNode;
		newHead->next = currNode;

		head = newHead;
	}
	
	void SinglyCircularList::MergeAtEnd(const SinglyCircularList& newOne){
		Node* end = GetEnd();
		end->next = newOne.head;
		Node* newend = newOne.GetEnd();
		newend->next = head;

	}
}

