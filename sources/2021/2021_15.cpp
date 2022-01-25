#include "2021_15.h"

namespace Day15_2021
{
	// Dijkstra's shortest path with priority queue
	int Main::find_lowest_risk(const t_graph& graph, int gsize)
	{
		// priority queue from lowest to highest risk
		priority_queue< t_intpair, vector<t_intpair>, greater<t_intpair> > pq;

		// lowest risk from src graph node (0) to any other
		// initializing to max risk
		vector<int> lowest_risk(gsize, INT_MAX);

		// insert source (0) to priority queue and set its risk to 0
		pq.push(make_pair(0, 0));
		lowest_risk[0] = 0;

		// repeat until all elements of lowest_risk are known
		while (!pq.empty())
		{
			int src = pq.top().second;
			pq.pop();

			// get all adjacent of src
			for (const auto& x : graph[src])
			{
				// from src to dst with risk
				int dst = x.first;
				int risk = x.second;

				// if there is lower risk to dst through src...
				if (lowest_risk[dst] > lowest_risk[src] + risk)
				{
					// update lowest_risk of dst
					lowest_risk[dst] = lowest_risk[src] + risk;

					// put to queue to solve
					pq.push(make_pair(lowest_risk[dst], dst));
				}
			}
		}

		// return lowest risk
		// from top-left (0) to bottom-right (last element) corner
		return lowest_risk.back();
	}

	// next risk
	int Main::succ(int r)
	{
		return r == 9 ? 1 : r + 1;
	}

	// solve input enlarging cavern
	int Main::solve(const vector<string>& input, int enlarge /* = 1 */)
	{
		// enlarged risk table
		int isize = (int)input.size();
		int esize = isize * enlarge;
		vector<vector<int>> risk(esize, vector<int>(esize));

		// read input and enlarge it (if required)
		for (int y = 0; y < isize; y++)
			for (int x = 0; x < isize; x++)
			{
				int r = int(input[y][x]) - '0';
				risk[y][x] = r;
				
				for (int ry = 0; ry < enlarge; ry++)
				{
					if (ry > 0)
						r = succ(risk[y + (ry - 1) * isize][x]);

					for (int rx = 0; rx < enlarge; rx++)
					{
						risk[y + ry * isize][x + rx * isize] = r;
						r = succ(r);
					}
				}
			}

		int gsize = esize * esize;
		t_graph graph(gsize, t_vecintpair());

		// initialize graph
		for (int y = 0; y < esize; y++)
			for (int x = 0; x < esize; x++)
				for (int i = 0; i < 4; i++)
				{
					static const t_vecintpair update_position =
						{ { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1} };

					int nx = x + update_position[i].first;
					int ny = y + update_position[i].second;
					if (nx >= 0 && nx < esize && ny >= 0 && ny < esize)
					{
						// source and destination node index:
						// calculated from (x, y) positions
						int src = y * esize + x;
						int dst = ny * esize + nx;

						// connection from src to dst with risk assigned
						graph[src].push_back(make_pair(dst, risk[ny][nx]));
					}
				}

		// find lowest risk
		return find_lowest_risk(graph, gsize);
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return solve(input);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return solve(input, 5);
	}
}
