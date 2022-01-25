#ifndef __2021_18_Strings__
#define __2021_18_Strings__

#include "../shared/Solution.h"

namespace Day18_2021_Strings
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static int read_number(const string& s, size_t& pos);
		static size_t number_on_left(const string& s, size_t pos);
		static size_t number_on_right(const string& s, size_t pos);
		static size_t can_explode(const string& s);
		static bool explode(string& s);
		static bool split(string& s);
		static void reduce(string& s);
		static string add(const string& a, const string& b);
		static int magnitude(string s);
	};
}

#endif
