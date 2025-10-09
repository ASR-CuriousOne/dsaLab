#include <iostream>
#include "stack.hpp"
#include <string>

bool isOper(char s){
    return s == '+' || s == '-' || s == '*' || s == '/' || s == '*' || s == '^';
}

std::string convertToPostfix(const std::string& prefix){
    int n = prefix.size();
    ASR::Stack<std::string> operands(n);
    for(int i = n - 1; i > -1; i--){
        char s = prefix[i];
        if(s == ' ') continue;

        if(isOper(s)){
            std::string oper1 = operands.pop();
            std::string oper2 = operands.pop();

            std::string result = oper1 + oper2 +s;

            operands.push(result);
        }
        else{
            std::string result;
			result.push_back(s);
			operands.push(result);
        }
        //operands.print();
    }

    return operands.peak();

}

int main(){

    std::string prefix;

    std::getline(std::cin ,prefix);

    std::cout << convertToPostfix(prefix) << std::endl;
}

