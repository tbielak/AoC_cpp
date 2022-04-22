#include "2018_04.h"

namespace Day04_2018
{
	OneHour::OneHour()
	{
		_minutes = vector<int>(60, 0);
	}

	void OneHour::short_nap(int falls_asleep, int wakes_up)
	{
		for (int i = falls_asleep; i < wakes_up; i++)
			_minutes[i]++;
	}

	int OneHour::minutes_asleep() const
	{
		return accumulate(_minutes.begin(), _minutes.end(), 0);
	}

	pair<int, int> OneHour::max_minute() const
	{
		int m = -1;
		int v = -1;
		for (int i = 0; i < 60; i++)
		{
			if (_minutes[i] > v)
			{
				v = _minutes[i];
				m = i;
			}
		}

		return make_pair(m, v);
	}

	t_guards Main::load(vector<string> input)
	{
		t_guards guards;
		sort(input.begin(), input.end());

		int id = -1;
		int falls_asleep = -1;
		for (const auto& s : input)
		{
			int minute = stoi(s.substr(15, 2));
			switch (s[19])
			{
				case 'G':
				{
					id = stoi(s.substr(26));
					break;
				}

				case 'f':
				{
					falls_asleep = minute;
					break;
				}

				case 'w':
				{
					guards[id].short_nap(falls_asleep, minute);
					break;
				}
			}
		}

		return guards;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto guards = load(input);

		int id = -1;
		int mins = -1;
		for (const auto& [guard, hour] : guards)
		{
			int asleep = hour.minutes_asleep();
			if (asleep > mins)
			{
				mins = asleep;
				id = guard;
			}
		}

		return id * guards[id].max_minute().first;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto guards = load(input);
		
		int id = -1;
		int minute = -1;
		int value = -1;
		for (const auto& [guard, hour] : guards)
		{
			const auto [m, v] = hour.max_minute();
			if (v > value)
			{
				minute = m;
				value = v;
				id = guard;
			}
		}

		return id * minute;
	}
}
