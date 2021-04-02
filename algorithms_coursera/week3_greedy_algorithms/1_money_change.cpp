#include <iostream>
using namespace std;

int get_change(int m) {
	int n = 0;
	int change = 10;
	while(m != 0)
	{
		while(m >= change)
		{
			m -= change;
			n++;
		}
		if(change == 10)
			change = 5;
		else if(change == 5)
		{
			change = 1;
			n += m;// m = 3, so 3 = 1+1+1, i.e nothing but n+=m
			m =0;
		}
	}
	return n;
}

int main() {
	int m;
	cin >> m;
	cout << get_change(m) << '\n';
}
