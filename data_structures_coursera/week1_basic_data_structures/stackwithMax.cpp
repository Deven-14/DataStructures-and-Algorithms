#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

using std::cin;
using std::string;
using std::vector;
using std::cout;
using std::max_element;

class StackWithMax {
    vector<int> stack;
    int max_ele=0;
  public:

    void Push(int value) {
        stack.push_back(value);
        if(value>max_ele)
            max_ele=value;
    }

    void Pop() {
        assert(stack.size());
        int temp=stack[stack.size()-1];
        stack.pop_back();
        if(temp==max_ele)
            max_ele=*max_element(stack.begin(), stack.end());
    }

    int Max() const {
        assert(stack.size());
        return max_ele;
    }
};

int main() {
    int num_queries = 0;
    cin >> num_queries;

    string query;
    string value;

    StackWithMax stack;

    for (int i = 0; i < num_queries; ++i) {
        cin >> query;
        if (query == "push") {
            cin >> value;
            stack.Push(std::stoi(value));
        }
        else if (query == "pop") {
            stack.Pop();
        }
        else if (query == "max") {
            cout << stack.Max() << "\n";
        }
        else {
            assert(0);
        }
    }
    return 0;
}
