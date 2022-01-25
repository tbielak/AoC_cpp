#ifndef __2016_04__
#define __2016_04__

#include "../shared/Solution.h"

namespace Day04_2016
{
	class Room
	{
	public:
		Room(const string& input);

		bool decoy;
		string name;
		int sectorID;
		string checksum;

	private:
		void check_if_decoy();
	};

	typedef vector<Room> t_rooms;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static t_rooms load(const vector<string>& input);
	};
}

#endif
