#include "stack.hpp"

int main(){
	ASR::Stack stack(10);

	for(int i = 0; i < stack.getCapacity(); i++){
		stack.push(((i+69)^7) % 20);
	}

	stack.print();

}
