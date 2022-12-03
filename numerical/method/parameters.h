#pragma once

const double pi = 3.1415;

struct parameters {
	double g = 9.81;

	int t_min = 0;
	int t_max = 1;
	double eps = 0.0001;
	double step = 0.001;
	double eps_br = 0.01;
	int n_max = 1000;

	double x0 = pi/10;
	double y0 = 0;
	double l = 0.1;
};