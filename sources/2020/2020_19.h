#ifndef __2020_19__
#define __2020_19__

#include "../shared/input_output.h"

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

	t_output main(const t_input& input);
}

#endif
