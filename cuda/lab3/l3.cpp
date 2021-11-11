#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const double co1 = 1.8;
const double co2 = 2.8;

double fun(double x) {
    return tan(co1 * x) - co2 * x;
}

double pi(void) {
    return M_PI / co1;
}

double get_ms() {
    struct timespec _t;
    clock_gettime(CLOCK_REALTIME, &_t);
    return _t.tv_sec*1000 + (_t.tv_nsec/1.0e6);
}

double bisection(double left, double right, double eps) {
    double mid = 0;
    double fl  = fun(left);
    double fr  = fun(right);

    while (abs(right - left) > abs(eps)) {
        double fm; 

        mid = (left + right) / 2;
        
        fm = fun(mid);

        if (fm) {
            // если одинак знак с левого края и по середине
            if (fm * fl > 0) {
                fl   = fm;
                left = mid;
            }
            // если одинак знак с правого края и по середине
            if (fm * fr > 0) {
                fr    = fm;
                right = mid;
            }
        }
        else
            break;
    }

    return mid;
}

int main(void) {
    vector<double> tear_points;

    double left, right, eps;
    cout << "l, r, e: ";
    cin >> left >> right >> eps;

    if (eps > 0.1)
        cout << "Ur epsilon too big" << endl;

    // next, we kinda wanna to find all the tear points, don't we?
    double tear = floor(left / pi()) * pi() - pi() / 2;

    cout << endl;
    while (tear < right + pi()) {
        // cout << tear << endl;
        tear_points.push_back(tear);
        tear += pi();
    }
    
    // we have out points. so we wanna find root in between each pair of them!

	double start = get_ms();

	cout << "Size: " << tear_points.size() << endl;
    for (int i = 1; i < tear_points.size(); ++i) {
        double lb = tear_points[i-1] + eps;
        double rb = tear_points[i]   - eps;
        cout << "Interval: [" << lb << ", " << rb << "]" << endl;
        double m = bisection(
            lb, 
            rb, 
            eps
        );

        if (m > left && m < right) {
			cout << "fun(" << m << ") = " << fun(m) << "\t (" << (int)fun(m) << ")" << endl;
			cout << endl;
		}
    }

    double end = get_ms();
    cout << "Time: " << end - start << endl;

    return 0;
}
