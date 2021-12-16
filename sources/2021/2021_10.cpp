#include "2021_10.h"

namespace Day10_2021
{
	pair<intmax_t, intmax_t> both_parts(const t_input& input)
	{
		static string open = "([{<";
		static string close = ")]}>";
		static vector<intmax_t> corrupted_points = { 3, 57, 1197, 25137 };
		static vector<intmax_t> autocomplete_points = { 1, 2, 3, 4 };

		intmax_t corrupted_score = 0;
		vector<intmax_t> all_autocomplete_scores;
		for (const auto& s : input)
		{
			stack<int> stack;
			bool corrupted = false;

			for (auto c : s)
			{
				size_t pos = open.find_first_of(c);
				if (pos != string::npos)
				{
					// opening char
					stack.push(int(pos));
				}
				else
				{
					// closing char
					int pos = (int)close.find_first_of(c);
					int top = stack.top();
					if (pos != top)
					{
						// corrupted
						corrupted_score += corrupted_points[pos];
						corrupted = true;
						break;
					}

					stack.pop();
				}
			}

			if (!corrupted)
			{
				// autocomplete score
				intmax_t autocomplete_score = 0;
				while (!stack.empty())
				{
					autocomplete_score *= 5;
					autocomplete_score += autocomplete_points[stack.top()];
					stack.pop();
				}

				all_autocomplete_scores.push_back(autocomplete_score);
			}
		}

		sort(all_autocomplete_scores.begin(), all_autocomplete_scores.end());
		return make_pair(corrupted_score, all_autocomplete_scores[all_autocomplete_scores.size() / 2]);
	}

	t_output main(const t_input& input)
	{
		auto t0 = chrono::steady_clock::now();
		auto px = both_parts(input);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(px.first));
		solutions.push_back(to_string(px.second));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
