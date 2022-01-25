#include "2020_19.h"

namespace Day19_2020
{
	Rule::Rule()
	{
	}

	Rule::Rule(const string& input)
	{
		size_t pos = input.find('|');
		if (pos == string::npos)
			rules.push_back(input);
		else
		{
			rules.push_back(input.substr(0, pos - 1));
			rules.push_back(input.substr(pos + 2));
		}
	}

	bool Rule::try_to_solve(const t_rules& all, const t_solved& solved)
	{
		vector<string> dst;
		for (size_t r = 0; r < rules.size(); r++)
		{
			auto sp = split(rules[r]);
			vector<vector<string>> x(sp.size());
			for (size_t i = 0; i < sp.size(); i++)
			{
				if (isdigit(sp[i][0]) && solved[stoi(sp[i])])
				{
					const auto& r = all.find(stoi(sp[i]))->second.rules;
					for (const auto& v : r)
						x[i].push_back(v);
				}
				else
					x[i].push_back(sp[i]);
			}

			vector<string> y = permute(x);
			for (size_t i = 0; i < y.size(); i++)
				dst.push_back(y[i]);
		}

		rules = dst;

		bool done = true;
		for (const auto& r : rules)
			for (auto c : r)
				if (isdigit(c))
					done = false;

		if (!done)
			return false;

		for (auto& r : rules)
			r = remove_spaces(r);

		return true;
	}

	vector<string> Rule::split(const string& input)
	{
		vector<string> ouptut;
		stringstream ss(input);
		string s;
		while (getline(ss, s, ' '))
			ouptut.push_back(s);

		return ouptut;
	}

	vector<string> Rule::permute(const vector<vector<string>>& x)
	{
		vector<string> y;
		for (size_t j = 0; j < x[0].size(); j++)
			y.push_back(x[0][j]);

		for (size_t i = 1; i < x.size(); i++)
		{
			vector<string> t;
			for (size_t k = 0; k < y.size(); k++)
				for (size_t j = 0; j < x[i].size(); j++)
					t.push_back(y[k] + " " + x[i][j]);

			y = t;
		}

		return y;
	}

	string Rule::remove_spaces(string& s)
	{
		string w;
		for (auto c : s)
			if (c != ' ')
				w += c;

		return w;
	}

	pair<t_rules, t_msgs> Main::load(const vector<string>& input)
	{
		t_rules rules;
		size_t idx = 0;
		for (; idx < input.size(); idx++)
		{
			const auto& line = input[idx];
			if (line == "")
				break;

			size_t pos = line.find(':');
			int number = stoi(line.substr(0, pos));
			rules[number] = Rule(line.substr(pos + 2));
		}

		idx++;
		t_msgs msgs;
		for (; idx < input.size(); idx++)
			msgs.push_back(input[idx]);

		return make_pair(rules, msgs);
	}

	void Main::solve(t_rules& rules)
	{
		size_t solved_count = 0;
		t_solved solved(rules.size());

		for (auto& r : rules)
		{
			for (auto& s : r.second.rules)
				if (s == "\"a\"" || s == "\"b\"")
				{
					s = s.substr(1, 1);
					solved[r.first] = true;
					solved_count++;
				}
		}

		while (solved_count != rules.size())
		{
			for (auto& r : rules)
			{
				if (solved[r.first])
					continue;

				if (r.second.try_to_solve(rules, solved))
				{
					solved[r.first] = true;
					solved_count++;
				}
			}
		}
	}

	bool Main::infinite_matches(const std::string& input, size_t pos, vector<int> r, vector<int> c, const t_rules& rules)
	{
		if (c[1] >= c[0] && c[1] != 0)
			return false;

		for (int i = 0; i < 2; i++)
		{
			if (i == 0 && c[1] != 0)
				continue;

			const auto& rx = rules.find(r[i])->second.rules;
			for (const auto& rule : rx)
			{
				size_t size = rule.size();
				if (!input.compare(pos, size, rule))
				{
					if (pos + size == input.size())  // only c2
						return (i == 0) ? false : c[1] + 1 < c[0];

					c[0] += (i == 0);
					c[1] += (i == 1);
					if (infinite_matches(input, pos + size, r, c, rules))
						return true;
				}
			}
		}

		return false;
	}

	AoC::Output Main::both_parts(const vector<string>& input)
	{
		// load and solve rules
		auto [rules, msgs] = load(input);
		solve(rules);

		// part one
		set<string> accepted;
		const auto& zero_rules = rules.find(0)->second.rules;
		for (const auto& x : zero_rules)
			accepted.insert(x);

		int count_p1 = 0;
		for (const auto& m : msgs)
			if (accepted.find(m) != accepted.end())
				count_p1++;

		// part two - assuming:
		// 0: x y
		// x: r0		(one element for x)
		// y: r0 r1		(two elements for y, first elements of x and y match)

		vector<int> r = { 42, 31 };		// { r0, r1 }
		vector<int> c = { 0, 0 };		// counting substrings recursively

		int count_p2 = 0;
		for (const auto& s : msgs)
			if (infinite_matches(s, 0, r, c, rules))
				count_p2++;

		return make_pair(count_p1, count_p2);
	}
}
