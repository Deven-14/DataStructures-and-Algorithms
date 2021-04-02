#include <iostream>
#include <vector>
using namespace std;

int compute_min_refills(int dist, int tank, vector<int> & stops) {
	int n = static_cast<int>(stops.size()) + 2;
	vector<int> totStops(n);
	totStops.push_back(0);
	int size = stops.size();
	for(int i = 0; i < size; ++i)
		totStops.push_back(stops[i]);
	totStops.push_back(dist);
	
	int noOfReFills = 0;
	int lastReFill = 0, currReFill = 0;//storing the index values is better than doing if(currrefill+dist < totstops[i]) currRefill+totstops[i];, here simply lost of problems can arrise, i.e integer overflow, then etc, so where ever possible use index instead of actual values of the array
	n = totStops.size() - 1;//so that the n-2 th case when enters the loops check if it is possible to go to n-1th case i.e dist, if yes then lastRefill!=currRefill, coz currRefill would have reached dist(n-1th case)
	while(currReFill < n)
	{
		lastReFill = currReFill;
		while(currReFill < n && totStops[currReFill + 1] - totStops[lastReFill] <= tank)
			++currReFill;
		if(lastReFill == currReFill)
			return -1;
		noOfReFills++;
	}
	noOfReFills--;//for the last case, if true then dist is also calculated as a refill, so removing the count
    return noOfReFills;
}


int main() {
    int d = 0;
    cin >> d;
    int m = 0;
    cin >> m;
    int n = 0;
    cin >> n;

    vector<int> stops(n);
    for (int i = 0; i < n; ++i)
        cin >> stops.at(i);

    cout << compute_min_refills(d, m, stops) << "\n";

    return 0;
}
