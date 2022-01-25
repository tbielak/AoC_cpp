#include "2021_12.h"

namespace Day12_2021
{
	void Main::add(t_graph& graph, const string& from, const string& to)
	{
		auto it = graph.find(from);
		if (it == graph.end())
			graph[from] = t_destinations({ to });
		else
			it->second.push_back(to);
	}

	pair<t_graph, t_visited> Main::load(const vector<string>& input)
	{
		t_graph graph;
		t_visited visited;

		for (const auto& s : input)
		{
			size_t pos = s.find_first_of('-');
			string left = s.substr(0, pos);
			string right = s.substr(pos + 1);
			add(graph, left, right);
			add(graph, right, left);
		}

		for (const auto& node : graph)
			visited[node.first] = make_pair(0, 1);

		return make_pair(graph, visited);
	}

	void Main::go(const t_graph& graph, t_visited visited, const string& here_I_am, string path, t_allpaths& all_paths)
	{
		if (here_I_am == "end")
		{
			all_paths.insert(path);
			return;
		}

		path += here_I_am + ",";
		visited[here_I_am].first++;
		const auto& destinations = graph.find(here_I_am)->second;
		
		for (const auto& node : destinations)
		{
			if (node[0] <= 'Z')
				go(graph, visited, node, path, all_paths);
			else
			{
				const auto& v = visited.find(node);
				if (v->second.first < v->second.second)
					go(graph, visited, node, path, all_paths);
			}
		}
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto [graph, visited] = load(input);

		t_allpaths all_paths;
		go(graph, visited, "start", "", all_paths);
		return all_paths.size();
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto [graph, visited] = load(input);

		t_allpaths all_paths;
		for (const auto& v : visited)
		{
			if (v.first[0] <= 'Z' || v.first == "start" || v.first == "end")
				continue;

			for (auto& m : visited)
				m.second.second = (m.first == v.first) ? 2 : 1;

			go(graph, visited, "start", "", all_paths);
		}

		return all_paths.size();
	}
}
