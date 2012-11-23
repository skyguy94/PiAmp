#include "stdafx.h"
#include "montecarlopi.h"
#include <iomanip>

using namespace std;
using namespace concurrency;

double ComputePiWithAreas();
double ComputePiWithNeedles();

int main(int argc, char* argv[])
{
	std::vector<double> values;

//	parallel_invoke([&values] { values.push_back(ComputePiWithAreas()); });

	values.push_back(ComputePiWithNeedles());
	values.push_back(ComputePiWithNeedles());
	values.push_back(ComputePiWithNeedles());
	values.push_back(ComputePiWithNeedles());

	double result = 0;
	for(auto value : values)
	{
		cout << "Experimental: " << value << std::endl;
		result += value;
	}

	double mean = result / values.size();
	double error =  (abs((mean - std::_Pi)) / std::_Pi) * 100;

	cout << setprecision(12) << "Mean: " << mean << " Error (%): " << setprecision(4) << error << " Actual: " << setprecision(12) << std::_Pi << std::endl;

	string t;
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
	MonteCarloPi mcPi(30000);
	auto experimentalPi = mcPi.ComputePiWithNeedles(3, 5);
	return experimentalPi;
}
