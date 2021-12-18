#include "2021_12.h"

namespace Day12_2021
{
	void add(t_graph& graph, const string& from, const string& to)
	{
		auto it = graph.find(from);
		if (it == graph.end())
			graph[from] = t_destinations({ to });
		else
			it->second.push_back(to);
	}

	void load(const t_input& input, t_graph& graph, t_visited& visited)
	{
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
	}

	void go(const t_graph& graph, t_visited visited, const string& here_I_am, string path, t_allpaths& all_paths)
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

	int part_one(const t_graph& graph, t_visited& vis)
	{
		t_allpaths all_paths;
		go(graph, vis, "start", "", all_paths);
		return (int)all_paths.size();
	}

	int part_two(const t_graph& graph, t_visited& visited)
	{
		t_allpaths all_paths;
		for (const auto& v : visited)
		{
			if (v.first[0] <= 'Z' || v.first == "start" || v.first == "end")
				continue;

			for (auto& m : visited)
				m.second.second = (m.first == v.first) ? 2 : 1;

			go(graph, visited, "start", "", all_paths);
		}

		return (int)all_paths.size();
	}

	t_output main(const t_input& input)
	{
		auto t0 = chrono::steady_clock::now();
		t_graph graph;
		t_visited visited;
		load(input, graph, visited);
		
		auto p1 = part_one(graph, visited);
		auto p2 = part_two(graph, visited);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
