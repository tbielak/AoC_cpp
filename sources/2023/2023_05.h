#ifndef __2023_05__
#define __2023_05__

#include "../shared/Solution.h"

namespace Day05_2023
{
	class Range
	{
	public:
		Range(int64_t from = -1, int64_t to = -1);

		bool empty() const;
		bool operator== (const Range& rhs) const;
		Range intersection(const Range& rhs) const;

		int64_t from, to;
	};

	class Item
	{
	public:
		Item(const Range& range, int64_t shift);

		Range range;
		int64_t shift;
	};

	using Map = vector<Item>;

	struct Data
	{
		vector<Range> seeds;
		vector<Map> maps;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static vector<int64_t> load(const string& s);
		static Data load(const vector<string>& input, bool ranges);
		static int64_t find_minimum(const vector<Range>& ranges);
		static int64_t solve(Data data);
	};
}

#endif
