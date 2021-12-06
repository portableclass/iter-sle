// Practical_work_6_5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include "Matrix.h"
#include "Method.h"
#include "Options.h"
#include "Task.h"
#include "SLE.h"

//const Matrix get_L(const Matrix any);
//const Matrix get_U(const Matrix any);
//const double get_norm(const Matrix any);
//const Matrix yakobi(const Matrix A, const Matrix b, const double eps = 10e-60);
//const Matrix zeidel(const Matrix A, const Matrix b, const double eps = 10e-60);

enum class ERROR
{
    begin,
    EMPTY = begin,
    MAIN_CRITERION = 1,
    SIZE_CHECK = 2,

    end,
};

//ERROR& operator++(ERROR& e)
//{
//    e = ERROR(static_cast<int>(e) + 1);
//    return e;
//}

mtd& operator++(mtd& e)
{
    e = mtd(static_cast<int>(e) + 1);
    return e;
}

int main()
{
    std::string fullway2data = "F:\\lessons third training course\\Численные методы\\практические\\5\\решенное\\Файлы программы\\input.txt";
    //const Matrix& A = read(fullway2data);
    Matrix A = read(fullway2data);

    double sum_diag = 0; 
    ERROR flag = ERROR::EMPTY;

    for (size_t i = 0; i < A.get_rSize(); i++)
        for (size_t j = 0; j < A.get_cSize(); j++)
            if (i != j)
                sum_diag += A(i, j);

    for (size_t i = 0; i < A.get_rSize(); i++)
        if (A(i, i) < sum_diag)
            flag = ERROR::MAIN_CRITERION;

    if (flag != ERROR::EMPTY)
    {
        std::string report;
        switch (flag) 
        {
            case(ERROR::MAIN_CRITERION):
                report = "ERROR. THE VALUE OF THE DIAGONAL ELEMENT OF THE MATRIX \nMUST BE GREATER THAN OR EQUAL TO \nTHE SUM OF THE NON-DIAGONAL ELEMENTS.";
                break;
            case(ERROR::SIZE_CHECK):
                break;
        }

        std::cout << report;
        return 0;
    }


    Matrix x_exist(A.get_cSize(), 1);

    // filling x_exist with values from 1 to the number of columns of matrix A
    unsigned int temp = 0;
    for (size_t i = 0; i < x_exist.get_rSize(); i++)
    {
        temp = i + 1;
        x_exist(i, 0) = temp;
    }

    // setting the values of the vector of the right part
    //const Matrix& b = A * x_exist;
    Matrix b = A * x_exist;

    /////////////////////////////////////////////////////////////////////////////////

    tsk a = tsk::A;
    Task task(A, b);
    print(task.at(a));
    /*mtd aboba = mtd::JACOBI;*/
    for (mtd i = mtd::begin; i != mtd::end; ++i)
    {
        SLE sle(task, Method(i));
        if (sle.options().get().rep == true)
        {
            print(sle.solution());
        }
    }

    /*Method method(aboba);*/
    //SLE sle(task, method);
    ////print(sle.solve());
    //print(sle.solution());
    //print(zeidel(A, b));

    return 0;
}

//const Matrix get_L(const Matrix any)
//{
//    const unsigned int size = any.get_cSize();
//    Matrix L(size, size);
//
//    for (size_t i = 0; i < size; i++)
//    {
//        for (size_t j = 0; j < size; j++)
//            if (i > j)
//                L(i, j) = any(i, j);
//    }
//
//    return L;
//}
//const Matrix get_U(const Matrix any)
//{
//    const unsigned int size = any.get_cSize();
//    Matrix U(size, size);
//
//    for (size_t i = 0; i < size; i++)
//    {
//        for (size_t j = 0; j < size; j++)
//            if (i < j)
//                U(i, j) = any(i, j);
//    }
//
//    return U;
//}
////const Matrix get_D(const Matrix any)
////{
////    const unsigned int size = any.get_cSize();
////    Matrix D(size, size);
////
////    for (size_t i = 0; i < size; i++)
////        D(i, i) = any(i, i);
////
////    return D;
////}
////const Matrix reverse_D(const Matrix any)
////{
////    const unsigned int size = any.get_cSize();
////    Matrix result(size, size);
////
////    for (size_t i = 0; i < size; i++)
////        if (any(i, i) != 0)
////            result(i, i) = 1/any(i, i);
////
////    return result;
////}
//
//const Matrix yakobi(const Matrix A, const Matrix b, const double eps)
//{
//    Matrix x(b.get_rSize(), b.get_cSize());
//    Matrix x_prev(b.get_rSize(), b.get_cSize());
//
//    Matrix revD(A.get_rSize(), A.get_cSize());
//    for (size_t i = 0; i < A.get_rSize(); i++)
//        revD(i, i) = 1/A(i, i);
//    Matrix g = revD * b;
//    Matrix B = revD * (get_L(A) + get_U(A));
//    double norm;
//    int iter = 0;
//
//    do {
//        x_prev = x;
//        x = g - B * x_prev;
//        norm = get_norm(x - x_prev);
//        std::cout << iter << std::endl;
//        iter++;
//    } while (norm > eps);
//
//    return x;
//}
//
//const Matrix zeidel(const Matrix A, const Matrix b, const double eps)
//{
//    Matrix x(b.get_rSize(), b.get_cSize());
//    Matrix x_prev(b.get_rSize(), b.get_cSize());
//
//    double norm;
//    int iter = 0;
//    double sum1, sum2;
//
//    do {
//        x_prev = x;
//        for (size_t i = 0; i < x.get_rSize(); i++)
//        {
//            sum1 = 0;
//            sum2 = 0;
//            //std::cout << "i: " << i << std::endl;
//            for (int loop1 = i - 1; loop1 > 0; loop1--)
//            {
//                //std::cout << "loop1: " << loop1 << std::endl;
//                sum1 += A(i, loop1) * x(loop1, 0);
//            }
//
//            //std::cout << "check: " << std::endl;
//            for (int loop2 = i + 1; loop2 < x.get_rSize(); loop2++)
//            {
//                //std::cout << "loop2: " << loop2 << std::endl;
//                sum2 += A(i, loop2) * x_prev(loop2, 0);
//            }
//
//            x(i, 0) = (b(i, 0) - sum1 - sum2) / A(i, i);
//        }
//        norm = get_norm(x - x_prev);
//        std::cout << iter << std::endl;
//        iter++;
//        //std::cout << "norm: "  << norm << std::endl;
//    } while (norm > eps);
//
//    return x;
//}
//
//const double get_norm(const Matrix any)
//{
//    double value_max = std::abs(any(0, 0));
//
//    for (size_t col = 0; col < any.get_cSize(); col++) {
//        for (size_t row = 0; row < any.get_rSize(); row++) {
//            value_max = std::max(value_max, std::abs(any(row, col)));
//        }
//    }
//
//    return value_max;
//}
