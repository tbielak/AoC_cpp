#include "2016_04.h"

namespace Day04_2016
{
	Room::Room(const string& input)
	{
		size_t pos = input.find_last_of('-');
		name = input.substr(0, pos);
			
		string s = input.substr(pos + 1);
		pos = s.find_first_of('[');
		sectorID = stoi(s.substr(0, pos));
		checksum = s.substr(pos + 1, 5);

		check_if_decoy();
	}

	void Room::check_if_decoy()
	{
		typedef map<char, int> t_charmap;
		t_charmap charmap;
		for (auto c : name)
			if (c != '-')
				charmap[c]++;

		typedef map<int, string> t_countmap;
		t_countmap countmap;
		for (const auto& c : charmap)
			countmap[c.second] += c.first;

		for (auto& x : countmap)
			sort(x.second.begin(), x.second.end());

		string s;
		for (t_countmap::const_reverse_iterator it = countmap.rbegin(); it != countmap.rend(); it++)
		{
			s += it->second;
			if (s.size() > 5)
				break;
		}

		decoy = s.substr(0, 5) != checksum;
	}

	t_rooms Main::load(const vector<string>& input)
	{
		t_rooms rooms;
		for (const auto& s : input)
			rooms.push_back(Room(s));

		return rooms;
	}

	AoC::Output Main::part_one(const vector<string>&input)
	{
		t_rooms rooms = load(input);

		int sum = 0;
		for (const auto& r : rooms)
			if (!r.decoy)
				sum += r.sectorID;

		return sum;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		t_rooms rooms = load(input);

		for (const auto& r : rooms)
			if (!r.decoy)
			{
				int rotate_amount = r.sectorID % 26;

				string s = r.name;
				for (auto& c : s)
					if (c != '-')
						c = char(((int(c - 'a') + rotate_amount) % 26) + 'a');

				if (s == "northpole-object-storage")
					return r.sectorID;
			}

		return -1;
	}
}
