#include "2017_12.h"

namespace Day12_2017
{
	t_programs Main::load(const string& input)
	{
		t_programs progs;
		string s;
		stringstream ss(input);
		while (getline(ss, s, ','))
		{
			progs.insert(stoi(s));
			ss.ignore(1);
		}

		return progs;
	}

	t_connections Main::load(const vector<string>& input)
	{
		t_connections connections;
		for (const string& s : input)
		{
			size_t pos = s.find(" <-> ");
			connections[stoi(s.substr(0, pos))] = load(s.substr(pos + 5));
		}

		return connections;
	}

	t_programs Main::find_group(const t_connections& connections, int group)
	{
		t_programs result = { group };
		t_programs looking_for = result;
		
		while (!looking_for.empty())
		{
			t_programs next;
			for (const auto& c : connections)
			{
				auto [id, progs] = c;

				t_programs intersection;
				set_intersection(progs.begin(), progs.end(), looking_for.begin(), looking_for.end(), inserter(intersection, intersection.end()));

				if (intersection.size() > 0 && result.find(id) == result.end())
				{
					result.insert(id);
					next.insert(id);
				}
			}

			looking_for = move(next);
		}

		return result;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return find_group(load(input), 0).size();
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		int count = 0;
		auto connections = load(input);
		
		while (connections.size() > 0)
		{
			count++;
			auto group = find_group(connections, connections.begin()->first);

			t_connections left;
			for (const auto& c : connections)
				if (group.find(c.first) == group.end())
					left.insert(c);

			connections = move(left);
		}

		return count;
	}
}
