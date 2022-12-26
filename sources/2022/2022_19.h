#ifndef __2022_19__
#define __2022_19__

#include "../shared/Solution.h"

namespace Day19_2022
{
	class Blueprint
	{
	public:
		Blueprint(int v1, int v2, int v3, int v4, int v5, int v6);

		int ore_robot_cost_in_ore;
		int clay_robot_cost_in_ore;
		int obsidian_robot_cost_in_ore;
		int obsidian_robot_cost_in_clay;
		int geode_robot_cost_in_ore;
		int geode_robot_cost_in_clay;
		int ore_max_cost;
	};

	class State
	{
	public:
		State(int16_t time_left);
		State(int16_t ore, int16_t clay, int16_t obsidian, int16_t geode,
			int16_t ore_robots_count, int16_t clay_robots_count, int16_t obsidian_robots_count, int16_t geode_robots_count, int16_t time_left);

		tuple<int64_t, int64_t, int16_t> key() const;

		int16_t ore, clay, obsidian, geode, ore_robots_count, clay_robots_count, obsidian_robots_count, geode_robots_count, time_left;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static map<int, Blueprint> load(const vector<string>& input);
		static int harvest(const Blueprint& b, int16_t time_left);
	};
}

#endif
