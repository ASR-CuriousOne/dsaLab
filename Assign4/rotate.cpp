#include <iostream>
#include <vector>

int gcd(int a, int b){
    if(a == 0) return b;

    return gcd(b%a,a);
}

int main(){
	int n,k;
	std::cin >> n >> k;
	std::vector<int> nums(n,0);

	for(auto& i : nums){
		std::cin >> i;
	}
	k = k % n;
	int t = gcd(n,k);
    
    for (int i = 0; i < t; i++) {
        int curr = nums[(i-k+n)%n];
        for (int j = 0; j < n / t; j++) {
            int J = (i+j*k)%n;
            curr = nums[J] ^ curr;
            nums[J] = curr ^ nums[J];
            curr = curr ^ nums[J];
        }
    }

	for(auto& i : nums){
		std::cout << i << ' ';	
	}
	
	std::cout << std::endl;
	
}
