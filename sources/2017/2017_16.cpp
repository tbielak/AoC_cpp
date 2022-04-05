#include "2017_16.h"

namespace Day16_2017
{
	DanceMove::DanceMove(char cmd, int p1, int p2 /* = 0 */)
	{
		switch (cmd)
		{
			case 's':
			{
				dance_move = [p1](string& progs)
				{
					progs = progs.substr(progs.size() - p1) + progs.substr(0, progs.size() - p1);
				};

				break;
			}

			case 'x':
			{
				dance_move = [p1, p2](string& progs)
				{
					swap(progs[p1], progs[p2]);
				};

				break;
			}

			case 'p':
			{
				dance_move = [p1, p2](string& progs)
				{
					swap(progs[progs.find_first_of(char(p1))], progs[progs.find_first_of(char(p2))]);
				};

				break;
			}
		}
	}

	t_dance Main::load(const string& input)
	{
		t_dance dance;
		stringstream ss(input);

		char cmd;
		while (ss >> cmd)
		{
			switch (cmd)
			{
				case 's':
				{
					int count;
					ss >> count;
					ss.ignore(1);
					dance.push_back(DanceMove(cmd, count));
					break;
				}

				case 'x':
				{
					int p1, p2;
					ss >> p1;
					ss.ignore(1);
					ss >> p2;
					ss.ignore(1);
					dance.push_back(DanceMove(cmd, p1, p2));
					break;
				}

				case 'p':
				{
					char p1, p2;
					ss >> p1;
					ss.ignore(1);
					ss >> p2;
					ss.ignore(1);
					dance.push_back(DanceMove(cmd, p1, p2));
					break;
				}
			}
		}

		return dance;
	}

	void Main::do_the_dance(string& progs, const t_dance& dance)
	{
		for (const auto& ins : dance)
			ins.dance_move(progs);
	}

	AoC::Output Main::part_one(const string& input)
	{
		auto dance = load(input);
		string progs = "abcdefghijklmnop";
		do_the_dance(progs, dance);
		return progs;
	}

	AoC::Output Main::part_two(const string& input)
	{
		auto dance = load(input);
		string progs = "abcdefghijklmnop";
		string stored;
		
		int one_loop = 0;
		for (; ; one_loop++)
		{
			do_the_dance(progs, dance);
			if (stored.size() == 0)
				stored = progs;
			else
				if (progs == stored)
					break;
		}

		int64_t count = 1000000000 % one_loop;
		for (int64_t i = 0; i < count - 1; i++)
			do_the_dance(progs, dance);
		
		return progs;
	}
}
