#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void test_case() {
	int m, n;

	cin >> n;
	cin >> m;

	vector<int> p, q;
	// pre-allocate
	p.reserve(n);
	q.reserve(n);

	for(int i=0; i<n; i++) {
		cin >> p[i];
		cin >> q[i];

	}


	int counter=0;
	for(int i=0; i<n; i++) { // iterate over all aliens
		//printf("ALIEN %d\n", i);
		if(p[i] == 0)
			continue;
		else {
			bool has_superinterval = false;

			// Check if alien dominates entire humankind
			if(p[i] == 1 && q[i] == m) {
				counter++;
				continue;
			}

			// Check if i feels superior to all other aliens and humans
			vector<int> dom_humans_a;
			vector<int> dom_humans_b;
			bool skip_alien = false;

			for(int j=0; j<m; j++) {
				// don't compare alien with self
				if(i==j)
					continue;

				//printf("p[%d] < p[%d] => %d\n", i, j, p[i] < p[j]);
				//printf("q[%d] < q[%d] => %d\n", j, i, q[j] < q[i]);
				if(p[i] < p[j] || q[j] < q[i]) { // if alien i dominates alien j
					//printf("%d dominates %d\n", i, j);
					// Add alien j's dominated humans to the list IF not empty
					if(p[j] > 0) {
						dom_humans_a.push_back(p[j]);
						dom_humans_b.push_back(q[j]);
					}
				} else {
					skip_alien = true;
					break; // alien i doesn't dominate alien j so can't count it
				}
			}


			// Check if humans form continuous interval
			if(!skip_alien) {
				// Add alien's own humans
				dom_humans_a.push_back(p[i]);
				dom_humans_b.push_back(q[i]);


				int last_b = 0;
				while(dom_humans_a.size() > 0) {
					// Take leftmost interval
					vector<int>::iterator min_iterator = min_element(dom_humans_a.begin(), dom_humans_a.end());
					int min_index = min_iterator - dom_humans_a.begin();
					int a = dom_humans_a[min_index];
					int b = dom_humans_b[min_index];
					// Remove taken interval from arrays
					dom_humans_a.erase(dom_humans_a.begin()+min_index);
					dom_humans_b.erase(dom_humans_b.begin()+min_index);

					//printf("[%d, %d]\n", a, b);
					// Increase counter only if all humans are covered
					if(a > last_b+1)
						break;
					else if(b == m) {
						counter++;
						break;
					} else {
						last_b = max(last_b, b);
					}
				}
			}

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