#include "2023_07.h"

namespace Day07_2023
{
	Hand::Hand(const string& order, const string& input, int joker_index)
	{
		// load bid value
		bid = stoi(input.substr(6));

		// load cards, establish ordering string
		vector<int> cards;
		for (int i = 0; i < 5; i++)
		{
			size_t pos = order.find_first_of(input[i]);
			cards.push_back(int(pos));
			ordering += char(pos + 'a');
		}

		// histogram of cards
		vector<int> histogram = vector<int>(order.size(), 0);
		for (auto c : cards)
			histogram[c]++;

		// take joker into account (if its index is specified in 'order' string)
		int jokers_count = 0;
		if (joker_index != -1)
		{
			jokers_count = histogram[0];	// number of jokers
			histogram[0] = 0;		// reset them in historgram 'cause they can be any card
		}

		// sort histogram to gather type-related counts
		sort(histogram.begin(), histogram.end());

		// change histogram to string type
		string stype;
		for (int i = (int)histogram.size() - 1; i >= 0; i--)
			if (histogram[i] > 1)
				stype += char(histogram[i] + '0');

		// change string type to int type (strong factor, whithout jokersa)
		type = 0;	// nothing
		if (stype.size() > 0)
		{
			if (stype == "5") type = 6;	// Five of a kind
			if (stype == "4") type = 5;	// Four of a kind
			if (stype == "32") type = 4;	// Full house
			if (stype == "3") type = 3;	// Three of a kind
			if (stype == "22") type = 2;	// Two pair
			if (stype == "2") type = 1;	// One pair
		}

		// use jokers
		while (jokers_count > 0 && type < 6)
		{
			// make hand stronger using joker in the best way (tricky ;)
			static vector<int> new_type = { 1, 3, 4, 5, 4, 6 };
			type = new_type[type];
			jokers_count--;
		}
	}

	bool Hand::operator < (const Hand& rhs) const
	{
		return (type != rhs.type) ? type < rhs.type : ordering < rhs.ordering;
	}

	int Main::solve(const string& order, const vector<string>& input, int joker_index)
	{
		set<Hand> hands;
		for (const auto& s : input)
			hands.insert(Hand(order, s, joker_index));

		int sum = 0;
		int i = 0;
		for (const auto& h : hands)
			sum += ++i * h.bid;

		return sum;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return solve("23456789TJQKA", input, -1);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return solve("J23456789TQKA", input, 0);
	}
}
