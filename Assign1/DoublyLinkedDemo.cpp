#include "linkedList.hpp"
#include <iostream>

int main(){
	std::cout << "Doubly Linked List Demo " << std::endl;

	ASR::DoublyLinkedList doublyLinkedList(10);
	std::cout << "Creation with head node only " << std::endl;
	doublyLinkedList.PrintForward();
	std::cout << std::endl;

	std::cout << "1. Insertion at Beginning: O(1)" << std::endl;
	doublyLinkedList.InsertBegin(20);
	doublyLinkedList.PrintForward();
	std::cout << std::endl;

	std::cout << "2. Insert at End: O(n)" << std::endl;
	doublyLinkedList.InsertEnd(30);
	doublyLinkedList.PrintForward();
	std::cout << std::endl;

	std::cout << "3. Insert at Index 2: O(n)" << std::endl;
	doublyLinkedList.InsertAt(40,2);
	doublyLinkedList.PrintForward();
	std::cout << std::endl;

	std::cout << "4. Delete from End: O(n)" << std::endl;
	doublyLinkedList.DeleteEnd();
	doublyLinkedList.PrintForward();
	std::cout << std::endl;

	std::cout << "5. Delete from Begin: O(1)" << std::endl;
	doublyLinkedList.DeleteBegin();
	doublyLinkedList.PrintForward();

	std::cout << "6. Delete At Pos 1: O(n)" << std::endl;
	doublyLinkedList.DeleteAt(1);
	doublyLinkedList.PrintForward();
	std::cout << std::endl;

	std::cout << "7. Merge Two List: O(1)" << std::endl;
	ASR::DoublyLinkedList doublyLinkedList2(11);
	doublyLinkedList2.InsertBegin(21);
	doublyLinkedList2.InsertBegin(59);
	doublyLinkedList2.InsertBegin(42);
	doublyLinkedList2.InsertAt(30, 2);
	std::cout << " Other Linked List: " << std::endl;
	doublyLinkedList2.PrintForward();
	std::cout << std::endl;
	std::cout << " After Merging: " << std::endl;
	doublyLinkedList.MergeAtEnd(doublyLinkedList2);
	doublyLinkedList.PrintForward();
	std::cout << std::endl;

	std::cout << "8/9. Search and Delete Specific Element 30: O(n)" << std::endl;
	doublyLinkedList.DeleteAt(doublyLinkedList.Search(30));
	doublyLinkedList.PrintForward();
	std::cout << std::endl;

	std::cout << "10. Sorting: O(n)" << std::endl;
	doublyLinkedList.Sort();
	doublyLinkedList.PrintForward();
	std::cout << std::endl;

	std::cout << "11. Print Backwards: " << std::endl;
	doublyLinkedList.PrintBackward();
}

