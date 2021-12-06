#include "SLE.h"
#include "Task.h"
#include "Method.h"
#include "Options.h"
#include "Matrix.h"

#include <iostream>
#include <cassert>

bool issolve(const SLE& s)
{
	return s._solve_flag;
}

SLE::SLE(const Task& t, const Method& m, const Options& o) : _task(t)
{
	assert(isempty(t) == false && "ERROR_WAS_SET_EMPTY_TASK!");

	this->_method = m;
	this->_options = o;
	this->_solution = Matrix();
	this->_solve_flag = false;

	std::cout << "The SLE was set successfully!" << std::endl;
}

const Matrix& SLE::solve()
{
	if (this->_solve_flag == true)
		return _solution;
	else
	{
		funs::funptr_t ptr = this->_method.get();
		this->_solution = ptr(this->_task.at(tsk::A), this->_task.at(tsk::b), this->_options);

		this->_solve_flag == true;
	}
}

const Matrix& SLE::solution()
{
	this->solve();

	return this->_solution;
}

const Options& SLE::options() const
{
	return this->_options;
}

const Method& SLE::method() const
{
	return this->_method;
}

bool SLE::options(const Options& opt)
{
	return false;
}

bool SLE::method(mtd m)
{
	return false;
}
