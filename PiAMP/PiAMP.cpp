#include "stdafx.h"
#include "montecarlopi.h"
#include "IterativePi.h"
#include <algorithm>
#include <Windows.h>

using namespace std;
using namespace concurrency;

double ComputePiWithAreas();
double ComputePiWithNeedles();
double ComputePiWithGaussLegendre();

int main(int argc, char* argv[])
{
	std::vector<double> values;

	double calculated = ComputePiWithGaussLegendre();
	cout << setw(15) << left << "Calculated:" << setprecision(26) << setw(26) << calculated << std::endl;

	auto t = create_task([calculated]() -> double
		{
			double mean = 0;
			double error = 100;
			vector<double> values;
			
			while (error > .05)
			{
				parallel_invoke(
				 [&values] { values.push_back(ComputePiWithAreas()); },
				 [&values] { values.push_back(ComputePiWithAreas()); },
				 [&values] { values.push_back(ComputePiWithAreas()); },
				 [&values] { values.push_back(ComputePiWithAreas()); },
				 [&values] { values.push_back(ComputePiWithAreas()); },
				 [&values] { values.push_back(ComputePiWithNeedles()); },
				 [&values] { values.push_back(ComputePiWithNeedles()); },
				 [&values] { values.push_back(ComputePiWithNeedles()); },
				 [&values] { values.push_back(ComputePiWithNeedles()); },
				 [&values] { values.push_back(ComputePiWithNeedles()); }
				);

				double result = parallel_reduce(begin(values), end(values), 0, std::plus<double>());
				mean = result / values.size();
				error = abs((mean - calculated) / calculated) * 100;
				
				parallel_sort(begin(values), end(values));
				parallel_for_each(begin(values), end(values), [](double i){ cout << setw(15) << left << "Experimental:" << setprecision(26) << setw(26) << i << std::endl; });
				cout << "Error (%): " << setprecision(3) << error << std::endl;
			}

			return mean;
		});
	
	t.then([calculated](double mean)
	{
		double error =  (abs((mean - calculated)) / calculated) * 100;

		cout << setprecision(26) << "Mean: " << mean << " Error (%): " << setprecision(3) << error << std::endl;
	});

	t.wait();

	char c;
	cin >> setw(1) >> c;
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
	auto experimentalPi = itPi.ComputePiWithGaussLegendre();
	return experimentalPi;
}