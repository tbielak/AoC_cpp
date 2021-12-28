#include "2021_22.h"

namespace Day22_2021
{
	Cuboid::Cuboid(int x1, int x2, int y1, int y2, int z1, int z2)
	:	x1(x1), x2(x2), y1(y1), y2(y2), z1(z1), z2(z2)
	{
	}

	// Solution => simple idea:
	// 1. Partition each axis for the ranges defined by all points from input
	// 2. Treat each range as discrete index in large grid, with one-byte on/off flags
	//
	// Note: It is not an elegant solution. Requires (c*2)*(c*2)*(c*2) bytes of RAM
	// (c is the number of input cubes = 420) + a lot of time to iterate it (1-2 seconds).

	template<typename Functor>
	int64_t solve(const t_cubes& cubes, Functor include)
	{
		// gather points on axes
		vector<int> axis_x, axis_y, axis_z;
		for (const auto& v : cubes)
		{
			const auto& c = v.first;
			if (include(c))
			{
				// key issue here: add 1 to bigger coordinate value
				axis_x.push_back(c.x1);
				axis_x.push_back(c.x2 + 1);
				axis_y.push_back(c.y1);
				axis_y.push_back(c.y2 + 1);
				axis_z.push_back(c.z1);
				axis_z.push_back(c.z2 + 1);
			}
		}

		// sort them
		// expect duplicates on this list -> there are cubes sharing the same coordinates
		sort(axis_x.begin(), axis_x.end());
		sort(axis_y.begin(), axis_y.end());
		sort(axis_z.begin(), axis_z.end());

		// create big grid, set each one-byte cell to 0 (off) by default
		vector<vector<vector<char>>> grid(axis_x.size(), vector<vector<char>>(axis_y.size(), vector<char>(axis_z.size())));

		// process all cubes
		for (const auto& v : cubes)
		{
			const auto& c = v.first;
			if (include(c))
			{
				// find (min, max) indices on each axis_* which are covered by input cube
				// key issue here (once again): add 1 to bigger coordinate value
				// performance note: STL's lower_bound() helps a lot in indices quick search
				int x_min = int(lower_bound(axis_x.begin(), axis_x.end(), c.x1) - axis_x.begin());
				int x_max = int(lower_bound(axis_x.begin(), axis_x.end(), c.x2 + 1) - axis_x.begin());
				int y_min = int(lower_bound(axis_y.begin(), axis_y.end(), c.y1) - axis_y.begin());
				int y_max = int(lower_bound(axis_y.begin(), axis_y.end(), c.y2 + 1) - axis_y.begin());
				int z_min = int(lower_bound(axis_z.begin(), axis_z.end(), c.z1) - axis_z.begin());
				int z_max = int(lower_bound(axis_z.begin(), axis_z.end(), c.z2 + 1) - axis_z.begin());

				// turn on or off
				for (int x = x_min; x < x_max; x++)
					for (int y = y_min; y < y_max; y++)
						for (int z = z_min; z < z_max; z++)
							grid[x][y][z] = v.second;
			}
		}

		// calculate the volume of the solid (count only cuboids turned on)
		int64_t volume = 0;
		for (int x = 0; x < (int)axis_x.size() - 1; x++)
			for (int y = 0; y < (int)axis_y.size() - 1; y++)
				for (int z = 0; z < (int)axis_z.size() - 1; z++)
					if (grid[x][y][z])
						volume += (int64_t)(axis_x[x + 1] - axis_x[x]) * (axis_y[y + 1] - axis_y[y]) * (axis_z[z + 1] - axis_z[z]);

		return volume;
	}

	int64_t part_one(const t_cubes& cubes)
	{
		return solve(cubes, [](const auto& c) -> bool { return c.x1 >= -50 && c.x2 <= 50 && c.y1 >= -50 && c.y2 <= 50 && c.z1 >= -50 && c.z2 <= 50; });
	}

	int64_t part_two(const t_cubes& cubes)
	{
		return solve(cubes, [](const auto& c) -> bool { (void)(c); return true; });
	}

	t_output main(const t_input& input)
	{
		t_cubes cubes;
		for (const auto& s : input)
		{
			smatch matches;
			regex regex("(on|off) x=([-|0-9]*)..([-|0-9]*),y=([-|0-9]*)..([-|0-9]*),z=([-|0-9]*)..([-|0-9]*)");
			regex_search(s, matches, regex);
			cubes.push_back(make_pair(Cuboid(stoi(matches[2]), stoi(matches[3]),
				stoi(matches[4]), stoi(matches[5]), stoi(matches[6]), stoi(matches[7])), matches[1] == "on" ? 1 : 0));
		}

		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(cubes);
		auto p2 = part_two(cubes);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
