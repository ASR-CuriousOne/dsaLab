#include "linkedList.hpp"
#include <iostream>

int main(){
	std::cout << "Doubly Linked List Demo " << std::endl;

	ASR::DoublyCircularList doublyCircularList(10,60);
	std::cout << "Creation with head node only " << std::endl;
	doublyCircularList.PrintForward();
	std::cout << std::endl;

	std::cout << "1. Insertion at Beginning: " << std::endl;
	doublyCircularList.InsertBegin(20);
	doublyCircularList.PrintForward();
	std::cout << std::endl;

	std::cout << "2. Insert at End: " << std::endl;
	doublyCircularList.InsertEnd(30);
	doublyCircularList.PrintForward();
	std::cout << std::endl;

	std::cout << "3. Insert at Index 2: " << std::endl;
	doublyCircularList.InsertAt(40,2);
	doublyCircularList.PrintForward();
	std::cout << std::endl;

	std::cout << "4. Delete from End: " << std::endl;
	doublyCircularList.DeleteEnd();
	doublyCircularList.PrintForward();
	std::cout << std::endl;

	std::cout << "5. Delete from Begin: " << std::endl;
	doublyCircularList.DeleteBegin();
	doublyCircularList.PrintForward();

	std::cout << "6. Delete At Pos 1: " << std::endl;
	doublyCircularList.DeleteAt(1);
	doublyCircularList.PrintForward();
	std::cout << std::endl;

	std::cout << "7. Merge Two List: " << std::endl;
	ASR::DoublyCircularList doublyLinkedList2(11,60);
	doublyLinkedList2.InsertBegin(21);
	doublyLinkedList2.InsertBegin(59);
	doublyLinkedList2.InsertBegin(42);
	doublyLinkedList2.InsertAt(30, 2);
	std::cout << " Other Linked List: " << std::endl;
	doublyLinkedList2.PrintForward();
	std::cout << std::endl;
	std::cout << " After Merging: " << std::endl;
	//doublyCircularList.MergeAtEnd(doublyLinkedList2);
	doublyCircularList.PrintForward();
	std::cout << std::endl;

	std::cout << "8/9. Search and Delete Specific Element 30: " << std::endl;
	doublyCircularList.DeleteAt(doublyCircularList.Search(30));
	doublyCircularList.PrintForward();
	std::cout << std::endl;

	std::cout << "10. Sorting: " << std::endl;
	doublyCircularList.Sort();
	doublyCircularList.PrintForward();
	std::cout << std::endl;

	std::cout << "11. Print Backwards: " << std::endl;
	doublyCircularList.PrintBackward();
}


