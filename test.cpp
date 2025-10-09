#include <iostream>
#include <vector>

int main(){
	int n = 0;
	std::cin >> n;

	std::vector<int> a(n,0);

	for(auto& i : a){
		std::cin >> i;
	}

	int s = 0,e = n - 1;
	int minVal = 0;
	bool first = true;
	while(true){	
		if(a[s] <= a[e]){
			minVal = a[first ? s : s + 1]; 	
			break;
		}
		first = false;

		int k = s + (e-s)/2;

		if(a[k] > a[s]){
			s = k;
		}
		else{
			e = k;
		}

		std::cout << s << ' ' << e << ' ' << k << std::endl;

		
	}

	std::cout << minVal << std::endl;


}
