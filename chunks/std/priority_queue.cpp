#include <queue>
#include <vector>
#include <iostream>
#include <functional>

using namespace std;
 
bool compare(int a, int b) {
    return a > b;
}

int main()
{
    // We use the default comparison function here.
    std::priority_queue<int> q1;
    q1.push(5);
    std::cout << q1.size() << '\n';
 
    // We use std::less as a comparison function here.
    std::vector<int> vec={3, 1, 4, 1, 5};
    std::priority_queue<int> q2(std::less<int>(), vec);
    std::cout << q2.size() << '\n';

    // We use the compare() function here.
    std::priority_queue<int, std::vector<int>, decltype(&compare)> q3(&compare);
    std::cout << q3.size() << '\n';
    for(int i=0; i<vec.size(); i++) {
    	q3.push(vec[i]);
    }
    
    while(!q2.empty()) {
    	cout << "default compare: " << q2.top() << endl;
    	q2.pop();
    }
    
    while(!q3.empty()) {
    	cout << "custom compare:  " << q3.top() << endl;
    	q3.pop();
    }
}

/* OUTPUT:
1
5
0
default compare: 5
default compare: 4
default compare: 3
default compare: 1
default compare: 1
custom compare:  1
custom compare:  1
custom compare:  3
custom compare:  4
custom compare:  5
*/