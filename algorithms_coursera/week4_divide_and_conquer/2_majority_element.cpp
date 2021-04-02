#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

int count(vector<int> &a, int left, int right, int element)
{
	if(element == -1)
		return -1;
	int c = 0;
	for(int i = left; i <= right; ++i)
		if(a[i] == element)
			++c;
	return c;
}

int get_majority_element(vector<int> &a, int left, int right) {
	if (left > right) return -1;
	if (left == right) return a[left];
	int mid = (left + right) / 2;
	int leftNum = get_majority_element(a, left, mid);
	int rightNum = get_majority_element(a, mid + 1, right);
	int leftCount = count(a, left, right, leftNum);
	//int rightCount = count(a, left, right, rightNum);instead of doing this here, i'm putting it down, coz, if leftcount> n/2 then no need to do this
	if(leftCount > (right - left + 1) / 2)//right - left + 1 = no of ele, and then that / 2
		return leftNum;
	int rightCount = count(a, left, right, rightNum);
	if(rightCount > (right - left + 1) / 2)
		return rightNum;
	return -1;
}
//INSTEAD OF USING DIVIDE AND CONQUER, U COULD USE SORT AND MAINLY THERE IS ONE WAY WHERE U CAN DO THIS IN O(N) BY SCANING THE SEQUENCE TWICE
int main() {
	int n;
	std::cin >> n;
	vector<int> a(n);
	for (size_t i = 0; i < a.size(); ++i) {
		std::cin >> a[i];
	}
	std::cout << (get_majority_element(a, 0, a.size() - 1) != -1) << '\n';//*********a.size()-1 **************
}
