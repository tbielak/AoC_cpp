#include "2018_13.h"

namespace Day13_2018
{
	Cart::Cart(int id, int x, int y, int facing)
	:	id(id), x(x), y(y), facing(facing), turn_phase(-1), crashed(false)
	{
	}

	bool Cart::operator < (const Cart& rhs) const
	{
		return (x == rhs.x) ? y < rhs.y : x < rhs.x;
	}

	void Cart::move()
	{
		static vector<int> acc_x = { 0, 1, 0, -1 };
		static vector<int> acc_y = { -1, 0, 1, 0 };

		x += acc_x[facing];
		y += acc_y[facing];
	}

	void Cart::update(char c)
	{
		if (c == '/')
			facing ^= 1;

		if (c == '\\')
			facing = 3 - facing;

		if (c == '+')
		{
			facing = (facing + turn_phase) & 3;
			turn_phase++;
			if (turn_phase == 2)
				turn_phase = -1;
		}
	}

	CartMadness::CartMadness(const vector<string>& input)
	:	_map(input)
	{
		int id = 0;
		const string carts = "^>v<";
		const string under = "|-|-";
		for (size_t y = 0; y < input.size(); y++)
			for (size_t x = 0; x < input[0].size(); x++)
			{
				size_t pos = carts.find_first_of(_map[y][x]);
				if (pos != string::npos)
				{
					_carts.push_back(Cart(id++, int(x), int(y), int(pos)));
					_map[y][x] = under[pos];
				}
			}
	}

	string CartMadness::run(bool up_to_first_crash)
	{
		int left = (int)_carts.size();
		while (1)
		{
			auto [x, y] = tick(up_to_first_crash, left);
			if (x > -1)
				return to_string(x) + "," + to_string(y);
		}

		return string("unreachable");
	}

	bool CartMadness::collision(const Cart& current, const Cart& other) const
	{
		return !other.crashed && current.id != other.id && current.x == other.x && current.y == other.y;
	}

	pair<int, int> CartMadness::tick(bool up_to_first_crash, int& carts_left)
	{
		sort(_carts.begin(), _carts.end());
		for (auto& current : _carts)
		{
			if (current.crashed)
				continue;

			current.move();

			for (auto& other : _carts)
				if (collision(current, other))
				{
					if (up_to_first_crash)
						return make_pair(current.x, current.y);

					current.crashed = true;
					other.crashed = true;
					carts_left -= 2;
				}

			current.update(_map[current.y][current.x]);
		}

		if (carts_left == 1)
			for (auto& last : _carts)
				if (!last.crashed)
					return make_pair(last.x, last.y);

		return make_pair(-1, -1);
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return CartMadness(input).run(true);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return CartMadness(input).run(false);
	}
}
