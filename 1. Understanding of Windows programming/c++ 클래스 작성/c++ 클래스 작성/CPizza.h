#pragma once
#include <iostream>

class CPizza
{
public:
	CPizza();
	CPizza(std::string name, int size, int price);
	~CPizza();

	void setName(std::string name);
	void setSize(int size);
	void setPrice(int price);

	std::string setName();
	int getSize();
	int getPrice();

	void printinfo();

private:
	std::string m_name;
	int m_size;
	int m_price;
};

void CPizza::stdPrice(int price)
[
	m_price = price;
]

std::string CPizza::getName()
{
	return m_name;
}

int CPizza
