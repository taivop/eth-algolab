#include <vector>
#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int value;          // One variable
    bool operator<(Node other) const {  // const means I won't and can't modify member variables of the current object
        return value < other.value;
    }
};
void print_queue(queue<Node> Q) {
    while(!Q.empty()) {
        cout << Q.front().value << " ";
        Q.pop();
    }
    cout << endl;
}
void print_queue(priority_queue<Node> Q) {
    while(!Q.empty()) {
        cout << Q.top().value << " ";
        Q.pop();
    }
    cout << endl;
}
int main() {
    queue<Node> Q;
    priority_queue<Node> PQ;
    Node n1 = {1}; Node n2 = {25}; Node n3 = {3};

    Q.push(n1); Q.push(n2); Q.push(n3);
    PQ.push(n1); PQ.push(n2); PQ.push(n3);

    cout << "---- Regular queue ----" << endl;
    print_queue(Q);
    cout << "---- Priority queue ----" << endl;
    print_queue(PQ);

    return 0;
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