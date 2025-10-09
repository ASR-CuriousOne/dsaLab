#include <iostream>
#include <string>
#include <stack>

int main(){
	std::string b;
	std::cin >> b;
	
	std::stack<char> s;
	bool isValid = false;

	for(auto i : b){
		if(i == '(' || i == '{' || i == '['){
			s.push(i);
		}
		else if(i == ')' || i == '}' || i == ']'){
			if(s.empty()){
				isValid = false;
				break;
			}
			if(	i == ')' && s.top() != '(' || 
				i == '}' && s.top() != '{' || 
				i == ']' && s.top() != '['
					){
				isValid = false; break;
			}
			s.pop();
		}
	}

	if(s.empty()) isValid = true;

	if(isValid) std::cout << b << " is valid bracket sequence" << std::endl;
	else std::cout << b << " is not a valid bracket sequence" << std::endl;
}
