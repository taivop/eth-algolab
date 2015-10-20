#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>

using namespace std;

// TODO maybe sum doesn't fit in int

int vector_sum(vector<int> v) {
	if(v.size() == 0)
		throw std::invalid_argument( "vector has 0 elements" );

 	int sum = 0;

	for(int x : v)
		sum += x;

	return sum;
}

string vector_to_str(vector<int> v) {
	string s = "[";
	for(int x : v) {
		s = s + to_string(x) + ",";
	}
	return s+"]";
}

int rec_try(vector<int> A, vector<int> B) {
	int a, b;
	int best = vector_sum(A) * vector_sum(B);
	vector<int> A_remain, B_remain;

	if(A.size() == 1 || B.size() == 1) {
		// Have to take all elements
		return((vector_sum(A) - A.size()) * (vector_sum(B) - B.size()));
	}

	// Take only one from A
	a = 1;
	A_remain = vector<int>(A.begin(), A.end()-a);
	for(b=1; b<B.size(); b++) {
		int cost = (A[A.size()-1] - 1) * vector_sum(vector<int>(B.end()-b, B.end()));
		vector<int> B_remain = vector<int>(B.begin(), B.end()-b);
		int res = rec_try(A_remain, B_remain);
		//cout << "REC:" << a << "," << b << " -> " << cost << "+" << res << endl;
		if(cost + res < best) {
			best = cost + res;
			//cout << "best is now " << best << ", cost comes from A[" << A.size()-a << ":" << A.size()-1 << "] x B[" << B.size()-1 << "]" << endl; 
		}
		//cout << "took " << b << " elements" << endl;
	}

	// Take only one from B
	b = 1;
	B_remain = vector<int>(B.begin(), B.end()-b);
	for(a=1; a<A.size(); a++) {
		int cost = (B[B.size()-1] - 1) * vector_sum(vector<int>(A.end()-a, A.end()));
		vector<int> A_remain = vector<int>(A.begin(), A.end()-a);
		int res = rec_try(A_remain, B_remain);
		//cout << "REC:" << a << "," << b << " -> " << cost << "+" << res << endl;
		if(cost + res < best) {
			best = cost + res;
			//cout << "best is now " << best << ", cost comes from A[" << A.size()-a << ":" << A.size()-1 << "] x B[" << B.size()-1 << "]" << endl; 
		}
		//cout << "took " << b << " elements" << endl;
	}

	cout << "best on A=" << vector_to_str(A) << ", B=" << vector_to_str(B) << " is " << best << endl;

	return(best); // the cost
}

void test_case() {
	int n;
	cin >> n;

	vector<int> A = vector<int>(n, 0);
	vector<int> B = vector<int>(n, 0);


	for(int i=0; i<n; i++) {
		cin >> A[i];
	}
	for(int i=0; i<n; i++)
		cin >> B[i];

	cout << rec_try(A, B) << endl;

	return;
}

int main(void) {
	std::ios_base::sync_with_stdio(false);
	
	int N;
	cin >> N;

	for(int i=0; i<N; i++)
		test_case();

	return 0;
}