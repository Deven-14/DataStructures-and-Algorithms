#include <iostream>
#include <vector>

using namespace std;

vector<int> optimal_summands(int n) {
	vector<int> summands;
	summands.push_back(1);
	--n;
	int i = 0;
	while(summands[i] + 1 <= n)
	{
		summands.push_back(summands[i++] + 1);
		n -= summands[i];
	}
	summands[i] += n;
	return summands;
}

int main() {
	int n;
	cin >> n;
	vector<int> summands = optimal_summands(n);
	cout << summands.size() << '\n';
	for (size_t i = 0; i < summands.size(); ++i) {
		cout << summands[i] << ' ';
	}
	cout << endl;
	return 0;
}
