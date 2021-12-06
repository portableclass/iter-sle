#pragma once

namespace opt
{
	struct OPTIONS_s
	{
		bool rep = true;
		unsigned int maxitr = 100;
		double accst = 1e-3;
	};
}

class Options
{
private:
	opt::OPTIONS_s options;

public:
	Options(const opt::OPTIONS_s opt);
	Options(const bool iterrep = opt::OPTIONS_s().rep, const unsigned int maxiter = opt::OPTIONS_s().maxitr, const double accurasitu = opt::OPTIONS_s().accst);

	void set(const opt::OPTIONS_s& opt);

	const opt::OPTIONS_s& get() const;
};