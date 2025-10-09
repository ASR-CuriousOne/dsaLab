#include <deque>
#include <iostream>
#include <vector>

int main(){
	int n,k;
	std::cin >> n >> k;
	std::vector<int> a(n,0);
	std::vector<int> r;
	for(auto& i : a){
		std::cin >> i;
	}
	
	std::deque<int> d;

	for(int i = 0; i < k && i < n; i++){
		while(!d.empty() && a[d.back()] <= a[i]){
			d.pop_back();
		} 
		d.push_back(i);
	}

	for(int i = k; i < n; i++){
		r.push_back(a[d.front()]);

		while(!d.empty() && d.front() <= i-k){
			d.pop_front();	
		}

		while(!d.empty() && a[d.back()] <= a[i]){
			d.pop_back();
		}
		d.push_back(i);
	}
	r.push_back(a[d.front()]);

	for(auto i : r){
		std::cout << i << ' ';
	}
	std::cout << std::endl;
	
}
