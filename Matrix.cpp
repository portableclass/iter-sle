#include "Matrix.h"
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <fstream>
#include <sstream>
#include <iomanip>

// -1) The private geter gets a linear index:
const unsigned int Matrix::get_index(unsigned int row, unsigned int col) const
{
	// n = i - 1 + (j - 1) * rown    � ������, ���� i in [1, rown], � j in [1, coln]  =>
	// => return row - 1 + (col - 1) * this->rown;
	// n = i + j * rown		� ������, ���� i in [0, rown-1], � j in [0, coln-1] =>
	// => return row + col * this->rown;
	// ������ ��������� �������� � exel ����� �������.

	assert((col < this->coln) && "ERROR_MATRIX_INDEX_IS_OUT_SIZE"); // assert(bool = true)
	assert((row < this->rown) && "ERROR_MATRIX_INDEX_IS_OUT_SIZE");

	return row + col * this->rown;
}

// 1) �onstructors:
Matrix::Matrix() : values(0), rown(0), coln(0) {}
Matrix::Matrix(const unsigned int rown, const unsigned int coln) : rown(rown), coln(coln), values(coln* rown) {}


// 2) Destructior:
Matrix::~Matrix()
{
	values.clear();
	values.shrink_to_fit();
}

// 3) Geters and seters:
const unsigned int Matrix::get_rSize() const
{
	return this->rown;
}
const unsigned int Matrix::get_cSize() const
{
	return this->coln;
}


// 4) Operators:
double& Matrix::operator()(const unsigned int row, const unsigned int col)
{
	return this->values.at(get_index(row, col));
}
const double& Matrix::operator()(const unsigned int row, const unsigned int col) const
{
	return this->values.at(get_index(row, col));
};

Matrix& Matrix::operator=(const Matrix& Any)
{
	// 0. �������� �� ��������������.
	if (this == &Any)
	{
		return *this;
	}

	// 1. The copying of the object values:
	this->coln = Any.coln;
	this->rown = Any.rown;
	this->values = Any.values;

	return *this;
}
Matrix& Matrix::operator+=(const Matrix& R)
{
	// 0. Checking of the sizes:s
	assert((this->rown == R.rown) && (this->coln == R.coln) && "ERROR_MATRIXES_SIZES_SHOULD_BE_EQUAL");
	assert((this->rown != 0) && (this->coln != 0) && "ERROR_MATRIXES_SIZES_SHOULD_BE_NO_ZERO");

	// ����� ���������������� �������:
	// +: ����������������
	// -: � ������ ������� ������������ (�� ����� ���� ���)
	for (size_t i = 0; i < this->values.size(); i++)
	{
		this->values.at(i) += R.values.at(i);
	}

	// ������� ������������ ������������� �����:
	// +: � ������ ����� �������������� ���� ���� ����� ���� : " (*this)(row, col) +=... " ����� ��������
	// -: ���� ����� ���������������� (�� ����� ���� ������� �� ����� ������������)
	// 
	// for (size_t row = 0; row < this->rown; row++)
	// {
	// 	 for (size_t col = 0; col < this->coln; col++)
	//	 {
	//		 (*this)(row, col) += R(row, col);
	//	 }
	// }

	return *this;
}
Matrix& Matrix::operator-=(const Matrix& R)
{
	// 0. Checking of the sizes:
	assert((this->rown == R.rown) && (this->coln == R.coln) && "ERROR_MATRIXES_SIZES_SHOULD_BE_EQUAL");
	assert((this->rown != 0) && (this->coln != 0) && "ERROR_MATRIXES_SIZES_SHOULD_BE_NO_ZERO");

	// 0. Checking of the sizes:
	for (size_t i = 0; i < this->values.size(); i++)
	{
		this->values.at(i) -= R.values.at(i);
	}

	return *this;
}
Matrix& Matrix::operator*=(const double k)
{
	// 0. Checking of the sizes:
	assert((this->rown != 0) && (this->coln != 0) && "ERROR_MATRIXES_SIZES_SHOULD_BE_NO_ZERO");

	for (size_t i = 0; i < this->values.size(); i++)
	{
		this->values.at(i) *= k;
	}

	return *this;
}
Matrix& Matrix::operator*=(const Matrix& R)
{
	// 0. Checking of the sizes:
	assert((this->coln == R.rown) && "ERROR_NUMBERS_LEFT_MATRIX_COLUMNS_AND_RIGHT_MATRIX_ROWS_SHOULD_BE_EQUAL");
	assert((this->coln != 0) && "ERROR_MATRIXES_SIZES_SHOULD_BE_NO_ZERO");
	assert((this->rown != 0) && (R.coln != 0) && "ERROR_MATRIXES_SIZES_SHOULD_BE_NO_ZERO");

	Matrix Res(this->rown, R.coln);

	for (size_t col = 0; col < R.coln; col++)
	{
		for (size_t row = 0; row < this->rown; row++)
		{
			for (size_t i = 0; i < this->coln; i++)
			{
				Res(row, col) += (*this)(row, i) * R(i, col); // (*this)(row, col) - ���������� ������ �� �������
			}
		}
	}

	*this = Res;

	return *this;
}

