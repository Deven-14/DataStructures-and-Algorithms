#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool compare(string &s1, string &s2)
{
	/*unsigned int i = 0, j = 0;
	while(s1[i] == s2[j])
	{
		unsigned int tempi = i, tempj = j;
		if(i + 1 < s1.size())
			++i;
		if(j + 1 < s2.size())
			++j;
		if(tempi == i && tempj == j)
			return s1 >= s2;
	}
	return s1[i] > s2[j];*/
	/*int a = stoi(s1 + s2);
	int b = stoi(s2 + s1);
	return a >= b;*/
	return s1+s2 > s2+s1;
}

void largest_number(vector<string> &a) {
	sort(a.begin(), a.end(), compare);
	//string result = "";
	for(auto x:a)
		cout << x;
	cout << endl;
		//result += x;// don't do result = result + a[i]; here coz, that'll waste time and space***************
	//return result;
}

int main() {
	int n;
	cin >> n;
	vector<string> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	//string result = 
	largest_number(a);
	//cout << result << endl;
}
