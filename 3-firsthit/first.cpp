#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/squared_distance_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel IK;

using namespace std;

void test_case(int n) {

	long x, y, a, b;
	cin >> x >> y >> a >> b;

	IK::Point_2 source(x, y);
	IK::Point_2 another(a, b);

	IK::Ray_2 phileas(source, another);

	bool yes = false;

	for(int i=0; i<n; i++) {
		long r, s, t, u;
		cin >> r >> s >> t >> u;

		IK::Point_2 p1(r, s), p2(t, u);
		IK::Segment_2 seg(p1, p2);

		if(CGAL::left_turn(source, another, p1) && CGAL::left_turn(source, another, p2) || 
			CGAL::right_turn(source, another, p1) && CGAL::right_turn(source, another, p2) ||
			CGAL::angle(another, source, p1) == CGAL::OBTUSE && CGAL::angle(another, source, p2) == CGAL::OBTUSE // BAp1 and BAp2 are both obtuse
			) {

		} else {
			yes = true;
		}
	}
	
	if(yes)
		cout << "yes" << endl;
	else
		cout << "no" << endl;
	
	return;
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