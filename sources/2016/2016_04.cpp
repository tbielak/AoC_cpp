#include "2016_04.h"

namespace Day04_2016
{
	class Room
	{
	public:
		Room(const string& input)
		:	decoy(false)
		{
			size_t pos = input.find_last_of('-');
			name = input.substr(0, pos);
			
			string s = input.substr(pos + 1);
			pos = s.find_first_of('[');
			sectorID = stoi(s.substr(0, pos));
			checksum = s.substr(pos + 1, 5);
		}

		bool decoy;
		string name;
		int sectorID;
		string checksum;
	};

	typedef vector<Room> t_rooms;

	bool check_if_decoy(const Room& r)
	{
		typedef map<char, int> t_charmap;
		t_charmap charmap;
		for (auto c : r.name)
			if (c != '-')
				charmap[c]++;

		typedef map<int, string> t_countmap;
		t_countmap countmap;
		for (const auto & c : charmap)
			countmap[c.second] += c.first;

		for (auto& x : countmap)
			sort(x.second.begin(), x.second.end());

		string checksum;
		for (t_countmap::const_reverse_iterator it = countmap.rbegin(); it != countmap.rend(); it++)
		{
			checksum += it->second;
			if (checksum.size() > 5)
				break;
		}

		return checksum.substr(0, 5) != r.checksum;
	}
	
	void find_decoys(t_rooms& rooms)
	{
		for (auto& r : rooms)
			if (check_if_decoy(r))
				r.decoy = true;
	}

	int part_one(const t_rooms& rooms)
	{
		int sum = 0;
		for (auto& r : rooms)
			if (!r.decoy)
				sum += r.sectorID;

		return sum;
	}

	int part_two(const t_rooms& rooms)
	{
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

	t_output main(const t_input& input)
	{
		t_rooms rooms;
		for (const auto& s : input)
			rooms.push_back(Room(s));

		auto t0 = chrono::steady_clock::now();
		find_decoys(rooms);
		auto p1 = part_one(rooms);
		auto p2 = part_two(rooms);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
