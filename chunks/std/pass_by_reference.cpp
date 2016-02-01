#include <vector>
#include <iostream>
#include <queue>
using namespace std;
void by_value(vector<int> v) {
    v[0] = 2337;
}
void by_reference(vector<int> &v) {
    v[0] = 2337;
}
void add_to_queue(queue<int> &Q) {
    Q.push(69);
}
void print_vec(vector<int> v) {
    for(auto it=v.begin(); it != v.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}
void print_queue(queue<int> Q) {
    while(!Q.empty()) {
        cout << Q.front() << " ";
        Q.pop();
    }
    cout << endl;
}
int main() {
    cout << "---- Vector ----" << endl;
    vector<int> v1(3, 7);
    print_vec(v1);

    v1[0] = 1337;
    print_vec(v1);

    by_value(v1);
    print_vec(v1);

    by_reference(v1);
    print_vec(v1);

    cout << "---- Queue ----" << endl;
    queue<int> Q;
    Q.push(25);
    print_queue(Q);
    add_to_queue(Q);
    add_to_queue(Q);
    print_queue(Q);
}
/* OUTPUT:
---- Vector ----
7 7 7 
1337 7 7 
1337 7 7 
2337 7 7 
---- Queue ----
25 
25 69 69
*/