#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long MaxPairwiseProduct(const vector<int>& numbers) {
    long long max_product = 0;
    int n = numbers.size();

    int max_index1 = 0, max_index2 = 0;
	
	for(int i = 1; i < n; ++i)
		if(numbers[i] > numbers[max_index1])
			max_index1 = i;
	if(max_index1 == 0)
		max_index2 = 1;//or else max_index2 = 0; in initialization
	for(int j = 0; j < n; ++j)
		if(j != max_index1 && numbers[j] > numbers[max_index2])
			max_index2 = j;
	
	max_product = static_cast<long long>(numbers[max_index1]) * numbers[max_index2];
	
    return max_product;
}

int main() {
    int n;
    cin >> n;
    vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }

    cout << MaxPairwiseProduct(numbers) << "\n";
    return 0;
}
