#include <iostream>

unsigned long long binomialCoefficient(int n, int k) {
    unsigned long long result = 1;

    if (k > n - k) {
        k = n - k;
    }

    for (int i = 0; i < k; ++i) {
        result *= (n - i);
        result /= (i + 1);
    }

    return result;
}

unsigned long long countBsts(int n) {
    if (n < 0) {
        return 0;
    }
    unsigned long long coefficient = binomialCoefficient(2 * n, n);
    return coefficient / (n + 1);
}

int main() {
    int n;
    std::cout << "Enter the number of distinct keys: ";
    std::cin >> n;

    if (n < 0) {
        std::cout << "Number of keys cannot be negative." << std::endl;
    } else {
        unsigned long long totalBsts = countBsts(n);
        std::cout << "Total number of distinct BSTs with " << n << " keys is: " << totalBsts << std::endl;
    }

    return 0;
}