#ifndef __2024_12__
#define __2024_12__

#include "../shared/Solution.h"

namespace Day12_2024
{
	class Farm
	{
	public:
		Farm(const vector<string>& input);
		int price(bool with_discount);

	private:
		int _height;
		int _width;
		const vector<string>& _input;
		vector<vector<int>> _fence;

		vector<vector<int>> fence_reduced();
		int bit_count(int v) const;
		int price(const vector<vector<int>>& fence_to_be_valued);
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);
	};
}

#endif
