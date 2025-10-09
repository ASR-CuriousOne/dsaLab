#ifndef STACK_HPP
#define STACK_HPP
#include <stdexcept>
#include <iostream>

namespace ASR{
	template<typename T>
	class Stack{
		T* arr = nullptr;
		int top = -1;
		int capacity = 0;
public:
		Stack(int capacity): capacity(capacity){
			arr = new T[capacity];
		}

		bool isEmpty(){
			return top < 0;
		}

		bool isFull(){
			return top > capacity - 2;
		}

		void push(const T& data){
			if(isFull()) throw std::runtime_error("Stack Overflow!!!!!");
			arr[++top] = data;
		}

		T pop(){	
			if(isEmpty()) throw std::runtime_error("Stack Underflow!!!!!");
			T value = arr[top]; top--;
    		return value; 
		}		

		T peak(){
			if(isEmpty()) throw std::runtime_error("Stack is Empty");
			T val = arr[top];
			return val;
		}

		T getAtIndex(int index){
			if(index < 0 || index > top) throw std::runtime_error("OutOfBounds");
			return arr[index];
		}
		 
		void print(){
			for(int i = top; i > -1;i--){
				std::cout << arr[i] << ' ';
			}
			std::cout << std::endl;
		}

		int size(){
			return top+1;
		}

		int getCapacity(){
			return capacity;
		}

		~Stack(){
			delete[] arr;
		}
	};

	template<typename T>
	struct Node{
		T data = 0;
		Node* next = nullptr;

		Node();

		Node(T data, Node<T>* next): data(data),next(next){}
	};

	template<typename T>
	class LinkedStack{
		Node<T>* head = nullptr;
public:
		LinkedStack(){};

		bool isEmpty(){return head == nullptr;}

		bool isFull(){return false; }

		void push(T data){
			if(isFull()) throw std::runtime_error("Stack Overflow!!!!!");
			Node<T>* newNode = new Node<T>(data,head);	
			head = newNode;
		};

		T pop(){
			if(isEmpty()) throw std::runtime_error("Stack Underflow!!!!!");
			Node<T>* temp = head;
			T data = head->data;
			head = head->next;
			delete temp;
			return data;
		}		

		T peak(){
			if(isEmpty()) throw std::runtime_error("Stack is Empty");
			return head->data;

		}

		T getAtIndex(int index){
			if(isEmpty()) throw std::runtime_error("Stack is Empty");
			Node<T>* temp = head;
			while(index > 0){
				if(temp->next == nullptr) throw std::runtime_error("End Of Stack Reached!");
				temp = temp->next;
				index--;
			}
			return temp->data;
		}
		 
		void print(){
			if(isEmpty()) throw std::runtime_error("Stack is Empty");
			Node<T>* temp = head;
			while(temp != nullptr){
				std::cout << temp->data << ' ';	
				temp = temp->next;
			}
			std::cout << std::endl;
		}
		~LinkedStack(){
			Node<T>* temp = head;
			while(temp != nullptr){
				Node<T>* toBeDeleted = temp;
				temp = temp->next;
				delete toBeDeleted;
			}
		
		}

	};

}

#endif
