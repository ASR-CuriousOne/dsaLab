#include "queue.hpp"

int main(){
	ASR::Queue<int> q(4);
	std::cout << "Queue using circular array." << std::endl << std::endl;
	std::cout << "Enqueue 10, 50, 40" << std::endl; 
	q.enqueue(10);
	q.enqueue(50);
	q.enqueue(40);
	q.display();
	std::cout << std::endl;
	std::cout << "Dequeue" << std::endl; 
	q.dequeue();
	q.display();

	ASR::LinkedQueue<int> linkedQueue;
	std::cout << "Queue using linked." << std::endl << std::endl;
	std::cout << "Enqueue 20, 60, 50" << std::endl; 
	linkedQueue.enqueue(20);
	linkedQueue.enqueue(60);
	linkedQueue.enqueue(50);
	linkedQueue.display();
	std::cout << std::endl;
	std::cout << "Dequeue" << std::endl; 
	linkedQueue.dequeue();
	linkedQueue.display();


}
