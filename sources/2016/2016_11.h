#ifndef __2016_11__
#define __2016_11__

#include "../shared/Solution.h"

namespace Day11_2016
{
	// Notes on implementation:
	// We expect millions of known configurations to be cached, that's why items configuration of single floor
	// is stored as one unsigned 16-bit value. LSB (8-bits) is dedicated to microchips, MSB (8-bits) is dedicated
	// to generators. The same bit of LSB and MSB corresponds to the same element (e.g. hydrogen).
	//
	// See example diagram and 16-bit floors configuration:
	//	F4 .  .  .  .  .    0x0000	(MSB -> generators = 0x00, LSB -> microchips = 0x00)
	//	F3 .  .  .  LG .    0x0200	(MSB -> generators = 0x02, LSB -> microchips = 0x00), L bit is on (bit 1)
	//	F2 .  HG .  .  .    0x0100	(MSB -> generators = 0x01, LSB -> microchips = 0x00), H bit is on (bit 0)
	//	F1 E  .  HM .  LM   0x0003	(MSB -> generators = 0x00, LSB -> microchips = 0x03), both bits (0 and 1) are on

	typedef vector<uint16_t> t_floors;              // items on the floors
	typedef pair<t_floors, int> t_state;            // the state: <floors, elevator floor> pair
	typedef set<t_state> t_known_states;            // known states = already explored configurations

	typedef pair<t_state, int> t_state_with_step;   // state with step count
	typedef queue<t_state_with_step> t_queue;       // queue of configurations to explore

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static t_floors load(const vector<string>& input);
		static bool safe(uint16_t& cfg);
		static void do_move(uint16_t& src, uint16_t& dst, uint16_t move);
		static bool is_valid(uint16_t src, uint16_t dst, uint16_t move);
		static vector<uint16_t> find_moves(uint16_t src, uint16_t dst);
		static int solve(const t_floors& floors);
	};
}

#endif
