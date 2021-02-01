#include "2015_19.h"

namespace Day19_2015
{
	Replacement::Replacement(const string& src, const string& dst)
	:	src(src), dst(dst), random(0)
	{
	}

	size_t part_one(const string& molecule, const t_vecReplacement& replacements)
	{
		set<string> distinct;
		for (const auto& r : replacements)
		{
			size_t len = r.src.size();
			for (size_t i = 0; i <= molecule.size() - len; i++)
			{
				if (molecule.substr(i, len) == r.src)
				{
					string s = molecule;
					s.erase(i, len);
					s.insert(i, r.dst);
					distinct.insert(s);
				}
			}
		}

		return distinct.size();
	}

	size_t part_two(const string& molecule, t_vecReplacement& replacements)
	{
		// initialize random engine
		int seed = (int)chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
		default_random_engine engine(seed);
		uniform_int_distribution<int> dist(0, INT_MAX);

		// find fewest number of steps
		int steps = 0;
		string s = molecule;
		bool done = false;
		while (!done)
		{
			bool any = false;
			for (const auto& r : replacements)
			{
				size_t p = s.find(r.dst);
				if (p != string::npos)
				{
					any = true;
					s.erase(p, r.dst.size());
					s.insert(p, r.src);
					steps++;
					if (s == "e")
					{
						done = true;
						break;
					}
				}
			}

			if (!any)
			{
				// in case of stall -> shuffle replacements...
				for (auto& r : replacements)
					r.random = dist(engine);

				sort(replacements.begin(), replacements.end(),
					[](const auto& a, const auto& b) { return a.random < b.random; });

				// ...and try again
				s = molecule;
				steps = 0;
			}
		}

		return steps;
	}

	t_output main(const t_input& input)
	{
		t_vecReplacement replacements;
		size_t idx = 0;
		for (; idx < input.size(); idx++)
		{
			const auto& line = input[idx];
			if (line == "")
				break;

			size_t pos = line.find(" => ");
			replacements.push_back(Replacement(line.substr(0, pos), line.substr(pos + 4)));
		}
		
		string molecule = input[idx + 1];
		
		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(molecule, replacements);
		auto p2 = part_two(molecule, replacements);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
