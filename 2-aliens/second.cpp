#include <iostream>
#include <vector>

using namespace std;

struct human {
	vector<int> wounded;
	human() {}
};

void test_case() {
	int m, n;

	cin >> n;
	cin >> m;

	vector<int> p, q;
	vector<human> humans;
	// pre-allocate
	p.reserve(n);
	q.reserve(n);
	humans.reserve(m);

	for(int i=0; i<n; i++) {
		cin >> p[i];
		cin >> q[i];

		human new_human = human();
		for(int j=0; j<p[i]; j++)
			new_human.wounded.push_back(j);
		for(int j=q[i]+1; j<n; j++)
			new_human.wounded.push_back(j);
		
		humans.push_back(new_human);
	}


	int counter=0;
	for(int i=0; i<n; i++) {
		if(p[i] == 0)
			continue;
		else {
			bool has_superinterval = false;
			for(int j=0; j<n; j++) {
				if((p[j] < p[i] && q[i] <= q[j]) || (p[j] <= p[i] && q[i] < q[j])) {
					has_superinterval = true;
					break;
				}
			}

			if(!has_superinterval)
				counter += 1;
		}
	}

	cout << counter << endl;
}

int main(void) {
	std::ios_base::sync_with_stdio(false);
	
	int N;
	cin >> N;

	for(int i=0; i<N; i++)
		test_case();

	return 0;
}