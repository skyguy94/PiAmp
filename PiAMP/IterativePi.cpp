#include "stdafx.h"
#include "IterativePi.h"

double IterativePi::ComputePiWithGaussLegendre()
{
	double ai = 1.0;
	double bi = 1.0/std::sqrt(2.0);
	double ti = (1.0/4.0);
	double pi = 1.0;

	for (int i = 0; i < 25; i++)
	{
		double aOld = ai;
		ai = (ai + bi) / 2;
		bi = std::sqrt(aOld*bi);
		ti = ti - (pi*std::pow(aOld - ai, 2));
		pi = 2 * pi;
	}

	double result = std::pow(ai + bi, 2) / (4*ti);
	return result;
}
