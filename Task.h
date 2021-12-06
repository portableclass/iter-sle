#pragma once

#include <iostream>
#include <vector>
#include "Matrix.h"

enum class tsk : unsigned
{
	A = 0,
	b = 1,
};


class Task
{
private:
	std::vector<Matrix> data;
	bool empty_flag;

public:
	Task() = delete;
	Task(const Matrix& A, const Matrix& b);

	const Matrix& at(const tsk key) const;

	friend bool isempty(const Task& t);
};