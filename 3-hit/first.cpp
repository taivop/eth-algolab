#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

using namespace std;

void test_case(int n) {

	long x, y, a, b;
	cin >> x >> y >> a >> b;

	K::Point_2 source(x, y);
	K::Point_2 another(a, b);

	K::Ray_2 phileas(source, another);

	for(int i=0; i<n; i++) {
		long r, s, t, u;
		cin >> r >> s >> t >> u;

		K::Point_2 p1(r, s), p2(t, u);
		K::Segment_2 seg(p1, p2);

		if(do_intersect(phileas, seg)) {
			cout << "yes" << endl;
			return;
			
		}
	}
	
	cout << "no" << endl;

}

int main(void) {
	std::ios_base::sync_with_stdio(false);
	
	int n;
	
	cin >> n;

	while(n != 0) {
		test_case(n);
		cin >> n;
	}

	return 0;
}