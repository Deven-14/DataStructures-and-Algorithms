#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

struct item
{
	int w;
	int v;
};

bool compare(item i1, item i2)
{
	return (static_cast<double>(i1.v)/i1.w)>(static_cast<double>(i2.v)/i2.w);//desending order
}

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
	double value = 0.0;
	vector<item> objects;
	int noOfobjects = static_cast<int>(weights.size());
	for(int j = 0; j < noOfobjects; ++j)
		objects.push_back({weights[j], values[j]});
	sort(objects.begin(), objects.end(), compare);
	
	int i = 0;
	while(i < noOfobjects && capacity > 0)
	{
		int amount = min(objects[i].w, capacity);
		value += amount * static_cast<double>(objects[i].v)/objects[i].w;
		capacity -= amount;
		++i;
	}
	return value;
}

int main() {
	int n;
	int capacity;
	cin >> n >> capacity;
	vector<int> values(n);
	vector<int> weights(n);
	for (int i = 0; i < n; i++) {
		cin >> values[i] >> weights[i];
	}

	double optimal_value = get_optimal_value(capacity, weights, values);

	cout << fixed << setprecision(4);
	cout << optimal_value << endl;
	return 0;
}
