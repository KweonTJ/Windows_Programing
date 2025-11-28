#pragma once
class AFX_EXT_CLASS CCalculatorBMI
{
public:
	double CalculateBMI(double height, double weight);
	CString DetermineObesity();
	double CalculateStdWeight(char gender, double height, double weight);
	double m_dBMI;
};
