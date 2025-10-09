#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <stdexcept>
#include <iostream>
#include <utility>


namespace ASR{
	template<typename T>
	class Queue{
		T* arr;
		int capacity = 0;
		int size = -1;
		int front = -1;
		int rear = -1;
		public:
		Queue(int capacity): capacity(capacity){
			arr = new T[capacity];
			front = capacity - 1;
			rear = capacity - 1;
			size = 0;

		}

		Queue(Queue&& other) noexcept {
			other.arr = arr;
			other.size = size;
			other.front = front;
			other.rear = rear;
			other.capacity = capacity;

			capacity = 0;
			front = 0;
			rear = 0;
			size = 0;
			arr = nullptr;

		}

		Queue& operator=(Queue&& other) noexcept{
			other.arr = arr;
			other.size = size;
			other.front = front;
			other.rear = rear;
			other.capacity = capacity;

			return 

		}

		bool isEmpty(){
			return size == 0;
		}

		bool isFull(){
			return size == capacity;
		}

		void enqueue(T data){
			if(isFull()) throw std::runtime_error("Queue is Full!!!");
			rear = (rear + 1) % capacity;
			size++;
			arr[rear] = data;
		}

		T dequeue(){
			if(isEmpty()) throw std::runtime_error("Queue is Empty!!!");
			front = (front + 1) % capacity;
			size--;
			return arr[front];
		}

		T peak(){
			if(isEmpty()) throw std::runtime_error("Queue is Empty!!!");
			return arr[(front+1)%capacity];
		}

		void display(){
			int start = (front + 1) % capacity;
			for(int i = 0; i < size; i++){
				std::cout << arr[(i + start) % capacity] << ' ';
			}
			std::cout << '\n';
		}

		void swap(Queue<T>& q2){
			std::swap(arr,q2.arr);
			std::swap(capacity,q2.capacity);
			std::swap(front,q2.front);
			std::swap(rear,q2.rear);
			std::swap(size,q2.size);
		}

		~Queue(){
			std::cout << "queue deleted" << std::endl;
			delete[] arr;
		}
	};
	
	template<typename T>
	struct Node{
		T data = 0;
		Node* next = nullptr;

		Node(){
			data = 0; next = nullptr;
		}
		Node(T data,Node* next): data(data),next(next){}
	};

	template<typename T>
		class LinkedQueue{
			Node<T>* front = nullptr;
			Node<T>* rear = nullptr;
public:
			LinkedQueue():front(nullptr), rear(nullptr){}

			bool isEmpty(){
				return front == nullptr;
			}

			bool isFull(){
				return false;
			}

			void enqueue(T data){
				Node<T>* newNode = new Node<T>(data,nullptr);
				if(isEmpty() && rear == nullptr){
					front = newNode;
					rear = newNode;
					return;
				}
				if(isFull()) throw std::runtime_error("Queue is full!!!!!!!!");
				rear->next = newNode;
				rear = newNode;
			}

			T dequeue(){
				if(isEmpty()) throw std::runtime_error("Queue is Empty!!!!!");
				Node<T>* toBeDeleted = front;
				front = front->next;
				if(front == nullptr) rear = nullptr;
				T value = toBeDeleted->data;
				delete toBeDeleted;
				return value;
			}

			T peak(){
				if(isEmpty()) throw std::runtime_error("Queue is Empty!!!!");
				return front->data;
			}
			void display(){
				for(Node<T>* temp = front;temp != nullptr; temp=temp->next){
					std::cout << temp->data << ' ';
				}
				std::cout << std::endl;
			}

			~LinkedQueue(){
				for(Node<T>* temp = front;temp != nullptr;){
					Node<T>* toBeDeleted = temp;
					temp = temp->next;
					delete toBeDeleted;
				}
				std::cout << "Linked queue deleted" << std::endl;
			}
		};
}

#endif
