#ifndef __2018_13__
#define __2018_13__

#include "../shared/Solution.h"

namespace Day13_2018
{
	class Cart
	{
	public:
		Cart(int id, int x, int y, int facing);

		bool operator < (const Cart& rhs) const;

		void move();
		void update(char c);

		int id;
		int x, y;
		int facing;
		int turn_phase;
		bool crashed;
	};

	typedef vector<Cart> t_carts;

	class CartMadness
	{
	public:
		CartMadness(const vector<string>& input);

		string run(bool up_to_first_crash);

	private:
		vector<string> _map;
		t_carts _carts;

		bool collision(const Cart& current, const Cart& other) const;
		pair<int, int> tick(bool up_to_first_crash, int& carts_left);
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);
	};
}

#endif
