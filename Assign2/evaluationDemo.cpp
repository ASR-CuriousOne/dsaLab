#include "stack.hpp"
#include <functional>
#include <cmath>
#include <iostream>
#include <map>
#include <stdexcept>

class Oper{

	char m_txt = 0;
	int m_precidence = 0;	
	std::function<float(float,float)> m_operation = [](float x,float y){return 0;};

public:
	Oper(){
		m_txt = 0; m_precidence = 0; m_operation = [](float x, float y){return 0;};
	};

	Oper(const char& txt,int precidence,std::function<float(float,float)> operation): m_txt(txt), m_precidence(precidence),m_operation(operation) {}

	bool isOper(char txt){
		return m_txt == txt;
	}
	int getPrecidence() { return m_precidence; }

	char getTxt(){
		return m_txt;
	}

	float operate(float a,float b){return m_operation(a,b);}

	friend std::ostream& operator<<(std::ostream& os, const Oper& oper);
	
};

Oper allOpers[] = {
	Oper('+',1,[](float x,float y){return x+y;}),
	Oper('-',1,[](float x,float y){return x-y;}),
	Oper('*',2,[](float x,float y){return x*y;}),
	Oper('/',2,[](float x,float y){if(y == 0) throw std::runtime_error("Division By Zero");return x/y;}),
	Oper('^',3,[](float x,float y){return std::pow(x,y);}),
	Oper('(',4,[](float x,float y){return 0;}),
	Oper(')',4,[](float x,float y){return 0;})

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

float evaluatePostfix(const std::string& postfix,const std::map<char, float>& values){
	int n = postfix.size();
	ASR::Stack<float> operands(n);	
	
	for(int i = 0; i < n; i++){
		if(postfix[i] == ' ') continue;
		
		bool isOper= false;
		for(auto o : allOpers){
			if(o.isOper(postfix[i])){
				isOper = true;
				float val2 = operands.pop();
				float val1 = operands.pop();

				float result = o.operate(val1, val2);
				operands.push(result);
			}
		}	

		if(!isOper){
			operands.push(values.at(postfix[i]));
		}
	}

	return operands.peak();
}

float evaluatePrefix(const std::string& prefix,const std::map<char, float>& values){
	int n = prefix.size();
	ASR::Stack<float> operands(n);	
	
	for(int i = n-1; i > -1; i--){
		if(prefix[i] == ' ') continue;
		bool isOper= false;
		for(auto o : allOpers){
			if(o.isOper(prefix[i])){
				isOper = true;
				float val1 = operands.pop();
				float val2 = operands.pop();

				float result = o.operate(val1, val2);

				operands.push(result);
			}
		}	

		if(!isOper){
			operands.push(values.at(prefix[i]));
		}
	}

	return operands.peak();

}

float evaluateInfix(const std::string& infix,const std::map<char,float>& values){
	return evaluatePostfix(infixToPostfix(infix), values);
}

std::map<char, float> createMapFromString(std::string values) {
    std::map<char, float> charIntMap;
    
    for (size_t i = 0; i < values.size(); ++i) {
        if (std::isalpha(values[i])) {
            char key = values[i];
            i += 4; 
            
            std::string numStr;
            while (i < values.size() && std::isdigit(values[i])) {
                numStr += values[i];
                i++;
            }
            
            float value = std::stoi(numStr);
            charIntMap[key] = value;
        }
    }
    
    return charIntMap;
}

int main(){
	int fixType = 1;
    std::string input;

    std::cout << "Fix Evaluator:\nInfix [1]\nPrefix 2\nPostFix 3\nSelect the Input Format: ";
    std::cin >> fixType;

	if(!(fixType > 0 && fixType < 4)){
		throw std::runtime_error("Invalid Type Choose between 1,2 and 3");
	
	}

    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Type expression: ";
    std::getline(std::cin, input);
	
	std::string values;

	std::cout << "Type Values: ";
	std::getline(std::cin,values);

	auto valueMap = createMapFromString(values);

	switch(fixType){
		case 1:
			{
				float ans = evaluateInfix(input,valueMap);
				std::cout << input << " = " << ans << std::endl; 
				break;
			}
		case 2:
			{
				float ans = evaluatePrefix(input,valueMap);
				std::cout << input << " = " << ans << std::endl; 
				break;
			}
		case 3:
			{
				float ans = evaluatePostfix(input,valueMap);
				std::cout << input << " = " << ans << std::endl;
				break;
			}
		default:
			{
				std::cout << "Input a correct choice between 1,2 and 3" << std::endl;
			}
				
	}
}
