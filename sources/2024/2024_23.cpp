#include "2024_23.h"

namespace Day23_2024
{
    t_graph Main::load(const vector<string>& input)
    {
        t_graph graph;
        for (const string& s : input)
        {
            string a = s.substr(0, 2);
            string b = s.substr(3, 2);
            graph[a].insert(b);
            graph[b].insert(a);
        }

        return graph;
    }

    set<string> Main::find_trios(const t_graph& graph)
    {
        set<string> trios;
        for (const auto& [from, to] : graph)
        {
            if (to.size() < 2)
                continue;

            vector<string> dst;
            for (const auto& s : to)
                dst.push_back(s);

            for (int i = 0; i < (int)dst.size(); i++)
                for (int j = i + 1; j < (int)dst.size(); j++)
                {
                    const auto& v = graph.find(dst[i])->second;
                    if (v.find(dst[j]) != v.end())
                    {
                        vector<string> v;
                        v.push_back(from);
                        v.push_back(dst[i]);
                        v.push_back(dst[j]);
                        sort(v.begin(), v.end());
                        trios.insert(v[0] + v[1] + v[2]);
                    }
                }
        }

        return trios;
    }

    // https://en.wikipedia.org/wiki/Bron%E2%80%93Kerbosch_algorithm
    void Main::bron_kerbosch_algorithm(
        set<string>&& R, set<string>&& P, set<string>&& X,
        t_graph& graph, vector<set<string>>& cliques)
    {
        if (P.empty() && X.empty())
        {
            cliques.push_back(R);
            return;
        }

        while (!P.empty())
        {
            string v = *P.begin();

            set<string> newR = R;
            newR.insert(v);

            set<string> newP;
            for (const string& p : P)
                if (graph[v].find(p) != graph[v].end())
                    newP.insert(p);

            set<string> newX;
            for (const string& x : X)
                if (graph[v].find(x) != graph[v].end())
                    newX.insert(x);

            bron_kerbosch_algorithm(move(newR), move(newP), move(newX), graph, cliques);
            P.erase(v);
            X.insert(v);
        }
    }

	AoC::Output Main::part_one(const vector<string>& input)
	{
        auto graph = load(input);
        auto trios = find_trios(graph);

		int c = 0;
		for (const auto& s : trios)
			if (s[0] == 't' || s[2] == 't' || s[4] == 't')
				c++;

		return c;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
        auto graph = load(input);
        
        set<string> vertices;
        for (const auto& [from, _] : graph)
            vertices.insert(from);

        vector<set<string>> cliques;
        bron_kerbosch_algorithm({}, move(vertices), {}, graph, cliques);

        size_t max_size = 0;
        for (const auto& c : cliques)
            max_size = max(max_size, c.size());

        string result;
        for (const auto& c : cliques)
            if (c.size() == max_size)
                for (const auto& s : c)
                    result += s + ",";
        
        return result.substr(0, result.size() - 1);
    }
}
