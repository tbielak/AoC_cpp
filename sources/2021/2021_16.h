#ifndef __2021_16__
#define __2021_16__

#include "../shared/input_output.h"

namespace Day16_2021
{
	const int64_t NO_VALUE = -1;

	class Packet
	{
	public:
		Packet(const string& binary, int& pos);

		int sum_version() const;
		void calc();

		int64_t value() const { return _value; }

	private:
		int _version;
		int _typeID;
		int64_t _value;
		vector<Packet> _subpackets;

		int read_bits(const string& binary, int& pos, int count);
		int64_t read_value(const string& binary, int& pos);
		
		void read_operator_packet(const string& binary, int& pos);
	};

	class Transmission
	{
	public:
		Transmission(const string& input);
		
		int sum_version() const;
		int64_t calc();

	private:
		vector<Packet> _packets;
	};

	t_output main(const t_input& input);
}

#endif
