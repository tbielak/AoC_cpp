#include "2018_07.h"

namespace Day07_2018
{
	t_graph Main::load(const vector<string>& input)
	{
		smatch matches;
		regex regex("Step ([A-Z]) must be finished before step ([A-Z]) can begin.");

		t_graph graph;
		for (const auto& line : input)
		{
			// two elements: p and r
			regex_search(line, matches, regex);
			char p = matches[1].str()[0];
			char r = matches[2].str()[0];

			// make sure both elements are in graph
			if (graph.find(p) == graph.end())
				graph[p] = t_setchar();

			if (graph.find(r) == graph.end())
				graph[r] = t_setchar();

			// element r requires element p
			graph.find(r)->second.insert(p);
		}

		return graph;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto graph = load(input);

		string result;
		while (graph.size() > 0)
		{
			// find elements which do not require any prerequisites
			t_setchar s;
			for (const auto& [p, r] : graph)
				if (r.size() == 0)
					s.insert(p);

			// get first of them (in alphabetical order)
			result += *s.begin();

			// erase it from the graph
			graph.erase(*s.begin());

			// erase it from prerequisites of other elements
			for (auto& [p, r] : graph)
				r.erase(*s.begin());
		}

		// done!
		return result;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto graph = load(input);

		// workers keeping {character, seconds left}
		const int max_workers = 5;
		typedef map<char, int> t_workers;
		t_workers workers;

		// seconds elapsed
		int secs = 0;

		while (graph.size() > 0 || workers.size() > 0)
		{
			// any worker ready to take next task?
			if (workers.size() < max_workers)
			{
				// find elements which do not require any prerequisites
				t_setchar s;
				for (const auto& [p, r] : graph)
					if (r.size() == 0)
						s.insert(p);

				// assign them to workers
				for (auto c : s)
					if (workers.size() < max_workers && workers.find(c) == workers.end())
						workers[c] = c - 'A' + 61;
			}

			// one second elapsed on each worker, find workers with tasks completed
			t_setchar completed;
			for (auto& w : workers)
			{
				w.second--;
				if (w.second == 0)
					completed.insert(w.first);
			}

			// any completed tasks?
			for (auto c : completed)
			{
				// free worker
				workers.erase(c);

				// erase completed element from the graph
				graph.erase(c);

				// erase it from prerequisites of other elements
				for (auto& [p, r] : graph)
					r.erase(c);
			}

			// one second elapsed
			secs++;
		}

		// done!
		return secs;
	}
}
