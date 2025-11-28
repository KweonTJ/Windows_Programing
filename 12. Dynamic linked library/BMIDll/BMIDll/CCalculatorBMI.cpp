#include "pch.h"
#include "CCalculatorBMI.h"

double CCalculatorBMI::CalculateBMI(double height, double weight)
{
    // TODO: 여기에 구현 코드 추가.
	m_dBMI = weight / ((height / 100) * (height / 100));
    return m_dBMI;
}

CString CCalculatorBMI::DetermineObesity()
{
    // TODO: 여기에 구현 코드 추가.
	CString obesity;
    if (m_dBMI < 18.5)
    {
		obesity = "저체중";
    }
    else if (m_dBMI < 23.0)
    {
        obesity = "정상";
    }
    else if (m_dBMI < 25.0)
	{
        obesity = "과체중";
    }
	else if (m_dBMI < 30.0)
    {
        obesity = "경도비만";
	}
    else if (m_dBMI < 35.0)
    {
        obesity = "중도비만";
    }
    else
    {
        obesity = "고도비만";
	}
    return obesity;
}

double CCalculatorBMI::CalculateStdWeight(char gender, double height, double weight)
{
    // TODO: 여기에 구현 코드 추가.
    switch (gender)
    {
    case 'M':
		return (height / 100) * (height / 100) * 22;
        break;
    case 'F':
		return (height / 100) * (height / 100) * 21;
        break;
    }
}
