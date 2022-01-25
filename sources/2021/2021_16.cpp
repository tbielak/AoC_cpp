#include "2021_16.h"

namespace Day16_2021
{
	Packet::Packet(const string& binary, int& pos)
	:	_value(NO_VALUE)
	{
		_version = read_bits(binary, pos, 3);
		_typeID = read_bits(binary, pos, 3);

		if (_typeID == 4)
			_value = read_value(binary, pos);
		else
			read_operator_packet(binary, pos);
	}

	int Packet::sum_version() const
	{
		return accumulate(_subpackets.begin(), _subpackets.end(), _version,
			[](int sum, const auto& s) { return sum + s.sum_version(); });
	}

	void Packet::calc()
	{
		for (auto& s : _subpackets)
			if (s._value == NO_VALUE)
				s.calc();
			
		switch (_typeID)
		{
			case 0:
				_value = 0;
				for (const auto& s : _subpackets)
					_value += s._value;
				break;

			case 1:
				_value = 1;
				for (const auto& s : _subpackets)
					_value *= s._value;
				break;

			case 2:
				_value = LLONG_MAX;
				for (const auto& s : _subpackets)
					_value = min(_value, s._value);
				break;

			case 3:
				_value = LLONG_MIN;
				for (const auto& s : _subpackets)
					_value = max(_value, s._value);
				break;

			case 5:
				_value = (_subpackets[0]._value > _subpackets[1]._value) ? 1 : 0;
				break;

			case 6:
				_value = (_subpackets[0]._value < _subpackets[1]._value) ? 1 : 0;
				break;

			case 7:
				_value = (_subpackets[0]._value == _subpackets[1]._value) ? 1 : 0;
				break;
		}
	}

	int Packet::read_bits(const string& binary, int& pos, int count)
	{
		int v = 0;
		for (int i = 0; i < count; i++)
		{
			v <<= 1;
			if (binary[pos++] == '1')
				v |= 1;
		}

		return v;
	}

	int64_t Packet::read_value(const string& binary, int& pos)
	{
		int64_t v = 0;
		int eot = 0;
		do
		{
			eot = read_bits(binary, pos, 1);
			v = v * 16 + read_bits(binary, pos, 4);
		}
		while (eot);

		return v;
	}

	void Packet::read_operator_packet(const string& binary, int& pos)
	{
		int length_type_ID = read_bits(binary, pos, 1);
		if (length_type_ID == 0)
		{
			int total_length = read_bits(binary, pos, 15);
			int sub_packets_end = pos + total_length;
			while (pos < sub_packets_end)
				_subpackets.push_back(Packet(binary, pos));
		}
		else
		{
			int number_of_subpackets = read_bits(binary, pos, 11);
			for (int i = 0; i < number_of_subpackets; i++)
				_subpackets.push_back(Packet(binary, pos));
		}
	}

	Transmission::Transmission(const string& input)
	{
		static const vector<string> hex =
		{
				"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111",
				"1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"
		};

		string binary;
		for (auto c : input)
			binary += hex[c < 'A' ? c - '0' : c - 'A' + 10];

		int pos = 0;
		while (pos < (int)binary.size())
		{
			_packets.push_back(Packet(binary, pos));
			if (binary.size() - pos < 8)
				break;	// padding at the end
		}
	}

	int Transmission::sum_version() const
	{
		return accumulate(_packets.begin(), _packets.end(), 0,
			[](int sum, const auto& p) { return sum + p.sum_version(); });
	}

	int64_t Transmission::calc()
	{
		for (auto& p : _packets)
			p.calc();

		return _packets[0].value();
	}

	AoC::Output Main::part_one(const string& input)
	{
		return Transmission(input).sum_version();
	}

	AoC::Output Main::part_two(const string& input)
	{
		return Transmission(input).calc();
	}
}
