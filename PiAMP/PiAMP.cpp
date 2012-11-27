#include "stdafx.h"
#include "montecarlopi.h"
#include "IterativePi.h"

using namespace std;
using namespace concurrency;

double ComputePiWithAreas();
double ComputePiWithNeedles();
double ComputePiWithGaussLegendre();

int main(int argc, char* argv[])
{
	std::vector<double> values;

 //parallel_invoke(
	// [&values] {values.push_back(ComputePiWithNeedles()); },
	// [&values] { values.push_back(ComputePiWithNeedles()); },
	// [&values] { values.push_back(ComputePiWithNeedles()); },
	// [&values] { values.push_back(ComputePiWithNeedles()); },
	// [&values] { values.push_back(ComputePiWithNeedles()); },
	// [&values] { values.push_back(ComputePiWithNeedles()); },
	// [&values] { values.push_back(ComputePiWithNeedles()); },
	// [&values] { values.push_back(ComputePiWithNeedles()); },
	// [&values] { values.push_back(ComputePiWithNeedles()); }
	// );

	values.push_back(ComputePiWithGaussLegendre());
	double result = 0;
	for(auto value : values)
	{
		cout << setw(15) << left << "Experimental:" << setprecision(26) << setw(26) << value << std::endl;
		result += value;
	}

	cout << setw(15) << left << "Constant:" << setprecision(26) << setw(26) << std::_Pi << std::endl;

	double mean = result / values.size();
	double error =  (abs((mean - std::_Pi)) / std::_Pi) * 100;

	cout << setprecision(26) << "Mean: " << mean << " Error (%): " << setprecision(3) << error << std::endl;

	char t;
	cin >> t;
}

double ComputePiWithAreas()
{
	MonteCarloPi mcPi(30000);
	auto experimentalPi = mcPi.ComputePiWithAreas();
	return experimentalPi;
}

double ComputePiWithNeedles()
{
	MonteCarloPi mcPi(3000);
	auto experimentalPi = mcPi.ComputePiWithNeedles(5, 6);
	return experimentalPi;
}

double ComputePiWithGaussLegendre()
{
	IterativePi itPi;
	auto experimentalPi = itPi.ComputeWithGaussLegendre();
	return experimentalPi;
}