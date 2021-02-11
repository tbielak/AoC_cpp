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

	int count_them(const string& s)
	{
		return (int)count(s.begin(), s.end(), ')');
	}

	void recursive_scan_part_one(int& cnt, t_vecItem& items, const string& src, const string& path)
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

	void recursive_scan_part_two(t_vecItem& items, const string& src, const string& path, string& san, string& you)
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

	int part_one(t_vecItem input)
	{
		int cnt = 0;
		recursive_scan_part_one(cnt, input, "COM", "COM");
		return cnt;
	}

	int part_two(t_vecItem input)
	{
		string san, you;
		recursive_scan_part_two(input, "COM", "COM", san, you);

		size_t i = 0;
		while (san[i] == you[i])
			i++;

		return count_them(san.substr(i)) + count_them(you.substr(i));
	}

	t_output main(const t_input& input)
	{
		t_vecItem items;
		for (const auto& line : input)
			items.push_back(Item(line));

		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(items);
		auto p2 = part_two(items);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
