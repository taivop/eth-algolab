#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Min_circle_2_traits_2<K>  Traits;
typedef CGAL::Min_circle_2<Traits>      Min_circle;

using namespace std;

double ceil_to_double(const K::FT& x)
{
  double a = std::ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return a;
}

void test_case(int n) {
	//cout << "n == " << n << endl;

	vector<K::Point_2> points;
	points.reserve(n);

	for(int i=0; i<n; i++) {
		long x, y;
		cin >> x >> y;
		//cout << x << ", " << y << endl;

		K::Point_2 p(x, y);
		points.push_back(p);
	}

	Min_circle mc(points.begin(), points.end(), true);
	Traits::Circle c = mc.circle();
	K::FT r_squared = c.squared_radius();
	K::FT r = sqrt(r_squared);

	cout << (long) ceil_to_double(r) << endl;
	
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