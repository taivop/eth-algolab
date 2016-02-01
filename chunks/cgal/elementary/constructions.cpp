#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Iso_rectangle_2.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <iostream>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef  CGAL::Min_circle_2_traits_2<K>  Traits;
typedef  CGAL::Min_circle_2<Traits> Min_circle;

int main() {

	cout << "CGAL CONSTRUCTIONS" << endl;
	// Documentation under '2D kernel objects': http://doc.cgal.org/latest/Kernel_23/group__kernel__classes2.html


	cout << "---- Line-line intersection ----" << endl;
	K::Point_2 a1(0, 0), a2(1, 0), b1(2,0), b2(2,2);
	K::Line_2 a = K::Line_2(a1, a2);
	K::Line_2 b = K::Line_2(b1, b2);

	auto o = CGAL::intersection(a, b);
	if (const K::Point_2* op = boost::get<K::Point_2>(&*o))
        cout << "lines a and b intersect at point: " << *op << endl;


    cout << "---- Rectangle-rectangle intersection ----" << endl;
    K::Point_2 r_left(0, 0), r_right(3, 3), p_left(2, 1), p_right(4,5);
    K::Iso_rectangle_2 r = K::Iso_rectangle_2(r_left, r_right);
    K::Iso_rectangle_2 p = K::Iso_rectangle_2(p_left, p_right);

    auto o2 = CGAL::intersection(r, p);
    if (const K::Iso_rectangle_2* ore = boost::get<K::Iso_rectangle_2>(&*o2))
        cout << "a and b intersect at rect: " << *ore << endl;


    cout << "---- Segment-segment intersection ----" << endl;
    K::Point_2 s1a(0, 0), s1b(2, 2), s2a(0, 1), s2b(1, 0);
    K::Segment_2 s1(s1a, s1b), s2(s2a, s2b);
    auto o3 = CGAL::intersection(s1, s2);
    if (const K::Point_2* op3 = boost::get<K::Point_2>(&*o3))
        cout << "a and b intersect at point: " << *op3 << endl;
    else if (const K::Segment_2* os3 = boost::get<K::Segment_2>(&*o3))
        cout << "a and b intersect at segment: " << os3->source() << " " << os3->target() << endl;




	cout << "---- Minimum enclosing circle ----" << endl;
	K::Point_2 p1(0, 0), p2(1, 2), p3(2, 0), p4(3, 1);
	vector<K::Point_2> v;
	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);
	v.push_back(p4);
	bool randomize = true;
	Min_circle mc(v.begin(), v.end(), randomize);
	Traits::Circle c = mc.circle();

	cout << "Circle center: " << c.center() << ", squared radius: " << c.squared_radius() << endl;




	return 0;
}
