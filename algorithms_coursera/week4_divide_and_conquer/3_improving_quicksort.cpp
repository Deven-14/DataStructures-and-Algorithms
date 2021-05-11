#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
/*
int partition2(vector<int> &a, int l, int r) {
	//their method
	int x = a[l];
	int j = l;
	for (int i = l + 1; i <= r; i++) {
		if (a[i] <= x) {
			j++;
			swap(a[i], a[j]);
		}
	}
	swap(a[l], a[j]);
	//my method
	int p = l++;
	while(a[r] > a[p])
		--r;
	while(l < r && a[l] <= a[p])
		++l;
	while(l < r)
	{
		swap(a[l++], a[r--]); // where swap is placed also matters...
		while(a[r] > a[p]) // "the last element gets swapped twice(last ele and pivot is one of the 2 cases)--allowed"
			--r;
		while(a[l] <= a[p])//smaller element is swapped last, so j (r) has to be found first.....order of finding j(r) and i(l) matters....
			++l;
	}
	swap(a[p], a[r]);// only i>j case gets terminated
	return r;
}*/

struct Pair
{
	int p1;
	int p2;
	Pair(int p1 = 0, int p2 = 0) : p1(p1), p2(p2) {}
};

Pair partition3(vector<int> &a, int l, int r) {
	int p1 = l, p2 = l++;
	while(a[r] > a[p2])
		--r;
	while(l < r && a[l] <= a[p2])
		++l;
	while(l < r)
	{
		swap(a[l++], a[r--]);
		while(a[r] > a[p2])
			--r;
		while(a[l] <= a[p2])
			++l;
	}
	swap(a[p2], a[r]);
	p2 = r;
	int i = p2 - 1;
	while(a[p1] < a[p2])
		++p1;
	while(i > p1 && a[i] == a[p2])
		--i;
	while(p1 < i)
	{
		swap(a[p1++], a[i--]);
		while(a[p1] < a[p2])
			++p1;
		while(a[i] == a[p2])
			--i;
	}
	return Pair(p1, p2);
}

void randomized_quick_sort(vector<int> &a, int l, int r) {
	/*if (l >= r) {
		return;
	}

	int k = l + rand() % (r - l + 1);
	swap(a[l], a[k]);
	Pair p = partition3(a, l, r);

	randomized_quick_sort(a, l, p.p1 - 1);
	randomized_quick_sort(a, p.p2 + 1, r);*/
	while(l < r)
	{
		int k = l + rand() % (r - l + 1);
		swap(a[l], a[k]);
		Pair p = partition3(a, l, r);
		
		if((p.p1 - l) < (r - p.p2))// '<' coz, we should make a call to small subarray, coz then we'll do recursive call on sub of that subarray, so it'll be even smaller, and hence smaller arrays implies less recursive calls, so smaller array
		{
			randomized_quick_sort(a, l, p.p1 - 1);
			l = p.p2 + 1;
		}
		else
		{
			randomized_quick_sort(a, p.p2 + 1, r);
			r = p.p1 - 1;
		}
	}
}

int main() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (size_t i = 0; i < a.size(); ++i) {
		cin >> a[i];
	}
	randomized_quick_sort(a, 0, a.size() - 1);
	for (size_t i = 0; i < a.size(); ++i) {
		cout << a[i] << ' ';
	}
	cout << endl;
}
