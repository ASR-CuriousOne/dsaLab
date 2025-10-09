#include "stack.hpp"

template<typename T>
class Queue{
	ASR::Stack<T> s1,s2;
	public:

	Queue(int capacity): s1(capacity),s2(capacity){}
	
	void enqueue(T data){
		s1.push(data);
	}
	void display(){
		s2.printReverse();
		s1.print();
	}

	T dequeue(){
		if(s1.isEmpty() && s2.isEmpty()){
			throw std::runtime_error("Queue is empty!!!!");
		}
		
		if (s2.isEmpty()) {
            while (!s1.isEmpty()) {
                s2.push(s1.pop());
                
            }
        }
		return s2.pop();
	}

	void peek(){
		return s1.peak();
	}

	bool isEmpty(){
		return s1.isEmpty();
	}
};


int main(){
	Queue<int> q(3);

	q.enqueue(8);
	q.display();
	q.enqueue(5);
	q.display();
	q.enqueue(9);
	q.display();
	q.dequeue();
	q.display();
	q.dequeue();
	q.display();
	q.dequeue();
	q.display();


}
