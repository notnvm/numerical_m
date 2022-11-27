#include "method.h"

extern parameters init;

// u_1 = u ; u_2 = u' || w = v0/l w' = -g*u/l u0 = pi/10, v0 = 0??

// du - u, dduu - du' //

double DSystem::problem_1(double u_0) { // u 
	return u_0;
}

double DSystem::problem_2(double u_1) { // u'' + g*u_1/l = 0 => u' = -g*u_1/l
	return -g * u_1 / init.l;
}

void DSystem::RK4() {
	clear();

	double h = init.step;

	du.push_back(init.u0);
	duh.push_back(init.u0);
	dduu.push_back(init.v0);
	dduuh.push_back(init.v0);
	sol[init.t_min] = init.u0;

	double k1 = 0, k2 = 0, k3 = 0, k4 = 0; 
	double l1 = 0, l2 = 0, l3 = 0, l4 = 0; 

	double k1h = 0, k2h = 0, k3h = 0, k4h = 0; 
	double l1h = 0, l2h = 0, l3h = 0, l4h = 0; 

	size_t counter = 0, counter_h = 0;

	double s = 0;
	double s1 = 0, s2 = 0;

	for (double t_curr = init.t_min; t_curr <= init.t_max;) {

		size_t doub = 0, div = 0;

		if (counter_h % 2 == 0) {
			l1 = problem_1(du[counter]);
			l2 = problem_1(du[counter] + h / 2 * l1);
			l3 = problem_1(du[counter] + h / 2 * l2);
			l4 = problem_1(du[counter] + h * l3);

			k1 = problem_2(dduu[counter]);
			k2 = problem_2(dduu[counter] + h / 2 * k1);
			k3 = problem_2(dduu[counter] + h / 2 * k2);
			k4 = problem_2(dduu[counter] + h * k3);

			++counter;
			du.push_back(du[counter - 1] + h / 6 * (l1 + 2 * l2 + 2 * l3 + l4));
			dduu.push_back(dduu[counter - 1] + h / 6 * (k1 + 2 * k2 + 2 * k3 + k4));
		}

		l1h = problem_1(duh[counter_h]);
		l2h = problem_1(duh[counter_h] + h / 4 * l1h);
		l3h = problem_1(duh[counter_h] + h / 4 * l2h);
		l4h = problem_1(duh[counter_h] + h / 2 * l3h);

		k1h = problem_2(dduuh[counter_h]);
		k2h = problem_2(dduuh[counter_h] + h / 4 * k1h);
		k3h = problem_2(dduuh[counter_h] + h / 4 * k2h);
		k4h = problem_2(dduuh[counter_h] + h / 2 * k3h);

		++counter_h;
		duh.push_back(duh[counter_h - 1] + h / 12 * (l1h + 2 * l2h + 2 * l3h + l4h));
		dduuh.push_back(dduuh[counter_h - 1] + h / 12 * (k1h + 2 * k2h + 2 * k3h + k4h));

		if (duh.size() % 2 != 0 && duh.size() != 1) {
			s1 = (duh.back() - du.back()) / 15;
			s1 = (dduuh.back() - dduu.back()) / 15;
			s =/* std::max(s1, s2)*/(duh.back() - du.back()) / 15;

			if (std::abs(s) >= (init.eps / 32) && std::abs(s) <= init.eps) {
				time.push_back(t_curr);
				t_curr += h;
				sol[t_curr] = du.back();
				counter_h = 0;

				duh.clear();
				dduuh.clear();
				duh.push_back(du[counter]);
				dduuh.push_back(dduu[counter]);
			}

			if (std::abs(s) < (init.eps / 32)) {
				time.push_back(t_curr);
				t_curr += h; 
				sol[t_curr] = du.back();
				h *= 2;
				doub = 1;

				counter_h = 0;

				duh.clear();
				dduuh.clear();
				duh.push_back(du[counter]);
				dduuh.push_back(dduu[counter]);
			}

			if (std::abs(s) > init.eps) {

				h /= 2;
				div = 1;

				counter_h = 0;
				--counter;

				du.pop_back();
				dduu.pop_back();
				duh.clear();
				dduuh.clear();
				duh.push_back(du[counter]);
				dduuh.push_back(dduu[counter]);
			}
		}
	}
	time.push_back(1);
}

void DSystem::clear() {
	du.clear();
	duh.clear();
	dduu.clear();
	dduuh.clear();
}