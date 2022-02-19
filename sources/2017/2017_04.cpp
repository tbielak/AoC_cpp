#include "2017_04.h"

namespace Day04_2017
{
	t_data Main::load(const vector<string>& input)
	{
		t_data data;
		for (string s : input)
		{
			data.push_back(t_passphrase());
			while (1)
			{
				size_t pos = s.find_first_of(' ');
				if (pos == string::npos)
				{
					data.back().push_back(s);
					break;
				}

				data.back().push_back(s.substr(0, pos));
				s = s.substr(pos + 1);
			}
		}

		return data;
	}

	int Main::valid_part_one(const t_passphrase& passphrase)
	{
		set<string> ss;
		for (const string& s : passphrase)
		{
			if (ss.find(s) != ss.end())
				return 0;

			ss.insert(s);
		}

		return 1;
	}

	int Main::valid_part_two(const t_passphrase& passphrase)
	{
		typedef map<char, int> t_charcount;
		typedef vector<t_charcount> t_vec;

		t_vec v;
		for (const string& s : passphrase)
		{
			v.push_back(t_charcount());
			for (char c : s)
				v.back()[c]++;
		}

		for (int i = 0; i < (int)v.size(); i++)
			for (int j = i + 1; j < (int)v.size(); j++)
				if (v[i] == v[j])
					return 0;

		return 1;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto data = load(input);

		return accumulate(data.begin(), data.end(), 0,
			[](int sum, const t_passphrase& p) { return sum + valid_part_one(p); });
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto data = load(input);

		return accumulate(data.begin(), data.end(), 0,
			[](int sum, const t_passphrase& p) { return sum + valid_part_two(p); });
	}
}
