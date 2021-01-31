#include "2015_11.h"

namespace Day11_2015
{
	void inc(string& password)
	{
		size_t i = password.size() - 1;
		while (1)
		{
			password[i]++;
			if (password[i] != '{')
				break;

			password[i] = 'a';
			if (i == 0)
				break;

			i--;
		}
	}

	bool valid(const string& password)
	{
		bool ok = false;
		for (size_t i = 0; i < password.size() - 2; i++)
			if (password[i] + 1 == password[i + 1] && password[i + 1] + 1 == password[i + 2])
				ok = true;

		if (!ok)
			return false;

		for (auto c : password)
			if (c == 'i' || c == 'o' || c == 'l')
				return false;

		size_t c = 0;
		size_t i = 0;
		while (i < password.size())
		{
			if (password[i + 1] == password[i])
			{
				i++;
				c++;
			}

			i++;
		}
		return c >= 2;
	}

	bool next(string& password)
	{
		inc(password);
		return valid(password);
	}

	vector<string> both_parts(string password)
	{
		vector<string> solution;
		for (int i = 0; i < 2; i++)
		{
			while (!next(password));
			solution.push_back(password);
		}

		return solution;
	}

	t_output main(const t_input& input)
	{
		auto t0 = chrono::steady_clock::now();
		auto px = both_parts(input[0]);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(px[0]);
		solutions.push_back(px[1]);
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
