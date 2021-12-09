#pragma once

#include "Task.h"
#include "Method.h"
#include "Options.h"
#include "Matrix.h"


class SLE
{
private:
	// 0) Values:
	Task _task;
	Method _method;
	Options _options;

	Matrix _solution;
	bool _solve_flag;

public:
	SLE() = delete;
	SLE(const Task& t, const Method& m = Method(), const Options& o = Options());

	const Matrix& solve();

	const Matrix& solution();
	const Options& options() const;
	const Method& method() const;

	bool options(const Options& opt);
	bool method(mtd m);

	friend bool issolve(const SLE& s);
};