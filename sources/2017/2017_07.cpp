#include "2017_07.h"

namespace Day07_2017
{
	Program::Program(const string& name)
	:	name(name), weight(0)
	{
	}

	int Program::count() const
	{
		return accumulate(above.begin(), above.end(), 1, [](int s, auto a) { return s + a->count(); });
	}

	int Program::recursive_weight() const
	{
		int result = weight;
		for (auto& x : above)
			result += x->recursive_weight();

		return result;
	}

	Tower::Tower(const vector<string>& input)
	{
		smatch matches;
		regex regex("([a-z]*) [(]([0-9]*)[)]");

		for (auto s : input)
		{
			string above;
			size_t pos = s.find(" -> ");
			if (pos != string::npos)
			{
				above = s.substr(pos + 4);
				s = s.substr(0, pos);
			}

			regex_search(s, matches, regex);
			Program* p = add(matches[1]);
			p->weight = stoi(matches[2]);
			
			while (above.size() > 0)
			{
				string name;
				size_t pos = above.find_first_of(',');
				if (pos == string::npos)
				{
					name = above;
					above = "";
				}
				else
				{
					name = above.substr(0, pos);
					above = above.substr(pos + 2);
				}

				p->above.push_back(add(name));
			}
		}

		for (auto& p : _programs)
			p.second->tree_weight = p.second->recursive_weight();

		for (t_mapptrProgram::const_iterator it = _programs.begin(); it != _programs.end(); it++)
			if (it->second->count() == (int)_programs.size())
				_bottom = it;
	}

	Tower::~Tower()
	{
		for (auto p : _programs)
			delete p.second;
	}

	Program* Tower::add(const string& name)
	{
		t_mapptrProgram::iterator it = _programs.find(name);
		if (it != _programs.end())
			return it->second;

		Program* p = new Program(name);
		_programs[name] = p;
		return p;
	}
	
	string Tower::bottom_name() const
	{
		return _bottom->first;
	}

	int Tower::weight_correction() const
	{
		int correction = -1;

		queue<Program*> q;
		q.push(_bottom->second);
		while (q.size() > 0)
		{
			Program* p = q.front();
			q.pop();

			if (p->above.size() == 0)
				continue;

			map<int, int> values;
			for (const auto& a : p->above)
				values[a->tree_weight]++;

			if (values.size() > 2)
				return -1;  // no solution (should not be reached)

			if (values.size() == 2)
			{
				int diff = (values.begin()->second == 1)
					? values.rbegin()->first - values.begin()->first
					: values.begin()->first - values.rbegin()->first;

				int not_balanced = (values.begin()->second == 1)
					? values.begin()->first
					: values.rbegin()->first;

				for (const auto& a : p->above)
					if (a->tree_weight == not_balanced)
						correction = a->weight + diff;
			}

			for (const auto& a : p->above)
				q.push(a);
		}

		return correction;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return Tower(input).bottom_name();
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return Tower(input).weight_correction();
	}
}
