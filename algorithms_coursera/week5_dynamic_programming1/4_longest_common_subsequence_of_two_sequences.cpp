#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using std::vector;

int lcs2(vector<int> &a, vector<int> &b) {
	int n = a.size();
	int m = b.size();
	vector<vector<int>> d(n + 1);
	
	for(int i = 0; i <= n; ++i)//i<=n *********************
	{
		d[i] = vector<int>(m + 1);
		d[i][0] = 0;
	}
	for(int j = 0; j <= m; ++j)
		d[0][j] = 0;
	
	for(int j = 1; j <= m; ++j)//for each column, we are going through the all the rows
	{
		for(int i = 1; i <= n; ++i)
		{
			int insertion = d[i][j - 1];
			int deletion = d[i - 1][j];
			int match = d[i - 1][j - 1] + 1;
			int mismatch = d[i - 1][j - 1];
			if(a[i - 1] == b[j - 1])
				d[i][j] = max(match, max(insertion, deletion));
			else
				d[i][j] = max(mismatch, max(insertion, deletion));
		}
	}
	return d[n][m];
}

int main() {
	size_t n;
	std::cin >> n;
	vector<int> a(n);
	for (size_t i = 0; i < n; i++) {
		std::cin >> a[i];
	}
	
	size_t m;
	std::cin >> m;
	vector<int> b(m);
	for (size_t i = 0; i < m; i++) {
		std::cin >> b[i];
	}
	
	std::cout << lcs2(a, b) << std::endl;
}
