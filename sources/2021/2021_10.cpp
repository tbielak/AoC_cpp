#include "2021_10.h"

namespace Day10_2021
{
	AoC::Output Main::both_parts(const vector<string>& input)
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
}
