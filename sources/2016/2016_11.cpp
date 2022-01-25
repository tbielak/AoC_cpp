#include "2016_11.h"

namespace Day11_2016
{
	// load input
	t_floors Main::load(const vector<string>& input)
	{
		// collect all element names
		// they are not important during solving, needed here to match name with bit index
		typedef map<string, int> t_map;
		t_map names;

		// empty floors
		t_floors floors(input.size());

		// scan floors 1..n-1 (they are indexed 0..n-2)
		for (int i = 0; i < (int)input.size() - 1; i++)
		{
			string s = input[i];
			size_t pos;
			while ((pos = s.find("a ")) != string::npos)
			{
				s = s.substr(pos + 2);
				pos = min(s.find_first_of('-'), s.find_first_of(' '));

				// find index of element in names map
				int idx = 0;
				string name = s.substr(0, pos);
				t_map::const_iterator it = names.find(name);
				if (it != names.end())
					idx = it->second;
				else
				{
					idx = (int)names.size();
					names[name] = idx;
				}

				// set appropriate bit, see comments in .h file for explanation
				// (offset == 0 for microchip, offset == 8 for generator)
				int offset = s[pos] == '-' ? 0 : 8;
				floors[i] |= uint16_t(1 << (offset + idx));
			}
		}

		return floors;
	}

	// is floor configuration safe?
	bool Main::safe(uint16_t& cfg)
	{
		// generator and microchip parts
		uint8_t g = uint8_t(cfg >> 8);
		uint8_t m = uint8_t(cfg & 0xff);

		// floor is safe when there are only generators or only microchips on the floor
		if (m == 0 || g == 0)
			return true;

		// floor is safe when there are no microchips not paired with generators
		return (m & g) == m;
	}

	// move elements from src to dst
	void Main::do_move(uint16_t& src, uint16_t& dst, uint16_t move)
	{
		src &= (move ^ 0xffff);
		dst |= move;
	}

	// is the move valid?
	// do the move and check floor safety
	bool Main::is_valid(uint16_t src, uint16_t dst, uint16_t move)
	{
		do_move(src, dst, move);
		return safe(src) && safe(dst);
	}

	// find all valid moves from src do dst floor
	vector<uint16_t> Main::find_moves(uint16_t src, uint16_t dst)
	{
		// valid moves
		vector<uint16_t> moves;

		// find items
		vector<int> items;
		for (uint16_t i = 0; i < 16; i++)
		{
			uint16_t mask = uint16_t(1 << i);
			if (src & mask)
			{
				items.push_back(i);

				// try to move one item
				if (is_valid(src, dst, mask))
					moves.push_back(mask);
			}
		}
		
		// try to move two items
		for (uint16_t i = 0; i < (uint16_t)items.size(); i++)
			for (uint16_t j = (uint16_t)(i + 1); j < (uint16_t)items.size(); j++)
			{
				uint16_t mask = uint16_t((1 << items[i]) + (1 << items[j]));
				if (is_valid(src, dst, mask))
					moves.push_back(mask);
			}

		return moves;
	}

	int Main::solve(const t_floors& floors)
	{
		// what is top floor target configuration?
		int top = (int)floors.size() - 1;
		int target_state = 0;
		for (int i = 0; i < top; i++)
			target_state |= floors[i];

		// initial state from input with zero steps
		t_state initial_state = make_pair(floors, 0);

		// store already known (initial) state
		t_known_states known;
		known.insert(initial_state);

		// queue of configurations to explore
		t_queue queue;

		// put initial state with elevator on 1st floor (0-based)
		queue.push(make_pair(initial_state, 0));

		// explore all unknown configurations
		while (!queue.empty())
		{
			// get config from queue
			const auto [state, step] = queue.front();
			const auto [floors, elevator] = state;
			queue.pop();

			// is it target state? -> finish
			if (floors[top] == target_state)
				return step;

			// elevator movement
			for (int e = -1; e <= 1; e++)
			{
				if (e == 0)
					continue;

				int elevator_target = elevator + e;
				if (elevator_target < 0 || elevator_target > top)
					continue;

				// find moves
				vector<uint16_t> moves = find_moves(floors[elevator], floors[elevator_target]);
				for (auto m : moves)
				{
					// do move
					t_floors new_floors = floors;
					do_move(new_floors[elevator], new_floors[elevator_target], m);

					// create new state
					t_state new_state = make_pair(new_floors, elevator_target);

					// if not known: store it and explore it
					t_known_states::const_iterator it = known.find(new_state);
					if (it == known.end())
					{
						queue.push(make_pair(new_state, step + 1));
						known.insert(new_state);
					}
				}
			}
		}

		return -1;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		// load from input and solve
		return solve(load(input));
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		// load from input...
		t_floors floors = load(input);

		// ...and add two elements on 1st floor (0-based):
		// just set two highest bits of microchip and generator parts
		floors[0] |= 0xc0c0;

		// solve
		return solve(floors);
	}
}
