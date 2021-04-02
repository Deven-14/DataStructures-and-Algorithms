#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int lcs3(vector<int> &a, vector<int> &b, vector<int> &c) {
	int n = a.size();//n is 3, 3 sequences, (1,2) and (2,3) and (1,3)
	int m = b.size();
	int p = c.size();
	vector<vector<vector<int>>> d(p + 1);//i.e (n x m) p times i.e p blocks of nxm
	
	for(int i = 0; i <= p; ++i)//i<=n *********************
	{
		d[i] = vector<vector<int>>(n + 1);//rows
		for(int j = 0; j <= n; ++j)//j<=m**************
		{
			d[i][j] = vector<int>(m + 1);//columns
			d[i][j][0] = 0;
		}
		for(int j = 0; j <= m; ++j)//j<=p**********
			d[i][0][j] = 0;
	}
	
	for(int j = 1; j <= m; ++j)//for each column, we are going through the all the rows
		for(int i = 1; i <= n; ++i)//each row
				d[0][i][j] = 0;
	
	for(int k = 1; k <= p; ++k)//each block, i.e each no in c vector is check with the whole 1st block i.e nxm, if c vector is 1 3 5 then 1 is checked with nxm then 1,3 is checked with nxm then 1,3,5 is checked with nxm 
	{
		for(int j = 1; j <= m; ++j)//for each column, we are going through the all the rows
		{
			for(int i = 1; i <= n; ++i)//each row
			{
				//match = d[k - 1][i - 1][j - 1] + 1;
				//mismatch = max(d[k - 1][i][j], max(d[k][i][j-1], d[k][i-1][j]));
				if(a[i - 1] == b[j - 1] && b[j - 1] == c[k - 1])
					d[k][i][j] = d[k - 1][i - 1][j - 1] + 1;//match; here we don't need to see the maximum of match, insertion and deletion, coz  we need it to be match, and if it is a proper match then it'll increment by 1 or else remain the same
				else
					d[k][i][j] = max(d[k - 1][i][j], max(d[k][i][j-1], d[k][i-1][j]));//mismatch; i.e mismatched then inserted and deleted value, max of these three is given if not equal
				//d[k - 1][i][j]- mismatch, d[k][i][j-1]-insertion, d[k][i-1][j]-deletion, max of these three
				//d[k - 1][i - 1][j - 1] + 1= match coz, 1 1 1, when equal then 1 1 is equal so what we did that time is d[k-1][i-1][j-1]+1, coz if the 1 1 has already come then it'll be 1+1=2 or else if it came in that level(row) itself then it would be 0+1=1 which is same as d[k-1][i][j], 
			}
		}
	}
	
    /*for(int i = 0; i <= p; ++i)
    {
        for(int j = 0; j <= n; ++j)
        {
            for(int k = 0; k <= m; ++k)
                cout << d[i][j][k] << " ";
            cout << endl;
        }
        cout << endl;
	}*/
	
	return d[p][n][m];
}

int main() {
	size_t an;
	std::cin >> an;
	vector<int> a(an);
	for (size_t i = 0; i < an; i++) {
		std::cin >> a[i];
	}
	
	size_t bn;
	std::cin >> bn;
	vector<int> b(bn);
	for (size_t i = 0; i < bn; i++) {
		std::cin >> b[i];
	}
	
	size_t cn;
	std::cin >> cn;
	vector<int> c(cn);
	for (size_t i = 0; i < cn; i++) {
		std::cin >> c[i];
	}
	
	std::cout << lcs3(a, b, c) << std::endl;
}
