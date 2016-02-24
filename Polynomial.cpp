//Alexandra Klimenko
//Homework 4
//Completed 2/22/2016

#include <sstream>
#include <cmath>

#include "Polynomial.h"



// Default constructor
Polynomial::Polynomial()
	:coeff(new double[1]{0}), size(1) 
{
}

// Copy contents to constructed object
Polynomial::Polynomial(double* array, int size)
	:coeff(new double[size]{0}) , size(size) 
{
	for (int i = 0; i < size; ++i) {
		coeff[i] = array[i];
	}
}

// Copy Constructor
Polynomial::Polynomial(const Polynomial &other) 
	:coeff(new double[other.size]{0}), size(other.size)
{
	for (int i = 0; i < size; ++i) {
		coeff[i] = other.coeff[i];
	}
}

//Constructor from an int to Polynomial
Polynomial::Polynomial(int anInt)
	:coeff(new double[1]{(double)anInt}) , size(1)
{
}

//Constructor from a double to Polynomial
Polynomial::Polynomial(double aDouble)
	: coeff(new double[1]{aDouble}), size(1)
{
}

//Overload assignment operator for copying
Polynomial Polynomial::operator=(const Polynomial& right) 
{
	if (this == &right) 
	{
		return *this;
	}

	if (this->size < right.size)
	{
		delete[] coeff;
		coeff = new double[right.size]{0};
	}

	size = right.size;

	for (int i = 0; i < size; ++i)
	{
		coeff[i] = right.coeff[i];
	}

	return *this;
}

Polynomial::~Polynomial()
{
	if (coeff != nullptr)
	{
		delete[] coeff;
		coeff = nullptr;
	}
	size = 0;
}

int Polynomial::getSize() const
{
	return size;
}

int Polynomial::degree() const
{
	int degree = 0;
	for (int i = size - 1; i >= 0; --i) {
		if (coeff[i] != 0) {
			return i;
		}
	}
	
	return degree;
}

std::string Polynomial::str() const {

	std::ostringstream sout;

	Polynomial tempCoeff(*this);

	for (int i = size - 1; i > 0; --i) {

		if (tempCoeff.coeff[i] == 1 || tempCoeff.coeff[i] == 0) {
		}
		else if (tempCoeff.coeff[i] == -1) {
			sout << "-";
		}
		else {
			sout << tempCoeff.coeff[i];
		}

		if (i == 1 && tempCoeff.coeff[i] != 0)
		{
			sout << "x";
		}
		else if (tempCoeff.coeff[i] != 0) {
			sout << "x^" << i;
		}
		
		if (tempCoeff.coeff[i - 1] != 0)
		{
			if (tempCoeff.coeff[i - 1] < 0) {
				sout << " - ";
				tempCoeff.coeff[i - 1] = -tempCoeff.coeff[i - 1];
			}
			else {
				sout << " + ";
			}
		}
		
	}
		if (tempCoeff.coeff[0])
		{
			sout << tempCoeff.coeff[0];
		}

	
	return sout.str();
}

double Polynomial::solve(double x) const {
	double result;
	for (int i = 0; i < size; ++i) {
		result += coeff[i] * pow(x, i);
	}
	return result;
}

double& Polynomial::operator[](int x) {
	if (x >= size) {
		double* temp = new double[x + 1]{ 0 };
		for (int i = 0; i < size; ++i) {
			temp[i] = coeff[i];
		}
		delete[] coeff;
		coeff = temp;
		size = x + 1;
	}
	return coeff[x];
}

Polynomial Polynomial::operator+(const Polynomial& right) const {
	int largestSize = 0;
	int smallestSize = 0;
	if (this->degree() < right.degree()) {
		largestSize = right.size;
		smallestSize = this->size;
	}
	else {
		largestSize = this->size;
		smallestSize = right.size;
	}

	double* sum = new double[largestSize] {0};
	for (int i = 0; i < smallestSize; ++i) {
		sum[i] = this->coeff[i] + right.coeff[i];
	}

	for (int i = smallestSize; i < largestSize; ++i) {
		if (largestSize == smallestSize) {
			sum[i] = this->coeff[i];
		}
		else {
		sum[i] = right.coeff[i];
		}
	}

	Polynomial sumPolynomial(sum, largestSize);
	delete[] sum;
	return sumPolynomial;
}

Polynomial Polynomial::operator-(const Polynomial& right) const {
	return (*this + (right * -1));
}

Polynomial Polynomial::operator*(const Polynomial& right) const {
	int largestDegree = this->degree() + right.degree() + 1;

	double* multiplication = new double[largestDegree] {0};

	for (int i = 0; i < this->size; ++i) {
		for (int j = 0; j < right.size; ++j) {
			multiplication[i+j] += coeff[i] * right.coeff[j];
		}
	}

	Polynomial multiplicationPolynomial(multiplication, largestDegree);
	delete[] multiplication;
	return multiplicationPolynomial;
}

Polynomial Polynomial::operator*(double d) const {
	Polynomial product(*this);
	for (int i = 0; i < size; ++i) {
		product[i] = this->coeff[i] * d;
	}
	return product;
}

Polynomial Polynomial::operator+=(const Polynomial& right) {

	*this = *this + right;
	return *this;
}

Polynomial Polynomial::operator-=(const Polynomial& right) {
	
	*this = *this - right;
	size = this->degree() + 1;
	return *this;
}

Polynomial Polynomial::operator*=(const Polynomial& right) {
	*this = *this * right;
	return *this;
}

bool Polynomial::operator==(const Polynomial& right) {

	if (this->degree() != right.degree()) {
		return false;
	}
		
	for (int i = 0; i < size; ++i) {
		if (this->coeff[i] != right.coeff[i]) {
			return false;
      	}
	}
	return true;
}

bool Polynomial::operator!=(const Polynomial& right) {
	return !(*this == right);
}



std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
os << p.str();
return os;
}



// provide your function implementations here