Matrix operator+(const Matrix& L, const Matrix& R)
{
	// 0. Checking of the sizes:
	assert((L.get_cSize() == R.get_cSize()) && "ERROR_MATRIXES_SIZES_SHOULD_BE_EQUAL");
	assert((L.get_rSize() == R.get_rSize()) && "ERROR_MATRIXES_SIZES_SHOULD_BE_EQUAL");
	assert((L.get_rSize() != 0) && (R.get_cSize() != 0) && "ERROR_MATRIXES_SIZES_SHOULD_BE_NO_ZERO");

	return Matrix(L) += R; // �������� ��������� ������ ������������
	// �������������� ������, ����������� �� ������������� ������������ � ��������� +=.
	//Matrix Res(L.get_rSize(), R.get_cSize());
	//
	//for (size_t col = 0; col < R.get_cSize(); col++)
	//{
	//	for (size_t row = 0; row < L.get_rSize(); row++)
	//	{
	//		Res(row, col) = L(row, col) + R(row, col);
	//	}
	//}
	// 
	//return Res;
}
Matrix operator-(const Matrix& L, const Matrix& R)
{
	// 0. Checking of the sizes:
	assert((L.get_cSize() == R.get_cSize()) && "ERROR_MATRIXES_SIZES_SHOULD_BE_EQUAL");
	assert((L.get_rSize() == R.get_rSize()) && "ERROR_MATRIXES_SIZES_SHOULD_BE_EQUAL");
	assert((L.get_rSize() != 0) && (R.get_cSize() != 0) && "ERROR_MATRIXES_SIZES_SHOULD_BE_NO_ZERO");

	return Matrix(L) -= R; // �������� ��������� ������ ������������
	// �������������� ������, ����������� �� ������������� ������������ � ��������� -=.
	//Matrix Res(L.get_rSize(), R.get_cSize());
	// 
	//for (size_t col = 0; col < R.get_cSize(); col++)
	//{
	//	for (size_t row = 0; row < L.get_rSize(); row++)
	//	{
	//		Res(row, col) = L(row, col) - R(row, col);
	//	}
	//}
	// 
	//return Res;
}
Matrix operator*(const Matrix& L, const Matrix& R)
{
	// 0. Checking of the sizes:
	assert((L.get_cSize() == R.get_rSize()) && "ERROR_NUMBERS_LEFT_MATRIX_COLUMNS_AND_RIGHT_MATRIX_ROWS_SHOULD_BE_EQUAL");
	assert((L.get_cSize() != 0) && "ERROR_MATRIXES_SIZES_SHOULD_BE_NO_ZERO");
	assert((L.get_rSize() != 0) && (R.get_cSize() != 0) && "ERROR_MATRIXES_SIZES_SHOULD_BE_NO_ZERO");

	//return Matrix(L) *= R; // �������� ��������� ������ ������������ // 1 ����������� L, 2 ����������� � ��������� �� ��������� ������� *=
	// �������������� ������, ����������� �� ������������� ������������ � ��������� *=.

	Matrix Res(L.get_rSize(), R.get_cSize());

	for (size_t col = 0; col < R.get_cSize(); col++)
	{
		for (size_t row = 0; row < L.get_rSize(); row++)
		{
			for (size_t i = 0; i < L.get_cSize(); i++)
			{
				Res(row, col) += L(row, i) * R(i, col);
			}
		}
	}

	return Res;
}
Matrix operator*(const double k, const Matrix& R)
{
	// 0. Checking of the sizes:
	assert((R.get_rSize() != 0) && (R.get_cSize() != 0) && "ERROR_MATRIXES_SIZES_SHOULD_BE_NO_ZERO");

	return Matrix(R) *= k;// �������� ��������� ������ ������������
	// �������������� ������, ����������� �� ������������� ������������ � ��������� +=.
	//Matrix Res(R.get_rSize(), R.get_cSize());
	// 
	//for (size_t col = 0; col < R.get_cSize(); col++)
	//{
	//	for (size_t row = 0; row < R.get_rSize(); row++)
	//	{
	//		Res(row, col) *= k;
	//	}
	//}
	// 
	//return Res;
}
Matrix operator*(const Matrix& L, const double k)
{
	// 0. Checking of the sizes:
	assert((L.get_rSize() != 0) && (L.get_cSize() != 0) && "ERROR_MATRIXES_SIZES_SHOULD_BE_NO_ZERO");

	return Matrix(L) *= k;	// �������� ��������� ������ ������������
	// �������������� ������, ����������� �� ������������� ������������ � ��������� *=.
	//Matrix Res(L.get_rSize(), L.get_cSize());
	// 
	//for (size_t col = 0; col < L.get_cSize(); col++)
	//{
	//	for (size_t row = 0; row < L.get_rSize(); row++)
	//	{
	//		Res(row, col) *= k;
	//	}
	//}
	// 
	//return Res;
}

