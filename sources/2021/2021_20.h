#ifndef __2021_20__
#define __2021_20__

#include "../shared/Solution.h"

namespace Day20_2021
{
	typedef vector<string> t_image;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static int is_hash(char c);
		static int get_idx(const t_image& image, int x, int y, int width, int height, char empty);
		static t_image enhance(const string& algorithm, const t_image& src, char& empty);
		static int solve(int steps, const vector<string>& input);
	};
}

#endif
