#pragma once

const double g = 9.81;
const double pi = 3.1415;

struct parameters {
	int t_min = 0;
	int t_max = 1;
	double eps = 0.001;
	double step = 0.1;

	double u0 = pi/10;
	double v0 = 0;
	double l = 0.1;
};