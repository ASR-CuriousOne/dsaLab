#include "BST.hpp"
#include <algorithm>

int main(){
	ASR::BST<int> bst;

	bst.insert(30);
	bst.insert(40);
	bst.insert(10);
	bst.insert(20);
	bst.insert(50);
	bst.insert(5);
	bst.print(ASR::Order::PreOrder);
	bst.print(ASR::Order::InOrder);
	bst.print(ASR::Order::PostOrder);
	bst.print(ASR::Order::LevelOrder);
	bst.serializePreOrder();

	bst.printDepths();
	bst.printHeights();

	std::cout << bst.getSuccessor(10) << std::endl;

	bst.remove(50);
	bst.remove(30);

	bst.print(ASR::Order::InOrder);
	bst.print(ASR::Order::LevelOrder);

	bst.deleteTree();

	bst.print(ASR::Order::InOrder);

	bst.constructFromInorderPreorder({5, 10, 20, 30, 40, 50}, {30, 10, 5, 20, 40, 50});

	bst.print(ASR::Order::InOrder);
	bst.print(ASR::Order::LevelOrder);

	bst.deleteTree();

	bst.constructFromInorderPostorder({5, 15, 20, 30, 80, 90}, {5, 20, 15, 90, 80, 30});
	bst.print(ASR::Order::InOrder);
	bst.print(ASR::Order::LevelOrder);

	
	
}
