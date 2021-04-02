#include <iostream>
#include <cassert>
#include <vector>

using std::vector;

int binary_search(const vector<int> &a, int x) {
	int low = 0, high = static_cast<int>(a.size()) - 1, mid = 0;
	while(low <= high)
	{
		mid = (low + high) / 2;
		if(a[mid] == x)
			return mid;
		else if(x > a[mid])
			low = mid + 1;
		else
			high = mid - 1;
	}
	return -1;
}

/*
int linear_search(const vector<int> &a, int x) {
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] == x) return i;
  }
  return -1;
}*/

int main() {
	int n;
	std::cin >> n;
	vector<int> a(n);
	for (size_t i = 0; i < a.size(); i++) {
		std::cin >> a[i];
	}
	int m;
	std::cin >> m;
	vector<int> b(m);
	for (int i = 0; i < m; ++i) {
		std::cin >> b[i];
	}
	for (int i = 0; i < m; ++i) {
		std::cout << binary_search(a, b[i]) << ' ';
	}
}
