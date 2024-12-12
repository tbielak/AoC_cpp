#include "2024_01.h"

namespace Day01_2024
{
	int Main::iabs(int i)
	{
		return (i < 0) ? -i : i;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		vector<int> left, right;

		for (const auto& s : input)
		{
			left.push_back(stoi(s.substr(0, 5)));
			right.push_back(stoi(s.substr(8, 5)));
		}

		sort(left.begin(), left.end());
		sort(right.begin(), right.end());

		int total_distance = 0;
		for (size_t i = 0; i < left.size(); i++)
			total_distance += iabs(left[i] - right[i]);

		return total_distance;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		set<int> left;
		map<int, int> right;

		for (const auto& s : input)
		{
			left.insert(stoi(s.substr(0, 5)));
			right[stoi(s.substr(8, 5))]++;
		}

		int64_t similarity_score = 0;
		for (auto i : left)
		{
			auto it = right.find(i);
			if (it != right.end())
				similarity_score += right[i] * i;
		}

		return similarity_score;
	}
}
