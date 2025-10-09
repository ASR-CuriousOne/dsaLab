#include "queue.hpp"

template<typename T>
class Stack{
	int capacity = -1;
	ASR::Queue<T> q1,q2;

public:
	Stack(int capacity):q1(capacity),q2(capacity){ capacity = capacity;}

	void push(T data){
		q2.enqueue(data);

		while(!q1.isEmpty()){
			q2.enqueue(q1.dequeue());
		}

		std::swap(q1,q2);
	}

	T pop(){
		return q1.dequeue();
	}

	T peek(){
		return q1.peak();
	}

	bool isEmpty(){
		return q1.isEmpty();
	}

	void display(){
		q1.display();
	}

};

int main(){
	Stack<int> s(3);
    s.push(5);
	s.display();
    s.push(7);
	s.display();
    s.push(9);	
	s.display();
	s.pop();
	s.display();
	s.pop();
	s.display();
	s.pop();
	s.display();
	
    return 0;
}
