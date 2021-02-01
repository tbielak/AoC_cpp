#include "2020_04.h"

namespace Day04_2020
{
	CheckEngine::CheckEngine(const vector<string>& input)
	{
		string p;
		for (const auto& s : input)
		{
			if (s == "")
			{
				load_passport(p);
				p = "";
				continue;
			}

			if (p != "") p += " ";
			p += s;
		}

		if (p != "")
			load_passport(p);
	}

	size_t CheckEngine::complete_count() const
	{
		return count_if(_passports.begin(), _passports.end(),
			[](const auto& p) { return p.size() == 7; });
	}

	size_t CheckEngine::valid_count() const
	{
		size_t cnt = 0;
		for (const auto& p : _passports)
		{
			if (p.size() != 7)
				continue;

			size_t v = 0;
			for (const auto& f : p)
			{
				const auto& [field, value] = f;
				if (field == "byr" && yr_check(value, 1920, 2002)) v++;
				if (field == "iyr" && yr_check(value, 2010, 2020)) v++;
				if (field == "eyr" && yr_check(value, 2020, 2030)) v++;
				if (field == "hgt" && hgt_check(value)) v++;
				if (field == "hcl" && hcl_check(value)) v++;
				if (field == "ecl" && ecl_check(value)) v++;
				if (field == "pid" && pid_check(value)) v++;
			}

			if (v == 7)
				cnt++;
		}

		return cnt;
	}

	void CheckEngine::load_passport(const string& input)
	{
		_passports.push_back(t_fields());
		stringstream ss(input);
		string s;
		while (getline(ss, s, ' '))
		{
			size_t pos = s.find(':');
			string key = s.substr(0, pos);
			if (key != "cid")
				_passports.back()[key] = s.substr(pos + 1);
		}
	}

	bool CheckEngine::is_number(const string& s) const
	{
		for (auto c : s)
			if (!isdigit(c))
				return false;

		return true;
	}

	bool CheckEngine::yr_check(const string& s, int yr_min, int yr_max) const
	{
		if (s.size() != 4 || !is_number(s))
			return false;

		int yr = stoi(s);
		return yr >= yr_min && yr <= yr_max;
	}

	bool CheckEngine::hgt_check(const string& s) const
	{
		size_t cm = s.find("cm");
		size_t in = s.find("in");
		if (!((cm == string::npos) ^ (in == string::npos)))
			return false;

		size_t pos = min(cm, in);
		string num = s.substr(0, pos);
		if (!is_number(num))
			return false;

		int v = stoi(num);
		return cm == string::npos ? (v >= 59 && v <= 76) : (v >= 150 && v <= 193);
	}

	bool CheckEngine::hcl_check(const string& s) const
	{
		if (s.size() != 7 || s[0] != '#')
			return false;

		for (size_t i = 1; i < 7; i++)
			if (!((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'f')))
				return false;

		return true;
	}

	bool CheckEngine::ecl_check(const string& s) const
	{
		const set<string> valid = { "amb","blu","brn","gry","grn","hzl","oth" };
		return valid.find(s) != valid.end();
	}

	bool CheckEngine::pid_check(const string& s) const
	{
		return s.size() == 9 && is_number(s);
	}

	size_t part_one(const CheckEngine& engine)
	{
		return engine.complete_count();
	}

	size_t part_two(const CheckEngine& engine)
	{
		return engine.valid_count();
	}

	t_output main(const t_input& input)
	{
		auto t0 = chrono::steady_clock::now();
		CheckEngine engine(input);
		auto p1 = part_one(engine);
		auto p2 = part_two(engine);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
