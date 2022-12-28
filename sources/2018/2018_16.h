#ifndef __2018_16__
#define __2018_16__

#include "../shared/Solution.h"

namespace Day16_2018
{
	class Sample
	{
	public:
		Sample(const string& before_str, const string& code_str, const string& after_str);
		static vector<int> parse(const string& input);

		vector<int> before;
		vector<int> code;
		vector<int> after;

	private:
		string clean(const string& input) const;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static pair<vector<Sample>, vector<vector<int>>> load(const vector<string>& input);
		static void execute(int op, vector<int>& regs, const vector<int>& code);
	};
}

#endif
