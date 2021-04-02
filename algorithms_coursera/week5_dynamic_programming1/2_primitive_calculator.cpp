#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void backTrack_optimal_sequence(int n, vector<int> &minNoOp, vector<int> &operations)
{
	if(n == 1)
		return;//befor mod2 or mod3, we can check for 2i+1, 3i+1 and 3i+2, i.e if there are extra one's we remove them first then go with %2 and %3, see below eg:
	if(minNoOp[n - 1] + 1 == minNoOp[n])//eg: for n = 10, minNoOp[9]=2+1=3 == minNoOp[10]=3 (10,9,3,1 and not 10,5,4,2,1)
		backTrack_optimal_sequence(n - 1, minNoOp, operations);
	else if(n % 2 == 0)
		backTrack_optimal_sequence(n / 2, minNoOp, operations);
	else
		backTrack_optimal_sequence(n / 3, minNoOp, operations);
	operations.push_back(n);
}

vector<int> optimal_sequence(int n) {
	/*std::vector<int> sequence;
	while (n >= 1) {
		sequence.push_back(n);
		if (n % 3 == 0) {
			n /= 3;
		} else if (n % 2 == 0) {
			n /= 2;
		} else {
			n = n - 1;
		}
	}
	reverse(sequence.begin(), sequence.end());
	return sequence;*/
	vector<int> minNoOfOp(n + 1);
	minNoOfOp[0] = 0;//[0]
	minNoOfOp[1] = 0;//[1]**********1 is already present
	minNoOfOp[2] = 1;//[2]
	minNoOfOp[3] = 1;//[3]
	vector<int> Operations;
	
	for(int i = 4; i <= n; ++i)
	{
		int op1 = 0, op2 = 0, op3 = 0;
		op1 = minNoOfOp[i - 1] + 1;
		if(i % 2 == 0)
			op2 = minNoOfOp[i/2] + 1;
		else
		    op2 = minNoOfOp[i - 1] + 1;
		if(i % 3 == 0)
			op3 = minNoOfOp[i/3] + 1;
		else if(i % 3 == 1)
		    op3 = minNoOfOp[i - 1] + 1;
		else
		    op3 = minNoOfOp[i - 2] + 2;
		minNoOfOp[i] = min(op1,min(op2,op3));
	}
	
	//backTrack_optimal_sequence(n, minNoOfOp, Operations);
	
	while(n != 1)
	{
		Operations.push_back(n);//or use stack to store and then put in the vector or store in vector and reverse
		if(n % 2 == 0 && minNoOfOp[n/2] + 1 == minNoOfOp[n])
			n /= 2;
		else if(n % 3 == 0 && minNoOfOp[n/3] + 1 == minNoOfOp[n])
			n /= 3;
		else
			n--;
	}
	Operations.push_back(1);
	reverse(Operations.begin(), Operations.end());
	
	return Operations;
}

int main() {
	int n;
	std::cin >> n;
	vector<int> sequence = optimal_sequence(n);
	std::cout << sequence.size() - 1 << std::endl;
	for (size_t i = 0; i < sequence.size(); ++i) {
		std::cout << sequence[i] << " ";
	}
	std::cout << endl;
}
