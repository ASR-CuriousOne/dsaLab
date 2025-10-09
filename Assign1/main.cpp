#include "linkedList.hpp"
#include <iostream>

int main(){
	

	ASR::LinkedList linkedList(10);
	linkedList.Print();
	std::cout << '\n';
	linkedList.InsertEnd(20);
	linkedList.Print();
	std::cout << '\n';
	linkedList.InsertBegin(30);
	linkedList.Print();
	std::cout << '\n';
	linkedList.InsertAt(45, 2);
	linkedList.Print();
	std::cout << '\n';
	linkedList.InsertAt(55, 1);
	linkedList.Print();
	std::cout << '\n';

 	linkedList.Reverse();
	linkedList.Print();
	std::cout << '\n';

	
	//linkedList.DeleteBegin();
	//linkedList.Print();
	//std::cout << '\n';

	//linkedList.DeleteAt(2);
	//linkedList.Print();
	//std::cout << '\n';

	//linkedList.DeleteEnd();
	//linkedList.Print();
	//std::cout << '\n';

	ASR::Node* found = linkedList.Search(20);
	std::cout << "Addr: " << found << '\n';
	if(found != nullptr){
		std::cout << "Data: " << found->data << " Next: " << found->next <<"\n\n";
	}

	linkedList.Sort();
	linkedList.Print();
	std::cout << '\n';



}
