#include "2015_13.h"

namespace Day13_2015
{
	Input::Input(const string& person1, const string& person2, int happiness)
	:	person1(person1), person2(person2), happiness(happiness)
	{
	}

	Happiness::Happiness()
	{
	}

	void Happiness::create_persons(const t_vecInput& input)
	{
		for (const auto& i : input)
		{
			add_person(i.person1);
			add_person(i.person2);
		}
	}

	void Happiness::add_me()
	{
		add_person("me");
	}

	void Happiness::who_likes_who(const t_vecInput& input)
	{
		vector<int> v = vector<int>(_persons.size());
		_likes = vector<vector<int>>(_persons.size(), v);
		for (const auto& i : input)
			_likes[_persons[i.person1]][_persons[i.person2]] = i.happiness;
	}

	int Happiness::max_happiness()
	{
		size_t count = _persons.size();
		_setup = vector<int>(count);
		for (int i = 0; i < (int)count; i++)
			_setup[i] = i;

		int maxh = INT_MIN;
		do
		{
			int h = 0;
			for (size_t i = 0; i < count; i++)
			{
				size_t idx1 = _setup[i];
				size_t idx2 = _setup[(i + 1) % count];
				h += _likes[idx1][idx2];
				h += _likes[idx2][idx1];
			}

			maxh = max(h, maxh);
		} while (next_permutation(_setup.begin(), _setup.end()));

		return maxh;
	}

	void Happiness::add_person(const string& s)
	{
		int i = (int)_persons.size();
		if (_persons.find(s) == _persons.end())
			_persons[s] = i;
	}
	
	int part_one(Happiness& h, const t_vecInput& input)
	{
		h.create_persons(input);
		h.who_likes_who(input);
		return h.max_happiness();
	}

	int part_two(Happiness& h, const t_vecInput& input)
	{
		h.add_me();
		h.who_likes_who(input);
		return h.max_happiness();
	}

	t_output main(const t_input& input)
	{
		t_vecInput vinput;
		regex regex("(.*)( would )(lose|gain)([ ])([0-9]*)( happiness units by sitting next to )(.*)([.])");
		smatch matches;
		for (const auto& line : input)
		{
			regex_search(line, matches, regex);
			int happiness = stoi(matches[5].str());
			vinput.push_back(Input(matches[1].str(), matches[7].str(), (matches[3].str() == "gain") ? happiness : -happiness));
		}

		Happiness h;
		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(h, vinput);
		auto p2 = part_two(h, vinput);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
