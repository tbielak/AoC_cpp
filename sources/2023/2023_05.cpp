#include "2023_05.h"

namespace Day05_2023
{
	Range::Range(int64_t from /* = -1 */, int64_t to /* = -1 */)
	:	from(from), to(to)
	{
	}

	bool Range::empty() const
	{
		return from == -1 && to == -1;
	}

	bool Range::operator== (const Range& rhs) const
	{
		return this->from == rhs.from && this->to == rhs.to;
	}

	Range Range::intersection(const Range& rhs) const
	{
		Range result;
		if (this->to < rhs.from || this->from > rhs.to)
			return result;

		if (this->to == rhs.from)
		{
			result.from = this->to;
			result.to = this->to;
			return result;
		}

		if (this->from == rhs.to)
		{
			result.from = this->from;
			result.to = this->from;
			return result;
		}

		result.from = (this->from >= rhs.from) ? this->from : rhs.from;
		result.to = (this->to <= rhs.to) ? this->to : rhs.to;
		return result;
	}

	Item::Item(const Range& range, int64_t shift)
	:	range(range), shift(shift)
	{
	}

	vector<int64_t> Main::load(const string& s)
	{
		size_t pos;
		vector<int64_t> v;
		for (size_t offset = 0; offset < s.size(); offset += pos)
			v.push_back(stoll(s.c_str() + offset, &pos));

		return v;
	}

	Data Main::load(const vector<string>& input, bool ranges)
	{
		Data data;
		auto seeds = load(input[0].substr(7));

		if (ranges)
			for (size_t i = 0; i < seeds.size() / 2; i++)
				data.seeds.push_back(Range(seeds[i * 2], seeds[i * 2] + seeds[i * 2 + 1] - 1));
		else
			for (size_t i = 0; i < seeds.size(); i++)
				data.seeds.push_back(Range(seeds[i], seeds[i]));

		for (size_t i = 1; i < input.size(); i++)
		{
			const string& s = input[i];
			if (s.empty())
			{
				data.maps.push_back(Map());
				continue;
			}

			if (!isdigit(s[0]))
				continue;

			auto v = load(input[i]);
			data.maps.back().push_back(Item(Range(v[1], v[1] + v[2] - 1), v[0] - v[1]));
		}

		return data;
	}

	int64_t Main::find_minimum(const vector<Range>& ranges)
	{
		int64_t v = ranges[0].from;
		for (size_t i = 1; i < ranges.size(); i++)
			v = min(v, ranges[i].from);

		return v;
	}

	int64_t Main::solve(Data data)
	{
		for (const auto& current_map : data.maps)
		{
			vector<Range> output;
			queue<Range> q;
			for (auto& ds : data.seeds)
				q.push(ds);

			while (!q.empty())
			{
				Range r = q.front();
				q.pop();

				bool inserted = false;
				for (auto& m : current_map)
				{
					auto ins = r.intersection(m.range);
					if (ins.empty())
						continue;

					inserted = true;
					output.push_back(Range(ins.from + m.shift, ins.to + m.shift));
					if (ins == r)
						break;

					if (ins.from != r.from)
						q.push(Range(r.from, ins.from - 1));

					if (ins.to != r.to)
						q.push(Range(ins.to + 1, r.to));
				}

				if (!inserted)
					output.push_back(r);
			}

			data.seeds = move(output);
		}

		return find_minimum(data.seeds);
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return solve(load(input, false));
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return solve(load(input, true));
	}
}
