#include "Method.h"
#include <string>
#include <vector>


// *********************

const std::vector <funs::funptr_t> methods({ funs::LU, funs::JACOBI, funs::SEIDEL });
const std::vector <std::string> names({ "LU", "JACOBI", "SEIDEL" });

Matrix funs::LU(const Matrix& A, const Matrix& b, const Options& options)
{
    return Matrix();
}

Matrix funs::JACOBI(const Matrix& A, const Matrix& b, const Options& options)
{

    Matrix x(b.get_rSize(), b.get_cSize());
    Matrix x_prev(b.get_rSize(), b.get_cSize());

    int maxiter = options.get().maxitr;
    int accst = options.get().accst;

    Matrix revD(A.get_rSize(), A.get_cSize());
    for (size_t i = 0; i < A.get_rSize(); i++)
        revD(i, i) = 1 / A(i, i);
    Matrix g = revD * b;

    ////////////////////////////////////////// убрать
    int column = A.get_cSize();
    int row = A.get_rSize();
    int size = A.get_cSize();
    Matrix L(row, column);
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
            if (i > j)
                L(i, j) = A(i, j);
    }
    Matrix U(row, column);

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
            if (i < j)
                U(i, j) = A(i, j);
    }
    //////////////////////////////////////

    Matrix B = revD * (L + U);
    double norm;
    int iter = 0;

    do {
        x_prev = x;
        x = g - B * x_prev;
        norm = get_norm(x - x_prev);
        std::cout << iter << std::endl;
        iter++;
    } while (norm > accst && maxiter >= iter);

    return x;
}

Matrix funs::SEIDEL(const Matrix& A, const Matrix& b, const Options& options)
{
    Matrix x(b.get_rSize(), b.get_cSize());
    Matrix x_prev(b.get_rSize(), b.get_cSize());

    double norm;
    int iter = 0;
    double sum1, sum2;
    int maxiter = options.get().maxitr;
    int accst = options.get().accst;

    do {
        x_prev = x;
        for (size_t i = 0; i < x.get_rSize(); i++)
        {
            sum1 = 0;
            sum2 = 0;
            //std::cout << "i: " << i << std::endl;
            for (int loop1 = i - 1; loop1 > 0; loop1--)
            {
                //std::cout << "loop1: " << loop1 << std::endl;
                sum1 += A(i, loop1) * x(loop1, 0);
            }

            //std::cout << "check: " << std::endl;
            for (int loop2 = i + 1; loop2 < x.get_rSize(); loop2++)
            {
                //std::cout << "loop2: " << loop2 << std::endl;
                sum2 += A(i, loop2) * x_prev(loop2, 0);
            }

            x(i, 0) = (b(i, 0) - sum1 - sum2) / A(i, i);
        }
        norm = get_norm(x - x_prev);
        std::cout << iter << std::endl;
        iter++;
        //std::cout << "norm: "  << norm << std::endl;
    } while (norm > accst && maxiter >= iter);

    return x;
}

// *********************

Method::Method() : key(mtd::defult), ptr(methods.at(static_cast<unsigned>(mtd::defult))) {};

Method::Method(const mtd m) : key(m), ptr(methods.at(static_cast<unsigned>(m))) {};

const funs::funptr_t Method::get() const
{
    return this->ptr;
}
void Method::set(const mtd m)
{
    this->key = m;
    this->ptr = methods.at(static_cast<unsigned>(m));
}