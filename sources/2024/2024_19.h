#ifndef __2024_19__
#define __2024_19__

#include "../shared/Solution.h"

namespace Day19_2024
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output both_parts(const vector<string>& input);

	private:
		static pair <vector<string>, vector<string>> load(const vector<string>& input);
		static int64_t count(const vector<string>& patterns, const string& design);
		static vector<int64_t> count(const vector<string>& patterns, const vector<string>& designs);
	};
}

#endif
