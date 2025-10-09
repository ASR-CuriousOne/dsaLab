#include "linkedList.hpp"
#include <iostream>

int main(){
	std::cout << "Singly Linked List Demo " << std::endl;

	ASR::SinglyCircularList linkedCircularList(10,60);
	std::cout << "Creation with head node only " << std::endl;
	linkedCircularList.Print();
	std::cout << std::endl;

	std::cout << "1. Insertion at Beginning: " << std::endl;
	linkedCircularList.InsertBegin(20);
	linkedCircularList.Print();
	std::cout << std::endl;

	std::cout << "2. Insert at End: " << std::endl;
	linkedCircularList.InsertEnd(30);
	linkedCircularList.Print();
	std::cout << std::endl;

	std::cout << "3. Insert at Index 2: " << std::endl;
	linkedCircularList.InsertAt(40,2);
	linkedCircularList.Print();
	std::cout << std::endl;

	std::cout << "4. Delete from End: " << std::endl;
	linkedCircularList.DeleteEnd();
	linkedCircularList.Print();
	std::cout << std::endl;

	std::cout << "5. Delete from Begin: " << std::endl;
	linkedCircularList.DeleteBegin();
	linkedCircularList.Print();

	std::cout << "6. Delete At Pos 1: " << std::endl;
	linkedCircularList.DeleteAt(1);
	linkedCircularList.Print();
	std::cout << std::endl;

	std::cout << "7. Merge Two List: " << std::endl;
	ASR::SinglyCircularList linkedList2(11,24);
	linkedList2.InsertBegin(21);
	linkedList2.InsertBegin(59);
	linkedList2.InsertBegin(42);
	linkedList2.InsertAt(30, 2);
	std::cout << " Other Linked List: " << std::endl;
	linkedList2.Print();
	std::cout << std::endl;
	std::cout << " After Merging: " << std::endl;
	linkedCircularList.MergeAtEnd(linkedList2);
	linkedCircularList.Print();
	std::cout << std::endl;

	std::cout << "8/9. Search and Delete Specific Element 30: " << std::endl;
	linkedCircularList.DeleteAt(linkedCircularList.Search(30));
	linkedCircularList.Print();
	std::cout << std::endl;

	std::cout << "10. Sorting: " << std::endl;
	linkedCircularList.Sort();
	linkedCircularList.Print();
	std::cout << std::endl;


	std::cout << "11. Reversing List: " << std::endl;
	linkedCircularList.Reverse();
	linkedCircularList.Print();
	std::cout << std::endl;
	
}

