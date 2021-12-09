#include "Task.h"

#include <iostream>
#include <vector>
#include "Matrix.h"
#include <cassert>


const std::vector<std::string> names({ "A", "b" });


Task::Task(const Matrix& A, const Matrix& b)
{
	assert(((A.get_cSize() == A.get_rSize()) && (A.get_rSize() != 0)) && "ERROR_MATRIX_SHOULD_BE_SQUARE");
	assert(((A.get_cSize() == b.get_rSize()) && (b.get_cSize() == 1)) && "ERROR_MATRIX_SHOULD_BE_SQUARE");

	this->data = std::vector<Matrix>({ A, b });
	this->empty_flag = false;

	std::cout << "The task was set successfully" << std::endl;
}

const Matrix& Task::at(const tsk key) const
{
	return data.at(static_cast<unsigned>(key));
}

bool isempty(const Task& t)
{
	return t.empty_flag;
}
