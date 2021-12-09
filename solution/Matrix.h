#pragma once

#include <iostream>
#include <vector>
#include <string>

class Matrix
{
private:
	// -1) The private geter gets a linear index:
	const unsigned int get_index(unsigned int row, unsigned int col) const;

	// 0) Values:
	std::vector <double> values;
	unsigned int rown;				
	unsigned int coln;				

public:
	// 1) Constructors:
	Matrix();
	Matrix(const unsigned int rown, const unsigned int coln);

	// 2) Destructior:
	~Matrix();

	// 3) Geters and seters:
	const unsigned int get_rSize() const;
	const unsigned int get_cSize() const;

	// 4) Opearators:
	double& operator()(const unsigned int row, const unsigned int col);
	const double& operator()(const unsigned int row, const unsigned int col) const;

	Matrix& operator=(const Matrix& R);
	Matrix& operator+=(const Matrix& R);
	Matrix& operator-=(const Matrix& R);
	Matrix& operator*=(const double k);
	Matrix& operator*=(const Matrix& R);
};


// 5) External:
// a) Operators:
Matrix operator+(const Matrix& L, const Matrix& R);
Matrix operator-(const Matrix& L, const Matrix& R);
Matrix operator*(const Matrix& L, const Matrix& R);
Matrix operator*(const double k, const Matrix& R);
Matrix operator*(const Matrix& L, const double k);

// b) Functions:
Matrix read(const std::string fullway2data);
void print(const Matrix& Any, unsigned int precicion = 4);
const double get_norm(const Matrix any);