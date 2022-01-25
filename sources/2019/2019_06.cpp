#include "2019_06.h"

namespace Day06_2019
{
	Item::Item(const string& input)
	:	visited(false)
	{
		size_t position = input.find_first_of(')');
		src = input.substr(0, position);
		target = input.substr(position + 1);
	}

	t_vecItem Main::load(const vector<string>& input)
	{
		t_vecItem items;
		for (const auto& line : input)
			items.push_back(Item(line));

		return items;
	}

	int Main::count_them(const string& s)
	{
		return (int)count(s.begin(), s.end(), ')');
	}

	void Main::recursive_scan_part_one(int& cnt, t_vecItem& items, const string& src, const string& path)
	{
		for (auto& s : items)
		{
			if (!s.visited && s.src == src)
			{
				s.visited = true;
				string p = path + ")" + s.target;
				cnt += count_them(p);

				recursive_scan_part_one(cnt, items, s.target, p);
			}
		}
	}

	void Main::recursive_scan_part_two(t_vecItem& items, const string& src, const string& path, string& san, string& you)
	{
		for (auto& s : items)
		{
			if (!s.visited && s.src == src)
			{
				s.visited = true;
				string p = path + ")" + s.target;

				if (p.find("YOU") != string::npos)
					you = p;

				if (p.find("SAN") != string::npos)
					san = p;

				recursive_scan_part_two(items, s.target, p, san, you);
			}
		}
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		t_vecItem items = load(input);

		int cnt = 0;
		recursive_scan_part_one(cnt, items, "COM", "COM");
		return cnt;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		t_vecItem items = load(input);

		string san, you;
		recursive_scan_part_two(items, "COM", "COM", san, you);

		size_t i = 0;
		while (san[i] == you[i])
			i++;

		return count_them(san.substr(i)) + count_them(you.substr(i));
	}
}
