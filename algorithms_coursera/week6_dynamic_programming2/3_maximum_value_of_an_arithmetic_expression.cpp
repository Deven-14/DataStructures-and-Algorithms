#include <iostream>
#include <cassert>
#include <string>
#include <cctype>
#include <algorithm>
#include <climits>
#include <vector>
using namespace std;
using std::vector;
using std::string;
using std::max;
using std::min;

long long eval(long long a, long long b, char op) {
	if (op == '*') {
		return a * b;
	} else if (op == '+') {
		return a + b;
	} else if (op == '-') {
		return a - b;
	} else {
		assert(0);
	}
}

struct Pair
{
	long long Max;
	long long Min;
};

Pair MaxAndMin(int i, int j, vector<char> &operators, vector<vector<long long>> &Min, vector<vector<long long>> &Max)
{
	long long m = LONG_MAX;
	long long M = LONG_MIN;
	for(int k = i; k < j; ++k)//***<j coz we do k+1 down
	{
		long long a = eval(Min[i][k], Max[k + 1][j], operators[k - 1]);//operators[k-1] coz starts from index 0
		long long b = eval(Max[i][k], Min[k + 1][j], operators[k - 1]);
		long long c = eval(Min[i][k], Min[k + 1][j], operators[k - 1]);
		long long d = eval(Max[i][k], Max[k + 1][j], operators[k - 1]);
		M = max(M, max(a, max(b, max(c , d))));//******* do it with M inside also, coz M changes in the loop
		m = min(m, min(a, min(b, min(c , d))));
	}
	return {M, m};
}

long long get_maximum_value(const string &exp) {
	vector<int> numbers;
	vector<char> operators;
	/*size_t i = 0;
	while(i < exp.size())
	{
		int start = i;
		while(isdigit(exp[i]))
			++i;
		numbers.push_back(stoi(exp.substr(start, i)));
		if(exp[i] != '\0')
			operators.push_back(exp[i++]);
	}*/
	for(size_t i = 0; i < exp.size(); ++i)
	{
		if(isdigit(exp[i]))
			numbers.push_back(exp[i]-'0');
		else
			operators.push_back(exp[i]);
	}
	
	vector<vector<long long>> Min(numbers.size() + 1);
	vector<vector<long long>> Max(numbers.size() + 1);
	
	for(size_t k = 1; k <= numbers.size(); ++k)
	{
		Min[k] = vector<long long>(numbers.size() + 1);
		Max[k] = vector<long long>(numbers.size() + 1);
		Min[k][k] = numbers[k - 1];
		Max[k][k] = numbers[k - 1];
	}
	
	for(size_t k = 1; k < numbers.size(); ++k)
	{
		for(size_t i = 1; i <= numbers.size() - k; ++i)
		{
			int j = i + k;
			Pair p = MaxAndMin(i, j, operators, Min, Max);
			Max[i][j] = p.Max;
			Min[i][j] = p.Min;
		}
	}
	
	/*for(i = 1; i <= numbers.size(); ++i)
	{
	    for(int j = 1; j <= numbers.size(); ++j)
	    {
	        cout << Max[i][j] << " ";
	    }
	    cout << endl;
	}
	for(i = 1; i <= numbers.size(); ++i)
	{
	    for(int j = 1; j <= numbers.size(); ++j)
	    {
	        cout << Min[i][j] << " ";
	    }
	    cout << endl;
	}
	*/
	return Max[1][numbers.size()];
}

int main() {
	string s;
	std::cin >> s;
	std::cout << get_maximum_value(s) << '\n';
}
