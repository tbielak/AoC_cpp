#include "2022_12_mt.h"

namespace Day12_2022_MT
{
	Point::Point(int x /* = 0 */, int y /* = 0 */)
	:	x(x), y(y)
	{
	}

	bool Point::operator == (const Point& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}

	bool Point::operator < (const Point& rhs) const
	{
		return (x == rhs.x) ? y < rhs.y : x < rhs.x;
	}

	bool Main::climbing(char from, char to)
	{
		if (from == 'S')
			from = 'a';

		if (to == 'E')
			to = 'z';

		return to <= from + 1;
	}

	int Main::bfs(const vector<string>& input, const Point& start)
	{
		int width = (int)input[0].size();
		int height = (int)input.size();
		const vector<int> move_x = { -1, 1, 0, 0 };
		const vector<int> move_y = { 0, 0, -1, 1 };

		t_visited visited;
		t_queue queue;
		queue.push(make_pair(start, 0));

		while (!queue.empty())
		{
			auto [p, steps] = queue.front();
			queue.pop();

			if (input[p.y][p.x] == 'E')
				return steps;

			if (visited.find(p) == visited.end())
			{
				visited.insert(p);
				for (int i = 0; i < 4; i++)
				{
					int x = p.x + move_x[i];
					int y = p.y + move_y[i];
					if (x >= 0 && x < width && y >= 0 && y < height && climbing(input[p.y][p.x], input[y][x]))
						queue.push(make_pair(Point(x, y), steps + 1));
				}
			}
		}

		return INT_MAX;
	}

	void Main::batch_bfs(const vector<string>& input, const vector<Point>& start, int& shortest)
	{
		shortest = INT_MAX;
		for (const auto& p : start)
			shortest = min(shortest, bfs(input, p));
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		Point start;
		for (int y = 0; y < (int)input.size(); y++)
			for (int x = 0; x < (int)input[0].size(); x++)
				if (input[y][x] == 'S')
					start = Point(x, y);

		return bfs(input, start);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		int thread_count = (int)thread::hardware_concurrency();
		vector<vector<Point>> points = vector<vector<Point>>(thread_count, vector<Point>());
		vector<int> shortest = vector<int>(thread_count, INT_MAX);

		int thread_idx = 0;
		for (int y = 0; y < (int)input.size(); y++)
			for (int x = 0; x < (int)input[0].size(); x++)
				if (input[y][x] == 'a')
				{
					points[thread_idx++].push_back(Point(x, y));
					thread_idx %= thread_count;
				}

		vector<thread *> threads = vector<thread *>(thread_count, 0);
		for (int t = 0; t < thread_count; t++)
			threads[t] = new thread(batch_bfs, ref(input), points[t], ref(shortest[t]));

		for (auto t : threads)
			t->join();

		for (auto t : threads)
			delete t;

		return *min_element(shortest.begin(), shortest.end());
	}
}
