//Alexandra Klimenko
//Homework 4
//Completed 2/22/2016

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <string>

class PolyTester;


class Polynomial
{
    friend class PolyTester;
	int size;
	double* coeff = new double[size];

private:
    // add your instance variables here
public:
    // add yourfunction declarations here
	Polynomial();
	Polynomial(double* array, int size);
	Polynomial(const Polynomial &other);
	Polynomial(int anInt);
	Polynomial(double aDouble);

	Polynomial operator=(const Polynomial& right);
	~Polynomial();

	int getSize() const;
	int degree() const;
	std::string str() const;
	double solve(double x) const;
	double& operator[](int i);

	Polynomial operator+(const Polynomial& right) const;
	Polynomial operator-(const Polynomial& right) const;
	Polynomial operator*(const Polynomial& right) const;

	Polynomial operator*(double d) const;
	Polynomial operator+=(const Polynomial& right);
	Polynomial operator-=(const Polynomial& right);
	Polynomial operator*=(const Polynomial& right);
	bool operator==(const Polynomial& right);
	bool operator!=(const Polynomial& right);


};


std::ostream& operator<<(std::ostream& os, const Polynomial& p);
#endif