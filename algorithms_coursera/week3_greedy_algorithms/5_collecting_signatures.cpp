#include <iostream>
#include <climits>
#include <algorithm>
#include <vector>
using namespace std;

struct Segment {
	int start, end;
};

bool compareLeftEnd(Segment s1, Segment s2)
{
	return s1.start < s2.start;
}

vector<int> optimal_points(vector<Segment> &segments) {
	vector<int> points;
	sort(segments.begin(), segments.end(), compareLeftEnd);
	int n = static_cast<int>(segments.size());
	int point;
	
	int i = 0;
	while(i < n)
	{
		point = segments[i].end;
		while(i < n-1 && point >= segments[i+1].start)
		{
			++i;
			if(segments[i].end < point)
				point = segments[i].end;
		}
		points.push_back(point);
		++i;
	}
	return points;
}

int main() {
	int n;
	cin >> n;
	vector<Segment> segments(n);
	for (size_t i = 0; i < segments.size(); ++i) {
		cin >> segments[i].start >> segments[i].end;
	}
	vector<int> points = optimal_points(segments);
	cout << points.size() << "\n";
	for (size_t i = 0; i < points.size(); ++i) {
		cout << points[i] << " ";
	}
	cout << endl;
}
