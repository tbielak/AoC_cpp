#ifndef __2023_19__
#define __2023_19__

#include "../shared/Solution.h"

namespace Day19_2023
{
	class Workflow
	{
	public:
		Workflow(string s = "");

		vector<string> rules;
	};

	using Part = vector<int>;
	using Range = pair<int, int>;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static pair<map<string, Workflow>, vector<Part>> load(const vector<string>& input);
		static int process_part(const Part& part, const map<string, Workflow>& workflows);
		static int64_t solve(const map<string, Workflow>& workflows, string name, vector<Range> ranges);
	};
}

#endif
