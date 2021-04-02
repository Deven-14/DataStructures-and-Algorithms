#include <iostream>
using namespace std;

int gcd(int a, int b)
{
	int temp;
	while(b > 0)
	{
		temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

long long lcm(int a, int b)
{
	int gcd_ = gcd(a, b);
	long long lcm_ = (static_cast<long long>(a) * b) / static_cast<long long>(gcd_);
	return lcm_;
}

int main()
{
	int a, b;
	cin >> a >> b;
	cout << lcm(a, b) << endl;
	return 0;
}