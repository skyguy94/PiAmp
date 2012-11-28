#include "stdafx.h"
#include "montecarlopi.h"
#include "IterativePi.h"

#include <algorithm>
#include <Windows.h>
#include <mpirxx.h>

using namespace std;
using namespace concurrency;

mpf_class ComputePiWithAreas()
{
	MonteCarloPi mcPi(30000000);
	auto experimentalPi = mcPi.ComputePiWithAreas();
	return experimentalPi;
}

mpf_class ComputePiWithNeedles()
{
	MonteCarloPi mcPi(30000000);
	auto experimentalPi = mcPi.ComputePiWithNeedles(5, 6);
	return experimentalPi;
}

mpf_class ComputePiWithGaussLegendre()
{
	IterativePi itPi;
	auto experimentalPi = itPi.ComputePiWithGaussLegendre();
	return experimentalPi;
}

int main(int argc, char* argv[])
{
	mpf_set_default_prec(1000000);

	std::vector<double> values;

	cout << "Calculating the first 1,000,000 digits of pi" << std::endl;

	task<mpf_class> glTask([]() -> mpf_class { return ComputePiWithGaussLegendre(); });
	task<mpf_class> needleTask([]() -> mpf_class { return ComputePiWithNeedles(); });
	task<mpf_class> areaTask([]() -> mpf_class { return ComputePiWithAreas(); });

	auto calculated = glTask.get();
	cout << setw(13) << left << "Calculated:" << setiosflags(ios::fixed) << setprecision(1000) << calculated << std::endl << "(1,000 of 1,000,000 digits)" << std::endl;

	auto needleExperimental = needleTask.get();
	auto areaExperimental = areaTask.get();

	auto avgTask = create_task(
		[&needleExperimental, &areaExperimental]() -> mpf_class { return (needleExperimental + areaExperimental) / 2; })
		.then(
			[&calculated](mpf_class& average) -> mpf_class
			{
				cout << setw(13) << left << "Average:" << average << std::endl;
				return abs(calculated - average) / calculated;
			});

	avgTask.wait();

	cout << setw(13) << left << setprecision(10) << "Error:" << avgTask.get() << std::endl;
	char c;
	cin >> setw(1) >> c;
}
