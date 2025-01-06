#include "2024_24.h"

namespace Day24_2024
{
	Device::Device(const vector<string>& input)
	{
		size_t i = 0;
		for (; !input[i].empty(); i++)
			add_wire(input[i].substr(0, 3), stoi(input[i].substr(5)));

		smatch matches;
		regex regex("([0-9a-z]*) ([A-Z]*) ([0-9a-z]*) -> ([0-9a-z]*)");
		for (++i; i < input.size(); i++)
		{
			regex_search(input[i], matches, regex);
			_gates.push_back(vector<string>({ matches[1], matches[2], matches[3], matches[4] }));
			add_wire(matches[1]);
			add_wire(matches[3]);
			add_wire(matches[4]);
		}
	}

	Device& Device::simulate()
	{
		while (1)
		{
			bool all_defined = true;
			for (auto& gate : _gates)
			{
				int& output = _wires.find(gate[OUTPUT])->second;
				if (output != UNDEFINED)
					continue;

				int v1 = _wires.find(gate[INPUT1])->second;
				int v2 = _wires.find(gate[INPUT2])->second;
				if (v1 == UNDEFINED || v2 == UNDEFINED)
				{
					all_defined = false;
					continue;
				}

				if (gate[TYPE] == "AND") output = v1 & v2; else
					if (gate[TYPE] == "XOR") output = v1 ^ v2; else
						if (gate[TYPE] == "OR") output = v1 | v2;
			}

			if (all_defined)
				break;
		}

		return *this;
	}

	int64_t Device::z_wires_output()
	{
		int64_t v = 0;
		int64_t m = 1;
		for (const auto& [name, value] : _wires)
			if (name[0] == 'z')
			{
				v += m * value;
				m *= 2;
			}

		return v;
	}

	string Device::eight_wires()
	{
		string carry = find_output("x00", "AND", "y00");
		int bit = 1;
		while (bit < 45)
		{
			string n = bit > 9 ? to_string(bit) : "0" + to_string(bit);
			string x = "x" + n;
			string y = "y" + n;
			string z = "z" + n;

			string A_output = find_output(x, "XOR", y);
			string B_output = find_output(x, "AND", y);

			string C_output = find_output(A_output, "XOR", carry);
			if (C_output.empty())
			{
				swap_outputs(A_output, B_output);
				continue;
			}

			if (C_output != z)
			{
				swap_outputs(C_output, z);
				continue;
			}

			string D_output = find_output(A_output, "AND", carry);
			carry = find_output(B_output, "OR", D_output);
			bit++;
		}

		string result;
		for (const string& s : _swapped)
		{
			if (!result.empty())
				result += ",";

			result += s;
		}

		return result;
	}

	void Device::add_wire(const string& name, int value /* = UNDEFINED */)
	{
		if (_wires.find(name) == _wires.end())
			_wires[name] = value;
	}

	string Device::find_output(const string& a, const string& type, const string& b) const
	{
		for (const auto& gate : _gates)
			if ((gate[INPUT1] == a && gate[TYPE] == type && gate[INPUT2] == b) ||
				(gate[INPUT1] == b && gate[TYPE] == type && gate[INPUT2] == a))
				return gate[OUTPUT];

		return string();
	}

	void Device::swap_outputs(const string& a, const string& b)
	{
		_swapped.insert(a);
		_swapped.insert(b);

		for (auto& gate : _gates)
		{
			if (gate[OUTPUT] == a)
				gate[OUTPUT] = b;
			else
				if (gate[OUTPUT] == b)
					gate[OUTPUT] = a;
		}
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return Device(input).simulate().z_wires_output();
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return Device(input).eight_wires();
	}
}
