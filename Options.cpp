#include "Options.h"
#include <iostream>

Options::Options(const opt::OPTIONS_s opt)
{
	this->options.rep = opt.rep;

	if (opt.maxitr > 0)
	{
		this->options.maxitr = opt.maxitr;
		std::cout << "The MAXITER was set successfully!" << std::endl;
	}
	if (opt.accst > 0)
	{
		this->options.accst = opt.accst;
		std::cout << "The MAXITER was set successfully!" << std::endl;
	}
	else
		std::cout << "The MAXITER and ACCURASITY were set default values!" << std::endl;
}

Options::Options(const bool iterrep, const unsigned int maxiter, const double accurasitu)
{
	this->options.rep = iterrep;

	if (maxiter > 0)
	{
		this->options.maxitr = maxiter;
		std::cout << "The MAXITER was set successfully!" << std::endl;
	}
	if (accurasitu > 0)
	{
		this->options.accst = accurasitu;
		std::cout << "The MAXITER was set successfully!" << std::endl;
	}
	else
		std::cout << "The MAXITER and ACCURASITY were set default values!" << std::endl;
}

void Options::set(const opt::OPTIONS_s& opt)
{
	this->options.rep = opt.rep;

	if (opt.maxitr > 0)
	{
		this->options.maxitr = opt.maxitr;
		std::cout << "The MAXITER was set successfully!" << std::endl;
	}
	if (opt.accst > 0)
	{
		this->options.accst = opt.accst;
		std::cout << "The MAXITER was set successfully!" << std::endl;
	}
	else
		std::cout << "The MAXITER and ACCURASITY were set default values!" << std::endl;
}

const opt::OPTIONS_s& Options::get() const
{
	return this->options;
}
