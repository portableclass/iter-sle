#include "Method.h"
#include <string>
#include <vector>

// *********************

const std::vector <funs::funptr_t> methods({ funs::LU, funs::JACOBI, funs::SEIDEL });
const std::vector <std::string> names({ "LU", "JACOBI", "SEIDEL" });

Matrix funs::LU(const Matrix& A, const Matrix& b, const Options& options)
{
    unsigned int size = A.get_cSize();
    Matrix LU(size, size);
    Matrix L(size, size);
    Matrix U(size, size);
    double temp;

    // Setting the value 1 to the main diagonal of the Matrix L
    for (size_t i = 0; i < size; i++)
        L(i, i) = 1;

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            temp = 0;

            if (i <= j)
            {
                // Determination of the elements of the Matrix U
                for (size_t k = 0; k < i; k++)
                    temp += L(i, k) * U(k, j);
                U(i, j) = A(i, j) - temp;
            }
            else
            {
                // Determination of the elements of the Matrix L
                for (size_t k = 0; k < i; k++)
                    temp += L(i, k) * U(k, j);
                L(i, j) = (A(i, j) - temp) / U(j, j);
            }

        }
    }

    // Writing the LU Matrix in compact form
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            if (i <= j)
                LU(i, j) = U(i, j);
            else
                LU(i, j) = L(i, j);
        }
    }

    if (LU(0, 0) == 0) {
        // required = the number of the row in which A[required][0] != 0 
        unsigned int required;
        for (required = 1; required < LU.get_rSize(); required++)
        {
            if (LU(required, 0) != 0) {
                double temp;
                for (size_t col = 0; col < LU.get_cSize(); col++)
                {
                    temp = LU(required, col);
                    LU(required, col) = LU(required + 1, col);
                    LU(required + 1, col) = temp;
                }
                break;
            }
        }
    }

    Matrix y(b.get_rSize(), 1);
    Matrix x(b.get_rSize(), 1);

    // reverse move for matrix L
    y(0, 0) = b(0, 0);
    for (size_t k = 1; k < L.get_rSize(); k++)
    {
        y(k, 0) = b(k, 0);
        for (size_t p = 0; p < k; p++)
            y(k, 0) = y(k, 0) - L(k, p) * y(p, 0);
    }

    // reverse move for matrix U
    const unsigned int sizeForX = U.get_rSize() - 1;
    x(sizeForX, 0) = y(sizeForX, 0) / U(sizeForX, sizeForX);
    for (int k = sizeForX - 1; k >= 0; k--)
    {
        x(k, 0) = y(k, 0);
        for (size_t p = k + 1; p < sizeForX + 1; p++)
            x(k, 0) = x(k, 0) - U(k, p) * x(p, 0);
        x(k, 0) = x(k, 0) / U(k, k);
    }

    std::cout << "Selected method: " << names.at(static_cast<unsigned>(mtd::LU)) << std::endl;
    return x;
}


Matrix funs::JACOBI(const Matrix& A, const Matrix& b, const Options& options)
{
    Matrix x(b.get_rSize(), b.get_cSize());
    Matrix x_prev(b.get_rSize(), b.get_cSize());
    double norm;
    unsigned int iter = 0;
    const unsigned int size = A.get_cSize();
    Matrix revD(size, size);

    ////////////////////////////////////////// óáðàòü
    Matrix L(size, size);
    Matrix U(size, size);
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            if (i > j)
                L(i, j) = A(i, j);
            if (i < j)
                U(i, j) = A(i, j);
        }
        revD(i, i) = 1 / A(i, i);
    }
    //////////////////////////////////////

    Matrix g = revD * b;
    Matrix B = revD * (L + U);

    do {
        x_prev = x;
        x = g - B * x_prev;
        norm = get_norm(x - x_prev);
        iter++;
    } while (norm > options.get().accst && options.get().maxitr >= iter);

    std::cout << "Selected method: " << names.at(static_cast<unsigned>(mtd::JACOBI)) << std::endl;
    std::cout << "Quantity iterations: " << iter << std::endl;
    return x;
}


Matrix funs::SEIDEL(const Matrix& A, const Matrix& b, const Options& options)
{
    Matrix x(b.get_rSize(), 1);
    Matrix x_prev(b.get_rSize(), 1);
    double norm;
    unsigned int iter = 0;
    double sum1, sum2;

    do {
        x_prev = x;
        for (size_t i = 0; i < x.get_rSize(); i++)
        {
            sum1 = 0;
            sum2 = 0;

            for (int loop1 = i - 1; loop1 > 0; loop1--)
                sum1 += A(i, loop1) * x(loop1, 0);
            for (int loop2 = i + 1; loop2 < x.get_rSize(); loop2++)
                sum2 += A(i, loop2) * x_prev(loop2, 0);

            x(i, 0) = (b(i, 0) - sum1 - sum2) / A(i, i);
        }
        norm = get_norm(x - x_prev);
        iter++;
    } while (norm > options.get().accst && options.get().maxitr >= iter);

    std::cout << "Selected method: " << names.at(static_cast<unsigned>(mtd::SEIDEL)) << std::endl;
    std::cout << "Quantity iterations: " << iter << std::endl;
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