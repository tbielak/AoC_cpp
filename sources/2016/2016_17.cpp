#include "2016_17.h"
#include "../MD5/MD5.h"

namespace Day17_2016
{
	const static vector<pair<int, int>> update_position = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };
	const static string next_step = "UDLR";

	void Main::go(int x, int y, const string& input, string path, string& shortest_path, string& longest_path)
	{
		if (x == 3 && y == 3)
		{
			if (shortest_path.size() == 0 || path.size() < shortest_path.size())
				shortest_path = path;

			if (longest_path.size() == 0 || path.size() > longest_path.size())
				longest_path = path;

			return;
		}

		string hash = RFC1321::MD5(input + path).get();
		for (int i = 0; i < (int)update_position.size(); i++)
		{
			if (hash[i] < 'b')
				continue;

			int nx = x + update_position[i].first;
			int ny = y + update_position[i].second;
			if (nx < 0 || nx > 3 || ny < 0 || ny > 3)
				continue;

			go(nx, ny, input, path + next_step[i], shortest_path, longest_path);
		}
	}

	AoC::Output Main::both_parts(const string& input)
	{
		string shortest_path, longest_path;
		go(0, 0, input, "", shortest_path, longest_path);
		return make_pair(shortest_path, to_string(longest_path.size()));
	}
}
