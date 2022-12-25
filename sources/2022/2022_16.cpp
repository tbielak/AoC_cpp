#include "2022_16.h"

namespace Day16_2022
{
	Solver::Solver(const vector<string>& input)
	{
		// see header file for some comments on data structures and algorithm draft
		load_input(input);
		shortest_routes();
	}

	int Solver::alone(int time)
	{
		find_paths(time);

		// solution = maximum of cumulated pressures for all paths
		return max_element(_paths.begin(), _paths.end(),
			[](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; })->second;
	}

	int Solver::with_elephant(int time)
	{
		find_paths(time);

		// solution = maximum of sum of two cumulated pressures obtained in two disjointed paths
		int result = 0;
		for (const auto& p1 : _paths)
			for (const auto& p2 : _paths)
				if (p1.first != p2.first && (p1.first & p2.first) == 0)	// disjointed?
					if (result < p1.second + p2.second)
						result = p1.second + p2.second;

		return result;
	}

	void Solver::load_input(const vector<string>& input)
	{
		// convert valves names to ints
		map<string, int> names2id;
		for (int i = 0; i < (int)input.size(); i++)
			names2id[input[i].substr(6, 2)] = i;

		// relevant valves, graph sources and flows of valves
		_start = names2id["AA"];
		_relevant.push_back(_start);
		for (const string& line : input)
		{
			const string& name = line.substr(6, 2);
			_graph[names2id[name]] = vector<int>();

			int flow = stoi(line.substr(23));
			_flow[names2id[name]] = flow;
			if (flow != 0)
				_relevant.push_back(names2id[name]);
		}

		// destinations of tunnels
		for (const string& line : input)
		{
			const string& name = line.substr(6, 2);
			size_t pos = line.find_first_of(' ', line.find("valve", 8)) + 1;
			while (pos < line.size())
			{
				_graph[names2id[name]].push_back(names2id[line.substr(pos, 2)]);
				pos += 4;
			}
		}
	}

	int Solver::bfs(int from, int to)
	{
		// 'dynamic' bfs = inserting cost elements when they appear
		map<int, int> cost;
		queue<pair<int, int>> q;
		q.push(make_pair(from, 0));
		while (q.size() > 0)
		{
			const auto [valve, len] = q.front();
			q.pop();

			if (valve == to)
				continue;

			if (cost.find(valve) == cost.end())
				cost[valve] = INT_MAX;

			if (len > cost[valve])
				continue;

			for (const auto& next : _graph[valve])
			{
				if (cost.find(next) == cost.end())
					cost[next] = INT_MAX;

				if (len + 1 < cost[next])
				{
					cost[next] = len + 1;
					q.push(make_pair(next, len + 1));
				}
			}
		}

		return cost[to];
	}

	void Solver::shortest_routes()
	{
		// shortest routes in graph between all relevant valves
		for (int i = 0; i < (int)_relevant.size(); i++)
			for (int j = i + 1; j < (int)_relevant.size(); j++)
			{
				int len = bfs(_relevant[i], _relevant[j]);
				_routes[_relevant[i]].push_back(make_pair(_relevant[j], len));
				_routes[_relevant[j]].push_back(make_pair(_relevant[i], len));
			}
	}

	void Solver::find_paths(int time)
	{
		queue<tuple<int, int, int, int64_t>> q;
		q.push(make_tuple(_start, 0, time, 0));
		while (q.size() > 0)
		{
			auto [valve, pressure, time, opened] = q.front();
			q.pop();

			// any valve opened?
			if (opened > 0)
			{
				// store path and maximum pressure for that path
				const auto& it = _paths.find(opened);
				if (it == _paths.end())
					_paths[opened] = pressure;
				else
					if (it->second < pressure)
						it->second = pressure;
			}

			// try all targets
			for (const auto& [target, cost] : _routes[valve])
			{
				// check if target valve already opened (visited)
				if ((opened & (int64_t(1) << target)) > 0)
					continue;

				// check if enough time left
				if (cost >= time)
					continue;

				// next state: target valve, cumulated pressure, time left, opened target valve
				q.push(make_tuple(
					target,
					pressure + _flow[target] * (time - cost - 1),
					time - cost - 1,
					opened | (int64_t(1) << target)));
			}
		}
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return Solver(input).alone(30);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return Solver(input).with_elephant(26);
	}
}
