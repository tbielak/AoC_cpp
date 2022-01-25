#ifndef __2019_06__
#define __2019_06__

#include "../shared/Solution.h"

namespace Day06_2019
{
	class Item
	{
	public:
		Item(const string& input);

		string src;
		string target;
		bool visited;
	};

	typedef vector<Item> t_vecItem;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static t_vecItem load(const vector<string>& input);
		static int count_them(const string& s);
		static void recursive_scan_part_one(int& cnt, t_vecItem& items, const string& src, const string& path);
		static void recursive_scan_part_two(t_vecItem& items, const string& src, const string& path, string& san, string& you);
	};
}

#endif
