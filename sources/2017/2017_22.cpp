#include "2017_22.h"

// explained here:
// https://github.com/tbielak/AoC_cpp/blob/master/doc/2017_22.md

namespace Day22_2017
{
	Position::Position(int x /* = 0 */, int y /* = 0 */)
	:	x(x), y(y)
	{
	}

	bool Position::operator < (const Position& rhs) const
	{
		return (x == rhs.x) ? y < rhs.y : x < rhs.x;
	}

	Grid::Grid(const vector<string>& input)
	{
		int size = (int)input.size();
		int center = size / 2;
		for (int y = 0; y < size; y++)
			for (int x = 0; x < size; x++)
				_map[Position(x - center, y - center)] = (input[y][x] == '#') ? 2 : 0;
	}

	int Grid::burst(int part, int steps)
	{
		static vector<int> acc_x = { 0, 1, 0, -1 };
		static vector<int> acc_y = { -1, 0, 1, 0 };

		Position carrier;
		int facing = 0;	// 0 = up, 1 = right, 2 = down, 3 = left
		int result = 0;
		for (int i = 0; i < steps; i++)
		{
			int infection_status = _map[carrier];
			facing = (facing + infection_status - 1) & 3;
			infection_status = (infection_status + (part ^ 3)) & 3;
			if (infection_status == 2)
				result++;

			_map[carrier] = infection_status;
			carrier.x += acc_x[facing];
			carrier.y += acc_y[facing];
		}

		return result;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return Grid(input).burst(1, 10000);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return Grid(input).burst(2, 10000000);
	}
}
