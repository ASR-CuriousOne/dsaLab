#include "stack.hpp"
#include <iostream>
#include <string>

int main(){
	std::cout << "Array Stack Demo" << std::endl;
	std::cout << "Creating Stack with capacity 3" << std::endl;
	ASR::Stack<int> integers(3);
	std::cout << std::endl;

	std::cout << "Pushing 2 and 7 to stack" << std::endl;	
	integers.push(2);
	integers.push(7);	
	integers.print();
	std::cout << std::endl;
	
	std::cout << "Checking if stack is full or not" << std::endl;
	std::cout << (integers.isFull() ? "Stack is full!\n" : "Stack is not full\n") << std::endl;

	std::cout << "Pushing 3 to stack" << std::endl;
	integers.push(3);
	integers.print();
	std::cout  <<std::endl;
	
	
	std::cout << "Checking if stack is full or not" << std::endl;	
	std::cout << (integers.isFull() ? "Stack is full!" : "Stack is not full") << std::endl;
	std::cout << std::endl;
	
	std::cout << "Reversing Array" << std::endl;
	int inArray[] = {1,2,4,8,10};

	ASR::Stack<int> rev(sizeof(inArray)/sizeof(int));

	std::cout << "Initial Array: " << std::endl;

	for(int i : inArray){
		std::cout << i << ' '; 
		rev.push(i);	
	}
	std::cout << std::endl;

	std::cout << std::endl;
	std::cout << "Reversed Array: " << std::endl;
	rev.print();
	std::cout << std::endl;

		
	std::string input;
	std::cout << "Type string to checked: ";
	std::cin >> input;
	int n = input.size();

	ASR::LinkedStack<char> revstring;

	for(int i = 0; i < n/2; i++){
		revstring.push(input[i]);
	}

	int offset = n % 2 == 0 ? 0 : 1;
	bool isPalindrome = true;
	for(int i = n/2 + offset; i < n; i++){
		if(input[i] != revstring.pop()) {
			isPalindrome = false;
			break;
		}
	}

	std::cout << (isPalindrome ? input + " is a Palindrome" : input + " is not a Palindrome") << std::endl;

}
