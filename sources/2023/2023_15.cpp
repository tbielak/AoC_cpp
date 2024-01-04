#include "2023_15.h"

namespace Day15_2023
{
	uint8_t Main::hash(const string& input)
	{
		uint8_t c = 0;
		for (uint8_t ch : input)
			c = uint8_t((c + ch) * 17);

		return c;
	}

	pair<string, int> Main::split(const string& input)
	{
		int value = -1;
		string label;
		size_t pos = input.find("=");
		if (pos == string::npos)
		{
			label = input;
			label.pop_back();
		}
		else
		{
			label = input.substr(0, pos);
			value = stoi(input.substr(pos + 1));
		}

		return make_pair(label, value);
	}

	void Main::update(LensSlot& box, const string& label, const string& value)
	{
		for (auto& st : box)
		{
			size_t pos = st.find_first_of('=');
			if (st.substr(0, pos) == label)
			{
				st = value;
				return;
			}
		}

		box.push_back(value);
	}

	void Main::erase(LensSlot& box, const string& label)
	{
		for (auto it = box.begin(); it != box.end(); it++)
		{
			size_t pos = it->find_first_of('=');
			if (it->substr(0, pos) == label)
			{
				box.erase(it);
				break;
			}
		}
	}

	size_t Main::sum(const vector<LensSlot>& boxes)
	{
		size_t sum = 0;
		for (size_t box = 0; box < 256; box++)
			for (size_t i = 0; i < boxes[box].size(); i++)
			{
				string x = boxes[box][i];
				int fl = stoi(x.substr(x.find_first_of('=') + 1));
				sum += (box + 1) * (i + 1) * fl;
			}

		return sum;
	}

	AoC::Output Main::part_one(const string& input)
	{
		int sum = 0;
		size_t pos = 0;
		for (size_t offset = 0; pos != string::npos; offset = pos + 1)
		{
			pos = input.find(",", offset);
			sum += hash(input.substr(offset, pos - offset));
		}

		return sum;
	}

	AoC::Output Main::part_two(const string& input)
	{
		vector<LensSlot> boxes = vector<LensSlot>(256);

		size_t pos = 0;
		for (size_t offset = 0; pos != string::npos; offset = pos + 1)
		{
			pos = input.find(",", offset);
			string step = input.substr(offset, pos - offset);
			auto [label, value] = split(step);

			uint8_t box = hash(label);
			if (value > -1)
				update(boxes[box], label, step);
			else
				erase(boxes[box], label);
		}

		return sum(boxes);
	}
}
