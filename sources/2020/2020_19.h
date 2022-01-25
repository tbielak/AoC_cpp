#ifndef __2020_19__
#define __2020_19__

#include "../shared/Solution.h"

namespace Day19_2020
{
	class Rule;
	typedef map<int, Rule> t_rules;
	typedef vector<bool> t_solved;
	typedef vector<string> t_msgs;

	class Rule
	{
	public:
		Rule();
		Rule(const string& input);

		bool try_to_solve(const t_rules& all, const t_solved& solved);

		vector<string> rules;

	private:
		vector<string> split(const string& input);
		vector<string> permute(const vector<vector<string>>& x);
		string remove_spaces(string& s);
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output both_parts(const vector<string>& input);

	private:
		static pair<t_rules, t_msgs> load(const vector<string>& input);
		static void solve(t_rules& rules);
		static bool infinite_matches(const std::string& input, size_t pos, vector<int> r, vector<int> c, const t_rules& rules);
	};
}

#endif
