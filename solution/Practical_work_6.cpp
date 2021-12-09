// Practical_work_6.cpp

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include "Matrix.h"
#include "Method.h"
#include "Options.h"
#include "Task.h"
#include "SLE.h"
#include <fstream>
#include <ctime>
#include <cassert>

void saveArray(const char* nameFile, double* ptr2deltaArray, const int iterEnd = 1);

enum class ERROR
{
    begin,

    EMPTY = begin,
    MAIN_CRITERION = 1,
    SIZE_CHECK = 2,
    SQUARE_CHECK = 3,

    end,

    common = EMPTY,
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
    std::string fullway2data = "E:\\input.txt";
    const Matrix A = read(fullway2data);

    // checking
    double sum_diag = 0;
    ERROR flag = ERROR::common;

    for (size_t i = 0; i < A.get_rSize(); i++)
        for (size_t j = 0; j < A.get_cSize(); j++)
            if (i != j)
                sum_diag += A(i, j);

    for (size_t i = 0; i < A.get_rSize(); i++)
        if (A(i, i) < sum_diag)
            flag = ERROR::MAIN_CRITERION;

    if (A.get_cSize() == 0 || A.get_rSize() == 0)
        flag = ERROR::SIZE_CHECK;

    if (A.get_cSize() != A.get_rSize())
        flag = ERROR::SQUARE_CHECK;

    if (flag != ERROR::common)
    {
        std::string report;
        switch (flag)
        {
        case(ERROR::MAIN_CRITERION):
            report = "ERROR. THE VALUE OF THE DIAGONAL ELEMENT OF THE MATRIX \nMUST BE GREATER THAN OR EQUAL TO \nTHE SUM OF THE NON-DIAGONAL ELEMENTS.";
            break;
        case(ERROR::SIZE_CHECK):
            report = "ERROR. MATRIX SIZES SHOULD BE NO ZERO";
            break;
        case(ERROR::SQUARE_CHECK):
            report = "ERROR. MATRIX SHOULD BE SQUARE";
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
    const Matrix b = A * x_exist;

    // configuring SLE
    Task task(A, b);
    Options options(true, 100, 1e-16);
    double seconds;

    // calling solution methods
    for (size_t i = 0; i < 10; i++)
    {
        for (mtd i = mtd::begin; i != mtd::end; ++i)
        {

            SLE sle(task, Method(i), options);
            clock_t start = clock();
            if (sle.options().get().rep == true)
                print(sle.solution());
            else
                sle.solution();
            clock_t end = clock();
            seconds = ((double)end - start) / CLOCKS_PER_SEC;
            /*  printf("The time: %f seconds\n\n\n", seconds);*/
            saveArray("E:\\hello.txt", &seconds);
        }

        std::ofstream bebrik;
        bebrik.open("E:\\hello.txt", std::ios::app);
        bebrik << "\n";
        bebrik.close();
    }

    return 0;
}

void saveArray(const char* nameFileAndWay, double* ptr2deltaArray, const int iterEnd)
{
    std::ofstream out;
    out.open(nameFileAndWay, std::ios::app);
    if (out.is_open())
    {
        out.width(10);
        out.precision(16);

        for (int iter = 0; iter < iterEnd; iter++)
            out << *(ptr2deltaArray + iter) << " ";
    }
};
