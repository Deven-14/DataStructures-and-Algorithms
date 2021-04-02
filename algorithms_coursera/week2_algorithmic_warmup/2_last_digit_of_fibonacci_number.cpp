#include <iostream>
#include <cassert>
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

//second question
int get_fibonacci_last_digit_naive(int n) {
    if (n <= 1)
        return n;

    int previous = 0;
    int current  = 1;

    for (int i = 0; i < n - 1; ++i) {
        int tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current) % 10;//******************************very nice idea instead of return current%10;
    }

    return current;
}

/*void test_solution() {
    assert(fibonacci_fast(3) == 2);
    assert(fibonacci_fast(10) == 55);
    for (int n = 0; n < 20; ++n)
        assert(fibonacci_fast(n) == fibonacci_naive(n));
}*/

int main() {
    int n = 0;
    cin >> n;

    //cout << fibonacci_naive(n) << '\n';
    //test_solution();
    //cout << fibonacci_fast(n) << '\n';
	int c = get_fibonacci_last_digit_naive(n);
    cout << c << '\n';
    return 0;
}
