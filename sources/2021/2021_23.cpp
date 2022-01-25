#include "2021_23.h"

namespace Day23_2021
{
	// check if place in diagram is hallway
	bool Main::is_hallway(const t_diagram& diagram, int place)
	{
		return diagram[place].size() == 1;
	}

	// get target place for selected amphipod
	int Main::target(char amphipod)
	{
		return (int(amphipod - '@') * 2);
	}

	// get cost of selected amphipod move
	int Main::cost(char amphipod)
	{
		return (int)pow(10, int(amphipod - 'A'));
	}

	// check if there is a free way to move amphipod from src to dst place
	// assumption: room has empty place, checking hallway only
	bool Main::can_reach(const t_diagram& diagram, int src, int dst)
	{
		int from = (src < dst) ? src + 1 : dst;
		int to = (src < dst) ? dst : src - 1;

		for (int i = from; i <= to; i++)
			if (is_hallway(diagram, i) && diagram[i] != ".")
				return false;

		return true;
	}

	// check if in selected room there are only empty places or taken by
	// amphipods of specified target type (in such case we don't want to
	// move anything from this room)
	bool Main::target_only(const string& room, char target)
	{
		int count = 0;
		for (auto c : room)
			if (c == '.' || c == target)
				count++;

		return (int)room.size() == count;
	}

	// finding possible destinations from src place
	// assumption: there is amphipod at src place (place cannot be empty)
	vector<int> Main::find_destinations(const t_diagram& diagram, int src)
	{
		// vector of possible destinations found
		vector<int> result;

		if (is_hallway(diagram, src))
		{
			// moving amphipod from hallway to room - one amphipod at place = 0
			char amphipod = diagram[src][0];

			// try to move it directly to the destination place
			int dst = target(amphipod);

			// if can reach it
			// and the room is empty or occupied only by the same type of amphipods
			// this is the only correct destination (if not -> no destinations)
			if (can_reach(diagram, src, dst) && target_only(diagram[dst], amphipod))
				result.push_back(dst);

			return result;
		}

		// looking for amphipod in room
		const string& current = diagram[src];
		char amphipod = current[current.find_first_not_of('.')];

		// if in right place and the room is empty or occupied only by
		// the same type of amphipods -> do not move it
		if (src == target(amphipod) && target_only(diagram[src], amphipod))
			return result;

		// in any other case - check all destinations
		for (int dst = 0; dst < (int)diagram.size(); dst++)
		{
			if (dst == src)
				continue;

			// moving to hallway only if amphipod can reach it
			// and there are no amphipods of different type there
			if (is_hallway(diagram, dst) &&
				can_reach(diagram, src, dst) && target_only(diagram[dst], amphipod))
				result.push_back(dst);
		}

		return result;
	}

	int Main::do_move(const t_diagram& src_diagram, t_diagram& dst_diagram, int src, int dst)
	{
		// moving out (see i + 1 distance in case of moving out from room)
		int i = (int)src_diagram[src].find_first_not_of('.');
		char amphipod = src_diagram[src][i];
		dst_diagram[src][i] = '.';
		int distance = is_hallway(src_diagram, src) ? 0 : i + 1;

		// moving in (first add distance on hallway, then i + 1 when moving into room)
		distance += (src > dst) ? (src - dst) : (dst - src);
		if (is_hallway(src_diagram, dst))
			dst_diagram[dst] = amphipod;
		else
		{
			int i = (int)src_diagram[dst].find_last_of('.');
			dst_diagram[dst][i] = amphipod;
			distance += i + 1;
		}

		// calculate cost of move
		return distance * cost(amphipod);
	}

	int Main::solve(const t_diagram& input, const t_diagram& target)
	{
		// known costs cache, cost is 0 for input diagram
		t_costs_cache cache;
		cache[input] = 0;

		// put input diagram to queue of diagrams need to be solved
		t_queue queue;
		queue.push(input);

		// repeat until queue becomes empty
		while (!queue.empty())
		{
			// get diagram to solve from queue
			t_diagram src_diagram = queue.front();
			queue.pop();

			// go through all positions
			for (int src = 0; src < (int)src_diagram.size(); src++)
			{
				// if position (hallway or room) is empty - skip it
				if (src_diagram[src].find_first_not_of('.') == string::npos)
					continue;

				// find all possible moves from src, go through them
				vector<int> dests = find_destinations(src_diagram, src);
				for (auto dest : dests)
				{
					// make move and calculate cost of move
					t_diagram dst_diagram = src_diagram;
					int new_cost = cache[src_diagram] + do_move(src_diagram, dst_diagram, src, dest);

					// if further cost is known - use it, if not - assume it is infinity
					t_costs_cache::const_iterator it = cache.find(dst_diagram);
					int known_cost = (it == cache.end()) ? INT_MAX : it->second;

					// found lower cost?
					if (new_cost < known_cost)
					{
						// remember it
						cache[dst_diagram] = new_cost;

						// and explore further
						queue.push(dst_diagram);
					}
				}
			}
		}

		// cost for target configuration
		return cache[target];
	}
	
	// load diagram from input
	t_diagram Main::load(const vector<string>& input)
	{
		// eleven places (hallway + rooms)
		t_diagram diagram(11);

		// load input into rooms
		for (int x = 0; x < 4; x++)
			for (int y = 2; y <= 3; y++)
				diagram[x * 2 + 2].push_back(input[y][x * 2 + 3]);

		// create empty hallway
		for (auto& s : diagram)
			if (s.size() == 0)
				s = ".";

		return diagram;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		// load diagram from input
		t_diagram diagram = load(input);

		// request target configuration and solve
		t_diagram target = { ".", ".", "AA", ".", "BB", ".", "CC", ".", "DD", ".", "." };
		return solve(diagram, target);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		// load diagram from input, insert extra part to the diagram
		t_diagram diagram = load(input);
		diagram[2].insert(1, "DD");
		diagram[4].insert(1, "CB");
		diagram[6].insert(1, "BA");
		diagram[8].insert(1, "AC");

		// request target configuration and solve
		t_diagram target = { ".", ".", "AAAA", ".", "BBBB", ".", "CCCC", ".", "DDDD", ".", "." };
		return solve(diagram, target);
	}
}
