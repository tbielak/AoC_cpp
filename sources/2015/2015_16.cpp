#include "2015_16.h"

namespace Day16_2015
{
	int part_one(const t_vec2int& input, const t_vecint& detected)
	{
		for (size_t i = 0; i < input.size(); i++)
		{
			int c = 0;
			int m = 0;
			for (size_t j = 0; j < detected.size(); j++)
				if (input[i][j] > 0)
				{
					c++;
					if (input[i][j] == detected[j])
						m++;
				}

			if (c == m && m > 0)
				return int(i) + 1;
		}

		return -1;
	}

	bool equ(int lhs, int rhs) { return lhs == rhs; }
	bool grt(int lhs, int rhs) { return lhs > rhs; }
	bool lst(int lhs, int rhs) { return lhs < rhs; }
	typedef bool (*compare_function)(int, int);

	int part_two(const t_vec2int& input, const t_vecint& detected)
	{
		const vector<compare_function> comp = { &equ, &grt, &equ, &lst, &equ, &equ, &lst, &grt, &equ, &equ };

		int maxm = -1;
		int maxmv = 0;
		for (size_t i = 0; i < input.size(); i++)
		{
			int c = 0;
			int m = 0;
			for (size_t j = 0; j < detected.size(); j++)
				if (input[i][j] > 0)
				{
					c++;
					if (comp[j](input[i][j], detected[j]))
						m++;
				}

			if (c == m && m > 0 and m > maxm)
			{
				maxm = m;
				maxmv = int(i) + 1;
			}
		}

		return maxmv;
	}

	t_output main(const t_input& input)
	{
		const map<string, size_t> compounds = { { "children", 0 }, { "cats", 1 }, { "samoyeds", 2 }, { "pomeranians", 3 },
			{ "akitas", 4 }, { "vizslas", 5 }, { "goldfish", 6 }, { "trees", 7 }, { "cars", 8 }, { "perfumes", 9 } };

		const t_vecint detected = { 3, 7, 2, 3, 0, 0, 5, 3, 2, 1 };

		t_vec2int vinput;
		regex regex("Sue ([0-9])*: ([a-z]*): ([0-9])*, ([a-z]*): ([0-9])*, ([a-z]*): ([0-9])*");
		smatch matches;
		for (const auto& line : input)
		{
			regex_search(line, matches, regex);
			t_vecint v(compounds.size());
			for (int i = 0; i < 3; i++)
				v[compounds.find(matches[i * 2 + 2].str())->second] = stoi(matches[i * 2 + 3].str());

			vinput.push_back(move(v));
		}

		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(vinput, detected);
		auto p2 = part_two(vinput, detected);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
