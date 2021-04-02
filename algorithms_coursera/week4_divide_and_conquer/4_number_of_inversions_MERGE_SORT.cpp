#include <iostream>
#include <vector>

using std::vector;

long long merge(vector<int> &a, vector<int> &b, size_t left, size_t right, size_t mid)
{
    //HERE DON'T NEED TO PASS b vector EXTERNALLY, WE CAN MAKE IT A LOCAL VARIABLE******************
	long long number_of_inversions = 0;
	size_t i = left, j = mid + 1, k = left;
	while(i <= mid && j <=right)
	{
		if(a[i] <= a[j])//less than or equal to coz inversions has to be greater
			b[k++] = a[i++];
		else
		{
		    b[k++] = a[j++];// to understand below statement, use eg: 1,2,4,7,10  3,5,8,9, u'll get to know
			number_of_inversions += (mid - i + 1);//for no of ele from I to mid, 
		}
	}
	while(i <= mid)
		b[k++] = a[i++];
	while(j <= right)
		b[k++] = a[j++];
	for(i = left; i <= right; ++i)//temp object
		a[i] = b[i];
	return number_of_inversions;
}

long long get_number_of_inversions(vector<int> &a, vector<int> &b, size_t left, size_t right) {
	long long number_of_inversions = 0;
	if (right <= left) return number_of_inversions;
	size_t mid = left + (right - left) / 2;
	number_of_inversions += get_number_of_inversions(a, b, left, mid);
	number_of_inversions += get_number_of_inversions(a, b, mid + 1, right);
	number_of_inversions += merge(a, b, left, right, mid);
	return number_of_inversions;
}

int main() {
	int n;
	std::cin >> n;
	vector<int> a(n);
	for (size_t i = 0; i < a.size(); i++) {
		std::cin >> a[i];
	}
	vector<int> b(a.size());
	std::cout << get_number_of_inversions(a, b, 0, a.size() - 1) << '\n';
}
