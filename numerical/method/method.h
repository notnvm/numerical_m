#pragma once

#include <vector>
#include <map>

#include "parameters.h"

class DSystem {
public:
	DSystem() = default;
	DSystem(const DSystem& other) = default;

	~DSystem() { clear(); }

public:

	void clear();
	void RK4();
	double problem_1(double);
	double problem_2(double);
	void log(); //

public:

	std::vector<double> get_du() { return du; }
	std::vector<double> get_dduu() { return dduu; }
	std::vector<double> get_time() { return time; }
	std::map<double, double> get_sol() { return sol; } // temp

private:
	std::vector<double> du;
	std::vector<double> duh;
	std::vector<double> dduu;
	std::vector<double> dduuh;
	std::vector<double> time;
	std::map<double, double> sol; // temp
};