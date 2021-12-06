#pragma once

// *********************
#include "Matrix.h"
#include "Options.h"

enum class mtd : unsigned
{
	begin = 0,

	LU = begin,
	JACOBI = 1,
	SEIDEL = 2,

	end,

	defult = LU,
};

namespace funs
{
	using funptr_t = Matrix(*)(const Matrix&, const Matrix&, const Options&);

	Matrix LU(const Matrix& A, const Matrix& b, const Options& options);
	Matrix JACOBI(const Matrix& A, const Matrix& b, const Options& options);
	Matrix SEIDEL(const Matrix& A, const Matrix& b, const Options& options);
}

// *********************



class Method
{
private:
	funs::funptr_t ptr;
	mtd key;

public:
	Method();
	Method(const mtd m);

	const funs::funptr_t get() const;
	void set(const mtd m);
};