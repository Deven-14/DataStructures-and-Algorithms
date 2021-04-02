#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

// The following code calls a naive algorithm for computing a Fibonacci number.
//
// What to do:
// 1. Compile the following code and run it on an input "40" to check that it is slow.
//    You may also want to submit it to the grader to ensure that it gets the "time limit exceeded" message.
// 2. Implement the fibonacci_fast procedure.
// 3. Remove the line that prints the result of the naive algorithm, comment the lines reading the input,
//    uncomment the line with a call to test_solution, compile the program, and run it.
//    This will ensure that your efficient algorithm returns the same as the naive one for small values of n.
// 4. If test_solution() reveals a bug in your implementation, debug it, fix it, and repeat step 3.
// 5. Remove the call to test_solution, uncomment the line with a call to fibonacci_fast (and the lines reading the input),
//    and submit it to the grader.

/*int fibonacci_naive(int n) {
    if (n <= 1)
        return n;

    return fibonacci_naive(n - 1) + fibonacci_naive(n - 2);
}*/

/*
//first question
int fibonacci_fast(int n) {
	if(n <= 1)
		return n;
	//int *f = new int[n+2];//it should be n+1 but then i wrote n+2 coz of n=0 and n=1 initial conditions, if the input is 0, but also we need f[2] as default value
	int *f = new int[n+1];//coz i added return statement in the begining
	f[0] = 0;
	f[1] = 1;
	for(int i = 2; i <= n; ++i)
		f[i] = f[i - 1] + f[i - 2];
	int num = f[n];
	delete[] f;
    return num;
}*/

/*
//second question, here n is in int range < 1 billion
int get_fibonacci_last_digit_naive(int n) {
    if (n <= 1)
        return n;

    int previous = 0;
    int current  = 1;

    for (int i = 0; i < n - 1; ++i) {
        int tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current) % 10;******************************very nice idea instead of return current%10;
    }

    return current;
}
*/


//third question, helpful in cryptography, coz u don't need to find fn and then % m, u can follow 2nd question method(but instead of 10, it'll be m), the use of this method us that
//here n is > 1 billion, it goes to 10^14
//so in such cases method 2 is not fine, coz it'll take more than 1 second to perform the action, so it is seen that when we do %m for m>=2 the output becomes periodic,
//and hence we use this periodic table to find the fn % m
long long get_fibonacci_huge(long long n, long long m) {
	if (n <= 1)
		return n;//coz periodic table's first 2 num  is 0 and 1
	
	vector<int> pT = {0, 1};//periodicTable
	int currpTIndex = 0;
	vector<int> pT2;
	
	long long previous = 0;
	long long current  = 1;
	
	long long i = 2;//i also should be long long*************
	while(pT.size() >= pT2.size())//&& i<=n)// i<=n if periodic form is not found yet but the ele is reached, i==n coz, coz that case has to execute for the value of p[n], but this is useless as for m=1000 maxval also the no of loops will be 1500 and so n can be way greater than billions, so it is a waste of putting that and coz the no of loops depends on m and not n
	//n= 50000000000 and m=1000 will take 1500 loops of while and n=5 and m=1000 will take 1500 loops, after 1500 loops we found the pT and FROM THIS pT WE CAN FIND ANY ELEMENT BY DOING rem = n%size and here majority of the n values is greater than 1 billion so putting i condition is a waste, and for m<1000 the no of loops executed are even less and hence we don't need
	{//pt.size()==pt2.size() case coz 01201256780120125678 this might be the case and we have to observe 012012 here it is not actually periodic so if next one is also equal(pt.size==pt2size case) then loop quits or else it'll be attached to pT and then started again
		long long tmp_previous = previous;
		previous = current;
		current = (tmp_previous + current) % m;
		if(current == pT[currpTIndex%pT.size()])
		{
			currpTIndex++;
			pT2.push_back(current);
		}
		else if(pT2.size()!=0)
		{
			currpTIndex = 0;
			long long size = pT2.size();//size has to be long long coz, n > 1billion
			for(long long j = 0; j < size; ++j)//j has to be long long****************
				pT.push_back(pT2[j]);
			pT2.clear();
			pT.push_back(current);
		}
		else
			pT.push_back(current);
		i++;
	}
	/*int size = pT.size();
	cout << size <<endl;//to check for the size when i<=n is not put
	if(i-1 == n)//if no perodic form is found but the nth num is found
		return pT[n];*/
	
	int rem = n % pT.size();
	return pT[rem];
}

/*void test_solution() {
    assert(fibonacci_fast(3) == 2);
    assert(fibonacci_fast(10) == 55);
    for (int n = 0; n < 20; ++n)
        assert(fibonacci_fast(n) == fibonacci_naive(n));
}*/

int main() {
    //int n = 0;
    //cin >> n;

    //cout << fibonacci_naive(n) << '\n';
    //test_solution();
    //cout << fibonacci_fast(n) << '\n';
	//int c = get_fibonacci_last_digit_naive(n);
    //cout << c << '\n';
	long long n, m;
    cin >> n >> m;
	//for(int i = 0; i < 1001; ++i)and instead of m put i and u can see the sizes of all such pT from 1 to 1000 and n can any value, coz it doesn't depend on anythying, we find the periodic table and the do rem=n%size (and size here depends of m coz we do ele % m, so the elements after a size will repeat the sequence and from the size of the sequence we can find any ele)and return p[rem] so n can be any number
    cout << get_fibonacci_huge(n, m) << '\n';//n can be any number, once we have the periodic series which depends on m (see above for explanation), we can find any ele
    return 0;
}
