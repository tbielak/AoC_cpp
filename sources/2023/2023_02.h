#ifndef __2023_02__
#define __2023_02__

#include "../shared/Solution.h"

namespace Day02_2023
{
	class Cube
	{
	public:
		Cube(const string& s);
		int find(const string& s, const string& name);

		int r, g, b;
	};

	using Games = map<int, vector<Cube>>;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static vector<Cube> load(string s);
		static Games load(const vector<string>& input);
	};
}

#endif
