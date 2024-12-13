#include "2024_07.h"

namespace Day07_2024
{
	int64_t Main::solve(const string& input, const string& ops_defined)
	{
		// load result
		size_t pos = input.find(":");
		int64_t result = stoll(input.substr(0, pos));

		// load arguments, store pow10 coefficients according to number of digits of argument
		string s;
		vector<int64_t> args;
		vector<int64_t> pow10;
		stringstream ss(input.substr(pos + 2));
		while (getline(ss, s, ' '))
		{
			args.push_back(stoll(s));
			pow10.push_back(int64_t(pow(10, (int)s.size())));
		}

		// operands tuple
		vector<int> op = vector<int>(args.size() - 1, 0);

		// test combinations
		while (1)
		{
			// evaluate
			int64_t v = args[0];
			for (size_t i = 1; i < args.size(); i++)
			{
				switch (ops_defined[op[i - 1]])
				{
				case '+': v += args[i]; break;
				case '*': v *= args[i]; break;
				default: v = v * pow10[i] + args[i]; break;
				}
			}

			// check result
			if (v == result)
				return v;

			// next operands tuple
			size_t i = 0;
			while (1)
			{
				if (++op[i] < (int)ops_defined.size())
					break;
				
				op[i] = 0;
				if (++i == op.size())
					return 0;
			}
		}
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return accumulate(input.begin(), input.end(), 0LL, [](int64_t v, const string& s) { return v + solve(s, "+*"); });
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return accumulate(input.begin(), input.end(), 0LL, [](int64_t v, const string& s) { return v + solve(s, "+*|"); });
	}
}
