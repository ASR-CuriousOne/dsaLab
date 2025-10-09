#include "BST.hpp"
#include <algorithm>

int main(){
	ASR::BST<int> bst;

	bst.Insert(30);
	bst.Insert(50);
	bst.Insert(20);
	bst.Insert(25);
	bst.Insert(27);
	bst.Insert(55);
	bst.Insert(49);
	bst.print(ASR::Order::PreOrder);
	bst.print(ASR::Order::InOrder);
	bst.print(ASR::Order::PostOrder);
}
