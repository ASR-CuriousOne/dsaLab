#include "linkedList.hpp"
#include <iostream>

int main(){
	std::cout << "Singly Linked List Demo " << std::endl;

	ASR::LinkedList linkedList(10);
	std::cout << "Creation with head node only " << std::endl;
	linkedList.Print();
	std::cout << std::endl;

	std::cout << "1. Insertion at Beginning: O(1) " << std::endl;
	linkedList.InsertBegin(20);
	linkedList.Print();
	std::cout << std::endl;

	std::cout << "2. Insert at End: O(n) " << std::endl;
	linkedList.InsertEnd(30);
	linkedList.Print();
	std::cout << std::endl;

	std::cout << "3. Insert at Index 2: O(n)" << std::endl;
	linkedList.InsertAt(40,2);
	linkedList.Print();
	std::cout << std::endl;

	std::cout << "4. Delete from End: O(n)" << std::endl;
	linkedList.DeleteEnd();
	linkedList.Print();
	std::cout << std::endl;

	std::cout << "5. Delete from Begin: O(1)" << std::endl;
	linkedList.DeleteBegin();
	linkedList.Print();

	std::cout << "6. Delete At Pos 1: O(n)" << std::endl;
	linkedList.DeleteAt(1);
	linkedList.Print();
	std::cout << std::endl;

	std::cout << "7. Merge Two List: O(n)" << std::endl;
	ASR::LinkedList linkedList2(11);
	linkedList2.InsertBegin(21);
	linkedList2.InsertBegin(59);
	linkedList2.InsertBegin(42);
	linkedList2.InsertAt(30, 2);
	std::cout << " Other Linked List: " << std::endl;
	linkedList2.Print();
	std::cout << std::endl;
	std::cout << " After Merging: " << std::endl;
	linkedList.MergeAtEnd(linkedList2);
	linkedList.Print();
	std::cout << std::endl;

	std::cout << "8/9. Search and Delete Specific Element 30: O(n)" << std::endl;
	linkedList.DeleteAt(linkedList.Search(30));
	linkedList.Print();
	std::cout << std::endl;

	std::cout << "10. Sorting: O(n^2)" << std::endl;
	linkedList.Sort();
	linkedList.Print();
	std::cout << std::endl;


	std::cout << "11. Reversing List: O(n)" << std::endl;
	linkedList.Reverse();
	linkedList.Print();
	std::cout << std::endl;
	
}
