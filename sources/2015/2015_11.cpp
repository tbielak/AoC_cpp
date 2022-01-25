#include "2015_11.h"

namespace Day11_2015
{
	void Main::inc(string& password)
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

	bool Main::valid(const string& password)
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

	bool Main::next(string& password)
	{
		inc(password);
		return valid(password);
	}

	AoC::Output Main::both_parts(const string& input)
	{
		string password = input;
		vector<string> solution;
		for (int i = 0; i < 2; i++)
		{
			while (!next(password));
			solution.push_back(password);
		}

		return solution;
	}
}
