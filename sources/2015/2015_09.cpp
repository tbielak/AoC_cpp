#include "2015_09.h"

namespace Day09_2015
{
	Distance::Distance(const string& from, const string& to, int distance)
	:	from(from), to(to), distance(distance)
	{
	}
	
	World::World(const t_vecDistance& input)
	:	_shortest(INT_MAX), _longest(0), _length(0)
	{
		for (const auto& x : input)
		{
			addPlace(x.from);
			addPlace(x.to);
		}

		vector<int> x(_places.size());
		_distances = vector<vector<int>>(_places.size(), x);
		for (const auto& x : input)
		{
			auto i = _places.find(x.from)->second;
			auto j = _places.find(x.to)->second;
			_distances[i][j] = x.distance;
			_distances[j][i] = x.distance;
		}

		_visited = vector<bool>(_places.size());
	}

	void World::travel_to(size_t i)
	{
		_visited[i] = true;
		if (count(_visited.begin(), _visited.end(), true) == (int)_places.size())
		{
			_shortest = min(_shortest, _length);
			_longest = max(_longest, _length);
		}

		for (size_t j = 0; j < _places.size(); j++)
			if (_distances[i][j] > 0 && !_visited[j])
			{
				_length += _distances[i][j];
				travel_to(j);
				_length -= _distances[i][j];
			}

		_visited[i] = false;
	}

	void World::tournee()
	{
		for (size_t i = 0; i < _places.size(); i++)
			travel_to(i);
	}

	void World::addPlace(const string& p)
	{
		if (_places.find(p) == _places.end())
		{
			auto size = _places.size();
			_places[p] = size;
		}
	}

	pair<int, int> both_parts(const t_vecDistance& input)
	{
		World world(input);
		world.tournee();
		return make_pair(world.shortest(), world.longest());
	}

	t_output main(const t_input& input)
	{
		t_vecDistance vdist;
		regex regex("([A-Za-z]*) to ([A-Za-z]*) = (.*)");
		smatch matches;
		for (const auto& line : input)
		{
			regex_search(line, matches, regex);
			vdist.push_back(Distance(matches[1].str(), matches[2].str(), stoi(matches[3].str())));
		}

		auto t0 = chrono::steady_clock::now();
		auto px = both_parts(vdist);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(px.first));
		solutions.push_back(to_string(px.second));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
