#include "2022_19.h"

namespace Day19_2022
{
	Blueprint::Blueprint(int v1, int v2, int v3, int v4, int v5, int v6)
	{
		ore_robot_cost_in_ore = v1;
		clay_robot_cost_in_ore = v2;
		obsidian_robot_cost_in_ore = v3;
		obsidian_robot_cost_in_clay = v4;
		geode_robot_cost_in_ore = v5;
		geode_robot_cost_in_clay = v6;
		ore_max_cost = max(v1, max(v2, max(v3, v5)));
	}

	State::State(int16_t time_left)
	:	ore(0), clay(0), obsidian(0), geode(0),
		ore_robots_count(1), clay_robots_count(0), obsidian_robots_count(0), geode_robots_count(0), time_left(time_left)
	{
	}

	State::State(int16_t ore, int16_t clay, int16_t obsidian, int16_t geode,
		int16_t ore_robots_count, int16_t clay_robots_count, int16_t obsidian_robots_count, int16_t geode_robots_count, int16_t time_left)
	:	ore(ore), clay(clay), obsidian(obsidian), geode(geode),
		ore_robots_count(ore_robots_count), clay_robots_count(clay_robots_count),
		obsidian_robots_count(obsidian_robots_count), geode_robots_count(geode_robots_count), time_left(time_left)
	{
	}

	tuple<int64_t, int64_t, int16_t> State::key() const
	{
		return make_tuple(
			(int64_t(ore) << 48) | (int64_t(clay) << 32) | (int64_t(obsidian) << 16) | int64_t(geode),
			(int64_t(ore_robots_count) << 48) | (int64_t(clay_robots_count) << 32) | (int64_t(obsidian_robots_count) << 16) | int64_t(geode_robots_count),
			time_left);
	}

	map<int, Blueprint> Main::load(const vector<string>& input)
	{
		smatch matches;
		regex regex("Blueprint ([0-9]+): Each ore robot costs ([0-9]+) ore. "
			"Each clay robot costs ([0-9]+) ore. "
			"Each obsidian robot costs ([0-9]+) ore and ([0-9]+) clay. "
			"Each geode robot costs ([0-9]+) ore and ([0-9]+) obsidian.");

		map<int, Blueprint> robots;
		for (const auto& line : input)
		{
			regex_search(line, matches, regex);
			robots.insert(map<int, Blueprint>::value_type(stoi(matches[1].str()), Blueprint(
				stoi(matches[2].str()), stoi(matches[3].str()), stoi(matches[4].str()),
				stoi(matches[5].str()), stoi(matches[6].str()), stoi(matches[7].str()))));
		}

		return robots;
	}

	int Main::harvest(const Blueprint& b, int16_t time_left)
	{
		int max_geodes = 0;
		set<tuple<int64_t, int64_t, int16_t>> visited;
		queue<State> queue;
		queue.push(State(time_left));

		while (queue.size() > 0)
		{
			State s = queue.front();
			queue.pop();

			max_geodes = max(max_geodes, int(s.geode));
			if (s.time_left == 0)
				continue;

			// limit to maximum amounts possible to harvest in time_left
			s.ore = int16_t(min(int(s.ore), s.time_left * b.ore_max_cost - s.ore_robots_count * (s.time_left - 1)));
			s.clay = int16_t(min(int(s.clay), s.time_left * b.obsidian_robot_cost_in_clay - s.clay_robots_count * (s.time_left - 1)));
			s.obsidian = int16_t(min(int(s.obsidian), s.time_left * b.geode_robot_cost_in_clay - s.obsidian_robots_count * (s.time_left - 1)));

			auto key = s.key();
			if (visited.find(key) != visited.end())
				continue;

			visited.insert(key);

			// harvest without buying
			queue.push(State(
				int16_t(s.ore + s.ore_robots_count),
				int16_t(s.clay + s.clay_robots_count),
				int16_t(s.obsidian + s.obsidian_robots_count),
				int16_t(s.geode + s.geode_robots_count),
				s.ore_robots_count,
				s.clay_robots_count,
				s.obsidian_robots_count,
				s.geode_robots_count,
				int16_t(s.time_left - 1)));

			// + try to buy a robot
			if (s.ore >= b.ore_robot_cost_in_ore)
				queue.push(State(
					int16_t(s.ore - b.ore_robot_cost_in_ore + s.ore_robots_count),
					int16_t(s.clay + s.clay_robots_count),
					int16_t(s.obsidian + s.obsidian_robots_count),
					int16_t(s.geode + s.geode_robots_count),
					int16_t(s.ore_robots_count + 1),
					s.clay_robots_count,
					s.obsidian_robots_count,
					s.geode_robots_count,
					int16_t(s.time_left - 1)));

			if (s.ore >= b.clay_robot_cost_in_ore)
				queue.push(State(
					int16_t(s.ore - b.clay_robot_cost_in_ore + s.ore_robots_count),
					int16_t(s.clay + s.clay_robots_count),
					int16_t(s.obsidian + s.obsidian_robots_count),
					int16_t(s.geode + s.geode_robots_count),
					s.ore_robots_count,
					int16_t(s.clay_robots_count + 1),
					s.obsidian_robots_count,
					s.geode_robots_count,
					int16_t(s.time_left - 1)));

			if (s.ore >= b.obsidian_robot_cost_in_ore && s.clay >= b.obsidian_robot_cost_in_clay)
				queue.push(State(
					int16_t(s.ore - b.obsidian_robot_cost_in_ore + s.ore_robots_count),
					int16_t(s.clay - b.obsidian_robot_cost_in_clay + s.clay_robots_count),
					int16_t(s.obsidian + s.obsidian_robots_count),
					int16_t(s.geode + s.geode_robots_count),
					s.ore_robots_count,
					s.clay_robots_count,
					int16_t(s.obsidian_robots_count + 1),
					s.geode_robots_count,
					int16_t(s.time_left - 1)));

			if (s.ore >= b.geode_robot_cost_in_ore && s.obsidian >= b.geode_robot_cost_in_clay)
				queue.push(State(
					int16_t(s.ore - b.geode_robot_cost_in_ore + s.ore_robots_count),
					int16_t(s.clay + s.clay_robots_count),
					int16_t(s.obsidian - b.geode_robot_cost_in_clay + s.obsidian_robots_count),
					int16_t(s.geode + s.geode_robots_count),
					s.ore_robots_count,
					s.clay_robots_count,
					s.obsidian_robots_count,
					int16_t(s.geode_robots_count + 1),
					int16_t(s.time_left - 1)));
		}

		return max_geodes;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		int result = 0;
		for (const auto& b : load(input))
			result += b.first * harvest(b.second, 24);

		return result;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		int result = 1;
		for (const auto& b : load(input))
			if (b.first <= 3)
				result *= harvest(b.second, 32);

		return result;
	}
}
