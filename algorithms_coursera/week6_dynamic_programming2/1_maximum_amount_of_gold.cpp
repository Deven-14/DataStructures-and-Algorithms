#include <iostream>
#include <vector>

using std::vector;

int optimal_weight(int W, const vector<int> &w) {
	vector<vector<int>> maxWeight(w.size() + 1);//rows
	for(size_t i = 0; i <= w.size(); ++i)
		maxWeight[i] = vector<int>(W + 1);//columns
	
	for(int j = 0; j <= W; ++j)
		maxWeight[0][j] = 0;
	for(size_t i = 0; i <= w.size(); ++i)
		maxWeight[i][0] = 0;
	
	for(size_t i = 1; i <= w.size(); ++i)
	{
		for(int j = 1; j <= W; ++j)
		{
		    maxWeight[i][j] = maxWeight[i - 1][j];//************j not w[i-1]
			if(w[i-1] <= j)
			{
				int val = maxWeight[i - 1][j - w[i-1]] + w[i-1];//w[i-1] and not w[i] coz the weights start from index 0************************
				if(val > maxWeight[i][j])
					maxWeight[i][j] = val;
			}
		}
	}
	
	return maxWeight[w.size()][W];
}

int main() {
	int n, W;
	std::cin >> W >> n;
	vector<int> w(n);
	for (int i = 0; i < n; i++) {
		std::cin >> w[i];
	}
	std::cout << optimal_weight(W, w) << '\n';
}