Matrix read(const std::string fullway2data)
{
	std::ifstream inputfile;
	inputfile.open(fullway2data);

	Matrix Res;

	if (inputfile.is_open())
	{
		std::string buff_s;
		double buff_d;
		std::vector <std::vector<double>> buff_data;
		std::vector <double> buff_data_row;

		while (getline(inputfile, buff_s))
		{
			std::istringstream buff_ss(buff_s);

			while (buff_ss >> buff_d)
			{
				buff_data_row.push_back(buff_d);
			}

			buff_data.push_back(buff_data_row);
			buff_data_row.clear();
		}

		Res = Matrix(buff_data.size(), buff_data.at(0).size());

		for (size_t row = 0; row < Res.get_rSize(); row++)
		{
			assert((buff_data.at(row).size() == Res.get_cSize()) && "ERROR_COPIED_MATRIX_COLUMNS_SIZES_SHOULD_BE_EQUAL");

			if (buff_data.at(row).size() != Res.get_cSize())
			{
				std::cout << "ERROR: copying matrix is failed! Process was stopped!" << std::endl;

				return Res;
			}

			for (size_t col = 0; col < Res.get_cSize(); col++)
			{
				Res(row, col) = buff_data.at(row).at(col);
			}
		}
	}
	else
	{
		std::cout << "ERROR: copying matrix is failed! File isn't opened!" << std::endl;
	}

	return Res;
}
void print(const Matrix& Any, unsigned int precicion)
{
	if ((Any.get_rSize() == 0) || (Any.get_cSize() == 0))
	{
		std::cout << "WARNING: printed matrix is empty!" << std::endl;
	}

	for (size_t i = 0; i < Any.get_rSize(); i++)
	{
		for (size_t j = 0; j < Any.get_cSize(); j++)
		{
			std::cout << std::setprecision(precicion) << std::scientific << Any(i, j) << "		";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

const double get_norm(const Matrix any)
{
	double value_max = std::abs(any(0, 0));

	for (size_t col = 0; col < any.get_cSize(); col++) {
		for (size_t row = 0; row < any.get_rSize(); row++) {
			value_max = std::max(value_max, std::abs(any(row, col)));
		}
	}

	return value_max;
}