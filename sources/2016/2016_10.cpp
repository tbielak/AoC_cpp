#include "2016_10.h"

namespace Day10_2016
{
	LowHigh::LowHigh(int low, int high)
	:	low(low), high(high)
	{
	}
	
	SetIns::SetIns(int bot, int value)
	:	bot(bot), value(value)
	{
	}

	Target::Target(char target, int index)
	:	target(target), index(index)
	{
	}

	MoveIns::MoveIns(const string& low_target, int low_index, const string& high_target, int high_index)
	:	low(Target(low_target[0], low_index)), high(Target(high_target[0], high_index))
	{
	}

	void Main::set_value(t_bots& bots, const SetIns& ins, const LowHigh& cmp, int& cmp_bot)
	{
		auto it = bots.find(ins.bot);
		if (it == bots.end())
		{
			// new bot, first value -> goes to low
			bots.insert(t_bots::value_type(ins.bot, LowHigh(ins.value, -1)));
		}
		else
		{
			if (it->second.low == -1)
			{
				// bot having no microchips, first goes to low
				it->second.low = ins.value;
			}
			else
			{
				// bot has one microchips
				if (ins.value > it->second.low)
				{
					// microchip value is higher than low -> value goes to high
					it->second.high = ins.value;
				}
				else
				{
					// microchip value is lower than low -> swapping values
					it->second.high = it->second.low;
					it->second.low = ins.value;
				}

				// comparison observer
				if (it->second.low == cmp.low && it->second.high == cmp.high)
					cmp_bot = ins.bot;
			}
		}
	}

	AoC::Output Main::both_parts(const vector<string>& input)
	{
		// read input
		smatch matches;
		regex regex_set("value ([0-9]*) goes to bot ([0-9]*)");
		regex regex_move("bot ([0-9]*) gives low to (bot|output) ([0-9]*) and high to (bot|output) ([0-9]*)");

		t_setins sets;
		t_moveins moves;
		for (const auto& instruction : input)
		{
			if (instruction[0] == 'v')
			{
				regex_search(instruction, matches, regex_set);
				sets.push_back(SetIns(stoi(matches[2]), stoi(matches[1])));
			}
			else
			{
				regex_search(instruction, matches, regex_move);
				moves.insert(t_moveins::value_type(
					stoi(matches[1]),
					MoveIns(matches[2], stoi(matches[3]), matches[4], stoi(matches[5]))
				));
			}
		}

		// prepare bots, output bin and comparison observer
		t_bots bots;
		t_outputbin outputbin;

		int cmp_bot = -1;
		LowHigh cmp = LowHigh(17, 61);

		// set bots' initial values
		for (const auto& s : sets)
			set_value(bots, s, cmp, cmp_bot);
		
		while (1)
		{
			// find bot having two microchips
			auto bit = bots.begin();
			while (bit != bots.end() && bit->second.high == -1)
				bit++;

			// no more bots? --> end of work
			if (bit == bots.end())
				break;
			
			// find move instruction for this bot
			auto mit = moves.find(bit->first);

			// process low
			const auto& low = mit->second.low;
			if (low.target == 'b')
				set_value(bots, SetIns(low.index, bit->second.low), cmp, cmp_bot);
			else
				outputbin[low.index] = bit->second.low;

			// process high
			const auto& high = mit->second.high;
			if (high.target == 'b')
				set_value(bots, SetIns(high.index, bit->second.high), cmp, cmp_bot);
			else
				outputbin[high.index] = bit->second.high;

			// source both has no chips now
			bit->second = LowHigh(-1, -1);
		}

		// done!
		return make_pair(cmp_bot, outputbin[0] * outputbin[1] * outputbin[2]);
	}
}
