#pragma once

class MonteCarloPi
{
private:
	int trials_;
	int SimulateInCircle();
	int SimulateOverLine(const double length, const double distance);
public:
	MonteCarloPi(int trials);
	double ComputePiWithAreas();
	double ComputePiWithNeedles(const double length, const double distance);
};
