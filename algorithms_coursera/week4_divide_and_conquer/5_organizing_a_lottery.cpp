#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>
using namespace std;

struct Point{
	int p;//point
	char ch;//role
	int actual_index;
	Point(int x, char c, int i = 0): p(x), ch(c), actual_index(i){}
};

bool compare(Point p1, Point p2)
{
	if(p1.p == p2.p)
	{
		/*if(p1.ch == 'l')
			return true;
		else if(p2.ch == 'l')
			return false;
		else if(p1.ch == 'p')
			return true;
		else if(p2.ch == 'p')
			return false;
		else if(p1.ch == 'r')
			return true;
		else
			return false;*/
		return p1.ch < p2.ch;
	}
	return p1.p<p2.p;
}

vector<int> fast_count_segments(vector<int> &starts, vector<int> &ends, vector<int> &points) {
	vector<Point> allPoints;//atleast that much size should be there
	for(size_t i = 0; i < starts.size(); ++i)
	{
		allPoints.push_back(Point(starts[i], 'l'));
		allPoints.push_back(Point(ends[i], 'r'));
	}
	for(size_t i = 0; i < points.size(); ++i)
		allPoints.push_back(Point(points[i], 'p', i));
	sort(allPoints.begin(), allPoints.end(), compare);
	vector<int> cnt(points.size());
	//unordered_map<int, int> umap;
	int segment_count = 0;
	for(size_t i = 0; i < allPoints.size(); ++i)
	{
		if(allPoints[i].ch == 'l')
			++segment_count;
		else if(allPoints[i].ch == 'r')
			--segment_count;
		else
			cnt[allPoints[i].actual_index] = segment_count;//umap.insert({allPoints[i].p, segment_count};
	}
	//for(size_t i = 0; i < points.size(); ++i)
		//cnt[i] = umap[points[i]];
	return cnt;
}

/*
vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
	vector<int> cnt(points.size());
	for (size_t i = 0; i < points.size(); i++) {
		for (size_t j = 0; j < starts.size(); j++) {
			cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
		}
	}
	return cnt;
}*/

int main() {
	int n, m;
	cin >> n >> m;
	vector<int> starts(n), ends(n);
	for (size_t i = 0; i < starts.size(); i++) {
		cin >> starts[i] >> ends[i];
	}
	vector<int> points(m);
	for (size_t i = 0; i < points.size(); i++) {
		cin >> points[i];
	}
	//use fast_count_segments
	vector<int> cnt = fast_count_segments(starts, ends, points);
	for (size_t i = 0; i < cnt.size(); i++) {
		cout << cnt[i] << ' ';
	}
}
