#include "2016_02.h"

namespace Day02_2016
{
	char Main::press(const vector<string>& key_map, const string& digit)
	{
		static string directions = "UDLR";
		char curr = '5';
		for (auto d : digit)
			curr = key_map[directions.find_first_of(d)][curr - '0'];

		return (curr > '9') ? char(curr - '0' - 10 + 'A') : curr;
	}

	string Main::enter_code(const vector<string>& key_map, const vector<string>& input)
	{
		string code;
		for (const auto& digit : input)
			code += press(key_map, digit);

		return code;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		static const vector<string> key_map = { "0123123456", "0456789789", "0112445778","0233566899" };
		return enter_code(key_map, input);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		static const vector<string> key_map = { "0121452349678;", "036785:;<9:=<=", "0122355678::;=", "0134467899;<<=" };
		return enter_code(key_map, input);
	}
}
