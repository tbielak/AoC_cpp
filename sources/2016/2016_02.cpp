#include "2016_02.h"

namespace Day02_2016
{
	char press(const vector<string>& key_map, const string& digit, char& curr)
	{
		static string directions = "UDLR";
		for (auto d : digit)
			curr = key_map[directions.find_first_of(d)][curr - '0'];

		return (curr > '9') ? char(curr - '0' - 10 + 'A') : curr;
	}

	string enter_code(const vector<string>& key_map, const t_input& input)
	{
		string code;
		char curr = '5';
		for (const auto& digit : input)
			code += press(key_map, digit, curr);

		return code;
	}

	string part_one(const t_input& input)
	{
		static const vector<string> key_map = { "0123123456", "0456789789", "0112445778","0233566899" };
		return enter_code(key_map, input);
	}

	string part_two(const t_input& input)
	{
		static const vector<string> key_map = { "0121452349678;", "036785:;<9:=<=", "0122355678::;=", "0134467899;<<=" };
		return enter_code(key_map, input);
	}

	t_output main(const t_input& input)
	{
		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(input);
		auto p2 = part_two(input);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(p1);
		solutions.push_back(p2);
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
