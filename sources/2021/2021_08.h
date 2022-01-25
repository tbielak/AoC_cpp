#ifndef __2021_08__
#define __2021_08__

#include "../shared/Solution.h"

namespace Day08_2021
{
	class Entry
	{
	public:
		Entry(string s);

		int count_digits_1478() const;
		int find_number() const;

	private:
		vector<string> _digits;
		string _one;
		string _four;
		
		static const vector<int> _segment_count;

		int get(const string& digit) const;
		int count(const string& src, const string& target) const;
		string read_input(string& input);
	};

	typedef vector<Entry> t_entries;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		t_entries load(const vector <string>& input);
	};
}

#endif
