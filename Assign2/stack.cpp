#include "stack.hpp"
#include <stdexcept>
#include <iostream>

namespace ASR {
	template<typename T>
	Stack<T>::Stack(int capacity): capacity(capacity){
			arr = new T[capacity];
	}

	template<typename T>
	bool Stack<T>::isEmpty(){
		return top < 0;
	}

	template<typename T>
	bool Stack<T>::isFull(){
		return top > capacity - 1;
	}
	
	template<typename T>
	void Stack<T>::push(T data){
		arr[++top] = data;
	}

	template<typename T>
	T Stack<T>::pop(){	
		return arr[top--];
	}
	
	template<typename T>
	Stack<T>::~Stack(){
		delete[] arr;
	}

	template<typename T>
	T Stack<T>::getAtIndex(int index){
		if(index < 0 || index > top) std::runtime_error("OutOfBounds");
		return arr[index];
	}
	
	template<typename T>
	void Stack<T>::print(){
		for(int i = top; i > -1;i--){
			std::cout << arr[i] << ' ';
		}
		std::cout << std::endl;
	}
	
	template<typename T>
	int Stack<T>::size(){
		return top+1;
	}

	template<typename T>
	int Stack<T>::getCapacity(){
		return capacity;
	}

}

