#include <iostream>
#include <utility>
#include <vector>
#include <stack>

int main(){
	int n;
	std::cin >> n;

	std::vector<int> a(n,0);
	std::vector<int> res(n,0);

	std::stack<std::pair<int, int>> s;

	for(auto& i : a){
		std::cin >> i;
	}
	for(int i = a.size() - 1; i > -1; i--){
		while(!s.empty() && s.top().first <= a[i]){
			s.pop();
		}
		if(!s.empty()){
			res[i] = s.top().second - i;
		}

		s.push({a[i],i});
	}

	for(auto i : res){
		std::cout << i << ' ';
	}
	std::cout << std::endl;
}
