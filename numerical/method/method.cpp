#include "method.h"

extern parameters init;
out outers;

double DSystem::problem_1(double t, double x, double y) {
	return y;
}

double DSystem::problem_2(double t,double x,double y) {
	return -init.g * x / init.l;
}

void DSystem::RK4() {
	clear();
	outers.data.clear();

	double h = init.step;

	double v0x = init.x0;
	double v0y = init.y0;

	x.push_back(v0x);
	xh.push_back(v0x);
	y.push_back(v0y);
	yh.push_back(v0y);

	sol_x[init.t_min] = v0x;
	sol_y[init.t_min] = v0y;


	double k1 = 0, k2 = 0, k3 = 0, k4 = 0; 
	double l1 = 0, l2 = 0, l3 = 0, l4 = 0; 

	double k1h = 0, k2h = 0, k3h = 0, k4h = 0; 
	double l1h = 0, l2h = 0, l3h = 0, l4h = 0; 

	size_t counter = 0, counter_h = 0, div = 0, doub = 0;

	double s = 0;
	double s1 = 0, s2 = 0;

	double t_curr_h = init.t_min;

	log(
		counter,
		init.t_min,
		h,
		sol_x[init.t_min],
		xh.back(),
		sol_x[init.t_min] - xh.back(),
		sol_y[init.t_min],
		yh.back(),
		sol_y[init.t_min] - yh.back(),
		s,
		doub,
		div
	);

	for (double t_curr = init.t_min; (t_curr < init.t_max - init.eps_br) && (counter <= init.n_max);) {

		doub = 0, div = 0;

		if (h > outers.max_step) {
			outers.max_step = h;
			outers.max_step_time = t_curr;
		}
		if (h < outers.min_step) {
			outers.min_step = h;
			outers.min_step_time = t_curr;
		}


		if (counter_h % 2 == 0) {
			l1 = problem_1(t_curr, x[counter], y[counter]);
			k1 = problem_2(t_curr, x[counter], y[counter]);

			l2 = problem_1(t_curr + h / 2, x[counter] + h / 2 * l1, y[counter] + h / 2 * k1);
			k2 = problem_2(t_curr + h / 2, x[counter] + h / 2 * l1, y[counter] + h / 2 * k1);

			l3 = problem_1(t_curr + h / 2, x[counter] + h / 2 * l2, y[counter] + h / 2 * k2);
			k3 = problem_2(t_curr + h / 2, x[counter] + h / 2 * l2, y[counter] + h / 2 * k2);

			l4 = problem_1(t_curr + h, x[counter] + h * l3, y[counter] + h * k3);
			k4 = problem_2(t_curr + h, x[counter] + h * l3, y[counter] + h * k3);

			++counter;
			x.push_back(x[counter - 1] + h / 6 * (l1 + 2 * l2 + 2 * l3 + l4));
			y.push_back(y[counter - 1] + h / 6 * (k1 + 2 * k2 + 2 * k3 + k4));
		}

		t_curr_h += h / 2;

		l1h = problem_1(t_curr_h, xh[counter_h], yh[counter_h]);
		k1h = problem_2(t_curr_h, xh[counter_h], yh[counter_h]);

		l2h = problem_1(t_curr_h + h / 4, xh[counter_h] + h / 4 * l1h, yh[counter_h] + h / 4 * k1h);
		k2h = problem_2(t_curr_h + h / 4, xh[counter_h] + h / 4 * l1h, yh[counter_h] + h / 4 * k1h);

		l3h = problem_1(t_curr_h + h / 4, xh[counter_h] + h / 4 * l2h, yh[counter_h] + h / 4 * k2h);
		k3h = problem_2(t_curr_h + h / 4, xh[counter_h] + h / 4 * l2h, yh[counter_h] + h / 4 * k2h);

		l4h = problem_1(t_curr_h + h / 2, xh[counter_h] + h / 2 * l3h, yh[counter_h] + h / 2 * k3h);
		k4h = problem_2(t_curr_h + h / 2, xh[counter_h] + h / 2 * l3h, yh[counter_h] + h / 2 * k3h);

		++counter_h;
		xh.push_back(xh[counter_h - 1] + h / 12 * (l1h + 2 * l2h + 2 * l3h + l4h));
		yh.push_back(yh[counter_h - 1] + h / 12 * (k1h + 2 * k2h + 2 * k3h + k4h));

		if ((xh.size() % 2 != 0 && xh.size() != 1) && (yh.size() % 2 != 0 && yh.size() != 1)) {
			s1 = (xh.back() - x.back()) / 15;
			s2 = (yh.back() - y.back()) / 15;
			s = std::max(std::abs(s1), std::abs(s2));

			if (s > outers.max_onlp)
				outers.max_onlp = s;

			if (std::abs(s) >= (init.eps / 32) && std::abs(s) <= init.eps) {
				t_curr += h;
				sol_x[t_curr] = x[counter];
				sol_y[t_curr] = y[counter];
;				counter_h = 0;

				log(
					counter,
					t_curr,
					h ,
					sol_x[t_curr],
					//x.back(),
					xh.back(),
					sol_x[t_curr] - xh.back(),
					//x.back() - xh.back(),
					sol_y[t_curr],
					//y.back(),
					yh.back(),
					sol_y[t_curr] - yh.back(),
					//y.back() - yh.back(),
					s,
					doub,
					div
				);

				xh.clear();
				yh.clear();
				xh.push_back(x[counter]);
				yh.push_back(y[counter]);
			}

			if (std::abs(s) < (init.eps / 32)) {
				t_curr += h;
				doub = 1;
				h *= 2;
				doub = 1;

				sol_x[t_curr] = x[counter];
				sol_y[t_curr] = y[counter];
				counter_h = 0;

				log(
					counter,
					t_curr,
					h,
					sol_x[t_curr],
					//x.back(),
					xh.back(),
					sol_x[t_curr] - xh.back(),
					//x.back() - xh.back(),
					sol_y[t_curr],
					//y.back(),
					yh.back(),
					sol_y[t_curr] - yh.back(),
					//y.back() - yh.back(),
					s,
					doub,
					div
				);

				outers.pows_counter += 1;

			    //h *= 2;
				xh.clear();
				yh.clear();
				xh.push_back(x[counter]);
				yh.push_back(y[counter]);
			}

			if (std::abs(s) > init.eps) {
				div = 1;

				log(
					counter,
					t_curr,
					h,
					sol_x[t_curr],
					//x.back(),
					xh.back(),
					sol_x[t_curr] - xh.back(),
					//x.back() - xh.back(),
					sol_y[t_curr],
					//y.back(),
					yh.back(),
					sol_y[t_curr] - yh.back(),
					//y.back() - yh.back(),
					s,
					doub,
					div
				);
				h /= 2;

				outers.divs_counter += 1;

				t_curr_h = t_curr;

				counter_h = 0;
				--counter;

				x.pop_back();
				y.pop_back();
				xh.clear();
				yh.clear();
				xh.push_back(x[counter]);
				yh.push_back(y[counter]);
			}
		}
	}
}

void DSystem::clear() {
	x.clear();
	xh.clear();
	y.clear();
	yh.clear();
	sol_x.clear();
	sol_y.clear();
	outers.data.clear();
	outers.pows_counter = 0;
	outers.divs_counter = 0;
}

void
DSystem::log(size_t idx, double x, double h, double v1, double v1h, double v1_diff, double v2, double v2h, double v2_diff, double onlp, size_t pows, size_t divs) {
	outers.data.push_back(std::make_tuple(idx, x, h, v1, v1h, v1_diff, v2, v2h, v2_diff, onlp, pows, divs));
}