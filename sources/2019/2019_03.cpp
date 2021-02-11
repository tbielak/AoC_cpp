#include "2019_03.h"

namespace Day03_2019
{
	Wire::Wire(const string& input)
	{
		string s;
		stringstream ss(input);
		while (getline(ss, s, ','))
			_path.push_back(make_pair(s[0], stoi(s.substr(1))));
	}

	void Wire::twists_and_turns()
	{
		int step = 0;
		pair<int, int> position;
		static map<char, pair<int, int>> turns = { {'R', {1, 0} }, {'U', {0, -1} }, {'L', {-1, 0} }, {'D', {0, 1} } };

		for (const auto& current_step : _path)
		{
			const auto& [direction, distance] = current_step;
			for (int i = 0; i < distance; i++)
			{
				position.first += turns[direction].first;
				position.second += turns[direction].second;
				_points[position] = ++step;
			}
		}
	}

	int Wire::distance_to_closest(const Wire& other)
	{
		int distance = INT_MAX;
		for (const auto& w1 : _points)
		{
			const auto& point = w1.first;
			const auto& w2 = other._points.find(point);
			if (w2 != other._points.end())
				distance = min(distance, abs(point.first) + abs(point.second));
		}

		return distance;
	}

	int Wire::fewest_steps(const Wire& other)
	{
		int steps = INT_MAX;
		for (const auto& w1 : _points)
		{
			const auto& w2 = other._points.find(w1.first);
			if (w2 != other._points.end())
				steps = min(steps, w1.second + w2->second);
		}

		return steps;
	}

	pair<int, int> both_parts(Wire& w1, Wire& w2)
	{
		w1.twists_and_turns();
		w2.twists_and_turns();
		return make_pair(w1.distance_to_closest(w2), w1.fewest_steps(w2));
	}

	t_output main(const t_input& input)
	{
		Wire w1(input[0]);
		Wire w2(input[1]);

		auto t0 = chrono::steady_clock::now();
		auto px = both_parts(w1, w2);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(px.first));
		solutions.push_back(to_string(px.second));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
