#ifndef __2024_13__
#define __2024_13__

#include "../shared/Solution.h"

namespace Day13_2024
{
	class Point
	{
	public:
		Point();
		Point(const string& input, const string& rs);
		
		int64_t x, y;
	};

	class Machine
	{
	public:
		Machine(const string& a, const string& b, const string& p, int64_t add);
		int64_t play() const;

	private:
		Point _a, _b, _prize;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static vector<Machine> load(const vector<string>& input, int64_t add);
		static int64_t solve(const vector<string>& input, int64_t add = 0);
	};
}

#endif
