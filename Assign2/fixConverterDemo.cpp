#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include "stack.hpp"
#include <functional>
#include <string_view>


class Oper{

	char m_txt = 0;
	int m_precidence = 0;	
	std::function<int(int,int)> m_operation = [](int x,int y){return 0;};

public:
	Oper(){
		m_txt = 0; m_precidence = 0; m_operation = [](int x, int y){return 0;};
	};

	Oper(const char& txt,int precidence,std::function<int(int,int)> operation): m_txt(txt), m_precidence(precidence),m_operation(operation) {}

	bool isOper(char txt){
		return m_txt == txt;
	}
	int getPrecidence() { return m_precidence; }

	char getTxt(){
		return m_txt;
	}

	int operate(int a,int b){return m_operation(a,b);}

	friend std::ostream& operator<<(std::ostream& os, const Oper& oper);
	
};

Oper allOpers[] = {
	Oper('+',1,[](int x,int y){return x+y;}),
	Oper('-',1,[](int x,int y){return x-y;}),
	Oper('*',2,[](int x,int y){return x*y;}),
	Oper('/',2,[](int x,int y){if(y == 0) throw std::runtime_error("Division By Zero");return x/y;}),
	Oper('^',3,[](int x,int y){return std::pow(x,y);}),
	Oper('(',4,[](int x,int y){return 0;}),
	Oper(')',4,[](int x,int y){return 0;})

};

std::ostream& operator<<(std::ostream& os, const Oper& oper){
		os << oper.m_txt;
    	return os;	
	};

std::string infixToPostfix(const std::string& infixExp){
	ASR::Stack<Oper> opers(100);

	std::string postFix = "";

	for(char s : infixExp){

		//std::cout << postFix << ' ';
		//opers.print();
		//std::cout << std::endl;

		bool isOper = false;

		if(s == ' ') continue;

		//if(s == '('){ opers.push(allOpers[5]); continue;}
		if(s == ')'){ 
			while(!opers.isEmpty()){
				char poped = opers.pop().getTxt();
				if(poped == '(') { break;}
				
				postFix.push_back(poped);
			}
			continue;
		}

		for(auto o : allOpers){
			if(o.isOper(s)){
				if(opers.isEmpty() || opers.peak().getPrecidence() < o.getPrecidence()){					
					opers.push(o);	
				}
				else{
					while(!opers.isEmpty() && opers.peak().getPrecidence() >= o.getPrecidence()){
						if(opers.peak().getTxt() == '(') break;
						postFix.push_back(opers.pop().getTxt());
					}
					opers.push(o);
				}
				isOper = true;
				break;
			}
		}

		if(!isOper) postFix.push_back(s);
		
	}

	while(!opers.isEmpty()){
		postFix.push_back(opers.pop().getTxt());
	}

	return postFix;	
}

std::string prefixToInfix(const std::string& prefix){
	int n = prefix.size();
	ASR::Stack<std::string> operands(n);

	for(int i = n - 1; i > -1; i--){
		bool isOper = false;
		for(auto o : allOpers){
			if(o.isOper(prefix[i])){
				isOper = true;
				std::string pre = operands.pop();
				std::string post = operands.pop();

				std::string result = "(" + pre + o.getTxt() + post + ")";

				operands.push(result);
			}
		}

		if(!isOper){
			std::string s;
			s.push_back(prefix[i]);
			operands.push(s);
		}
	}

	return operands.peak();
}

std::string infixToPrefix(const std::string& infix){
	std::string prefix = infix;
	std::reverse(prefix.begin(),prefix.end());
	for (int i = 0; i < prefix.size(); i++) {
        if (prefix[i] == '(') {
            prefix[i] = ')';
        } else if (prefix[i] == ')') {
            prefix[i] = '(';
        }
    }
	prefix = infixToPostfix(prefix);
	std::reverse(prefix.begin(),prefix.end());
	return prefix;
}

int main(){

	int fixType = 1;
    std::string input;

    std::cout << "Fix Converter:\nInfix [1]\nPrefix 2\nSelect the Input Format: ";
    std::cin >> fixType;
	if(!(fixType > 0 && fixType < 3)){
		throw std::runtime_error("Invalid Type Choose between 1,2");
	
	}
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Type expression: ";
    std::getline(std::cin, input);
	
	std::string infix,prefix,postfix;
	switch (fixType) {
		case 1:
			postfix = infixToPostfix(input);
			prefix = infixToPrefix(input);
			std::cout << "Infix:   " << input << std::endl; 
			std::cout << "Prefix:  " << prefix << std::endl;
			std::cout << "Postfix: " << postfix << std::endl;

			break;
		case 2:
			infix = prefixToInfix(input);
			std::cout << "Infix:   " << infix << '\n';
			std::cout << "Prefix:  " << input << '\n';
			break;
	}
}
