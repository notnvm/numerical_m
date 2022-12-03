#pragma once

#include <vector>
#include <map>
#include <tuple>

#include "parameters.h"

struct out {
	std::vector< std::tuple<size_t, double, double, double, double, double, double, double, double, double, size_t, size_t> > data;
	double max_step = 0;
	double max_step_time = 0;
	double min_step_time = 0;
	double min_step = 1000;
	double max_onlp = -1000;
	int divs_counter = 0;
	int pows_counter = 0;
};

class DSystem {
public:
	DSystem() = default;
	DSystem(const DSystem& other) = default;

	~DSystem() { clear(); }

public:

	void clear();
	void RK4();
	double problem_1(double,double,double);
	double problem_2(double,double,double);

	void
	log(size_t, double, double, double, double, double, double, double, double, double, size_t, size_t);

public:

	std::vector<double> get_u() { return x; }
	std::vector<double> get_du() { return y; }

	std::map<double, double> get_sol_x() { return sol_x; }
	std::map<double, double> get_sol_y() { return sol_y; }

private:
	std::vector<double> x;
	std::vector<double> xh;
	std::vector<double> y;
	std::vector<double> yh;
	std::map<double, double> sol_x;
	std::map<double, double> sol_y;
};