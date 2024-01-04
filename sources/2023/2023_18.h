#ifndef __2023_18__
#define __2023_18__

#include "../shared/Solution.h"

namespace Day18_2023
{
	class Point
	{
	public:
		Point(int y, int x);
		bool operator < (const Point& rhs) const;

		int y, x;
	};

	using Item = pair<int, int>;		// direction (right = 0, down = 1, left = 2, up = 3), steps
	using Range = pair<int, int>;		// min, max

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static vector<Item> load(const vector<string>& input, bool hex);
		static set<Point> find_points(const vector<Item>& items);
		static vector<Range> get_ranges(const set<int>& indices);
		static pair<vector<Range>, vector<Range>> get_ranges(const set<Point>& points);
		static vector<string> compressed_map(const vector<Item>& items, const vector<Range>& rx, const vector<Range>& ry);
		static vector<vector<int64_t>> get_area(const vector<Range>& rx, const vector<Range>& ry);
		static bool can_go(const vector<string>& m, int y, int x);
		static vector<vector<int>> walk(const vector<string>& input);
		static int64_t count(const vector<string>& cmap, vector<vector<int>>& dmap, const vector<vector<int64_t>>& area);
		static int64_t solve(const vector<string>& input, bool hex);
	};
}

#endif
