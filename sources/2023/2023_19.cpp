#include "2023_19.h"

namespace Day19_2023
{
	Workflow::Workflow(string s /* = "" */)
	{
		while (!s.empty())
		{
			size_t pos = s.find_first_of(",");
			if (pos == string::npos)
				pos = s.find_first_of("}");

			rules.push_back(s.substr(0, pos));
			s = s.substr(pos + 1);
		}
	}

	pair<map<string, Workflow>, vector<Part>> Main::load(const vector<string>& input)
	{
		map<string, Workflow> workflows;
		vector<Part> parts;

		size_t i = 0;
		for (; ; i++)
		{
			if (input[i].empty())
				break;

			size_t pos = input[i].find_first_of("{");
			string name = input[i].substr(0, pos);
			workflows[name] = Workflow(input[i].substr(pos + 1));
		}

		i++;
		for (; i < input.size(); i++)
		{
			Part p;
			size_t offset = 0;
			for (int x = 0; x < 4; x++)
			{
				size_t pos = input[i].find_first_of('=', offset);
				p.push_back(stoi(input[i].substr(pos + 1)));
				offset = pos + 1;
			}

			parts.push_back(p);
		}

		return make_pair(workflows, parts);
	}

	int Main::process_part(const Part& part, const map<string, Workflow>& workflows)
	{
		string n = "in";
		while (n != "A")
		{
			if (n == "R")
				return 0;

			const auto& rules = workflows.find(n)->second.rules;
			for (const string& r : rules)
			{
				if (r[1] == '>' || r[1] == '<')
				{
					const string xmas = "xmas";
					int v = part[xmas.find_first_of(r[0])];
					if ((r[1] == '<' && v < stoi(r.substr(2))) || (r[1] == '>' && v > stoi(r.substr(2))))
					{
						n = r.substr(r.find_first_of(':') + 1);
						break;
					}
				}
				else
				{
					n = r;
					break;
				}
			}
		}

		int rating = 0;
		for (int v : part)
			rating += v;

		return rating;
	}

	int64_t Main::solve(const map<string, Workflow>& workflows, string name, vector<Range> ranges)
	{
		if (name == "R")
			return 0;

		if (name == "A")
		{
			int64_t m = 1;
			for (int i = 0; i < 4; i++)
				m *= (ranges[i].second - ranges[i].first + 1);

			return m;
		}

		int64_t sum = 0;
		const auto& rules = workflows.find(name)->second.rules;
		for (const auto& r : rules)
		{
			if (r[1] == '>' || r[1] == '<')
			{
				name = r.substr(r.find_first_of(':') + 1);
				int value = stoi(r.substr(2));
				
				const string xmas = "xmas";
				size_t idx = xmas.find_first_of(r[0]);
				auto [vmin, vmax] = ranges[idx];

				if (r[1] == '<')
				{
					if (vmin < value)
					{
						auto new_ranges = ranges;
						new_ranges[idx].second = value - 1;
						sum += solve(workflows, name, new_ranges);
					}

					if (vmax < value)
						break;
						
					ranges[idx].first = value;
				}
				else
				{
					if (vmax > value)
					{
						auto new_ranges = ranges;
						new_ranges[idx].first = value + 1;
						sum += solve(workflows, name, new_ranges);
					}

					if (vmin > value)
						break;

					ranges[idx].second = value;
				}
			}
		}

		return sum + solve(workflows, rules.back(), ranges);
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto [workflows, parts] = load(input);

		int sum = 0;
		for (const auto& p : parts)
			sum += process_part(p, workflows);

		return sum;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto [workflows, _] = load(input);

		vector<Range> ranges;
		for (int i = 0; i < 4; i++)
			ranges.push_back(Range({ 1, 4000 }));

		return solve(workflows, "in", ranges);
	}
}
