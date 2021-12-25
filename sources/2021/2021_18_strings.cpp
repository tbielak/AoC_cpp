#include "2021_18_strings.h"

namespace Day18_2021_Strings
{
	int read_number(const string& s, size_t& pos)
	{
		int v = 0;
		while (isdigit(s[pos]))
			v = v * 10 + int(s[pos++] - '0');

		return v;
	}

	size_t number_on_left(const string& s, size_t pos)
	{
		while (1)
		{
			if (isdigit(s[pos]))
			{
				while (isdigit(s[pos]))
					pos--;

				return pos + 1;
			}

			if (pos == 0)
				break;

			pos--;
		}

		return string::npos;
	}

	size_t number_on_right(const string& s, size_t pos)
	{
		while (1)
		{
			if (isdigit(s[pos]))
				return pos;

			pos++;

			if (pos == s.size())
				break;
		}

		return string::npos;
	}

	size_t can_explode(const string& s)
	{
		int level = 0;
		for (size_t i = 0; i < s.size(); i++)
		{
			if (s[i] == '[') level++;
			if (level == 5) return i;
			if (s[i] == ']') level--;
		}

		return string::npos;
	}

	bool explode(string& s)
	{
		size_t lpos = can_explode(s);
		if (lpos == string::npos)
			return false;

		size_t rpos = lpos + 1;
		int x = read_number(s, rpos);
		rpos++;
		int y = read_number(s, rpos);
		rpos++;

		size_t ldig = number_on_left(s, lpos);
		if (ldig != string::npos)
		{
			size_t rdig = ldig;
			int v = read_number(s, rdig);
			string nv = to_string(x + v);
			s.erase(ldig, rdig - ldig);
			s.insert(ldig, nv);
			int offs = (int)nv.size() - int(rdig - ldig);
			lpos += offs;
			rpos += offs;
		}

		ldig = number_on_right(s, rpos);
		if (ldig != string::npos)
		{
			size_t rdig = ldig;
			int v = read_number(s, rdig);
			s.erase(ldig, rdig - ldig);
			s.insert(ldig, to_string(y + v));
		}

		s.erase(lpos, rpos - lpos);
		s.insert(lpos, "0");
		return true;
	}

	bool split(string& s)
	{
		for (size_t ldig = 0; ldig < s.size() - 1; ldig++)
			if (isdigit(s[ldig]) && isdigit(s[ldig + 1]))
			{
				size_t rdig = ldig;
				int v = read_number(s, rdig);
				int v2 = v / 2;
				s.erase(ldig, rdig - ldig);
				s.insert(ldig, "[" + to_string(v2) + "," + to_string(v - v2) + "]");
				return true;
			}

		return false;
	}

	void reduce(string& s)
	{
		while (1)
			if (!explode(s) && !split(s))
				return;
	}

	string add(const string& a, const string& b)
	{
		string s = "[" + a + "," + b + "]";
		reduce(s);
		return s;
	}

	int magnitude(string s)
	{
		while (s[0] == '[')
		{
			size_t comma = 1;
			while (!isdigit(s[comma - 1]) || s[comma] != ',' || !isdigit(s[comma + 1]))
				comma++;

			size_t rpar = comma - 1;
			while (isdigit(s[rpar]))
				rpar--;

			rpar++;
			size_t lpar = rpar - 1;
			int lval = read_number(s, rpar);
			rpar++;
			int rval = read_number(s, rpar);
			rpar++;

			s.erase(lpar, rpar - lpar);
			s.insert(lpar, to_string(lval * 3 + rval * 2));
		}

		return stoi(s);
	}

	int part_one(const t_input& input)
	{
		string s = input[0];
		for (size_t i = 1; i < input.size(); i++)
			s = add(s, input[i]);

		return magnitude(s);
	}

	int part_two(const t_input& input)
	{
		int largest = 0;

		for (size_t i = 0; i < input.size(); i++)
			for (size_t j = 0; j < input.size(); j++)
				if (i != j)
				{
					string s = add(input[i], input[j]);
					int mag = magnitude(s);
					largest = max(largest, mag);
				}

		return largest;
	}

	t_output main(const t_input& input)
	{
		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(input);
		auto p2 = part_two(input);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
