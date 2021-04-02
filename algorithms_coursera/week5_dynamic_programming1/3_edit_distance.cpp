#include <iostream>
#include <vector>
#include <string>
using namespace std;

int edit_distance(const string &str1, const string &str2) {
	int n = str1.size();
	int m = str2.size();
	vector<vector<int>> d(n + 1);
	
	for(int i = 0; i <= n; ++i)//i<=n *********************
	{
		d[i] = vector<int>(m + 1);
		d[i][0] = i;
	}
	for(int j = 0; j <= m; ++j)
		d[0][j] = j;
	
	for(int j = 1; j <= m; ++j)//for each column, we are going through the all the rows
	{
		for(int i = 1; i <= n; ++i)
		{
			int insertion = d[i][j - 1] + 1;
			int deletion = d[i - 1][j] + 1;
			int match = d[i - 1][j - 1];
			int mismatch = d[i - 1][j - 1] + 1;
			if(str1[i - 1] == str2[j - 1])
				d[i][j] = min(match, min(insertion, deletion));
			else
				d[i][j] = min(mismatch, min(insertion, deletion));
		}
	}
	return d[n][m];
}

int main() {
	string str1;
	string str2;
	std::cin >> str1 >> str2;
	std::cout << edit_distance(str1, str2) << std::endl;
	return 0;
}
