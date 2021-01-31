#include "2015_12.h"

namespace Day12_2015
{
	JSONEntity::JSONEntity()
		: _kind(JSONEntityKind::ent_unknown), _numberValue(0)
	{
	}

	JSONEntity::~JSONEntity()
	{
		for (auto& p : _object)
			delete p.second;

		for (auto& x : _array)
			delete x;
	}

	void JSONEntity::load(const string& input)
	{
		load_value(input, 0);
	}

	size_t JSONEntity::load_string(const string& input, string& output, size_t pos)
	{
		size_t end = input.find('\"', pos + 1);
		output = input.substr(pos + 1, end - pos - 1);
		return end + 1;
	}

	size_t JSONEntity::load_number(const string& input, int& output, size_t pos)
	{
		size_t end = pos + 1;
		while (input[end] >= '0' && input[end] <= '9') end++;
		output = stoi(input.substr(pos, end - pos));
		return end;
	}

	size_t JSONEntity::load_value(const string& input, size_t pos)
	{
		if (input[pos] == '{')
			pos = load_object(input, pos + 1);
		else
			if (input[pos] == '[')
				pos = load_array(input, pos + 1);
			else
				if ((input[pos] >= '0' && input[pos] <= '9') || input[pos] == '-')
				{
					_kind = JSONEntityKind::ent_number;
					pos = load_number(input, _numberValue, pos);
				}
				else
				{
					_kind = JSONEntityKind::ent_string;
					pos = load_string(input, _stringValue, pos);
				}

		return pos;
	}

	size_t JSONEntity::load_object(const string& input, size_t pos)
	{
		_kind = JSONEntityKind::ent_object;
		while (input[pos] != '}')
		{
			if (input[pos] == ',')
				pos++;
			else
			{
				string name;
				pos = load_string(input, name, pos);
				_object.push_back(t_JSONPair(move(name), new JSONEntity()));
				pos = _object.back().second->load_value(input, pos + 1);
			}
		}

		return pos + 1;
	}

	size_t JSONEntity::load_array(const string& input, size_t pos)
	{
		_kind = JSONEntityKind::ent_array;
		while (input[pos] != ']')
		{
			if (input[pos] == ',')
				pos++;
			else
			{
				_array.push_back(new JSONEntity());
				pos = _array.back()->load_value(input, pos);
			}
		}

		return pos + 1;
	}

	int recursive_add_numbers(const JSONEntity& json, bool ignore_red)
	{
		int sum = 0;
		switch (json.kind())
		{
		case JSONEntityKind::ent_object:
		{
			if (ignore_red)
			{
				const auto& obj = json.object();
				for (const auto& x : obj)
					if (x.second->kind() == JSONEntityKind::ent_string && x.second->stringValue() == "red")
						return 0;
			}

			for (const auto& x : json.object())
				sum += recursive_add_numbers(*x.second, ignore_red);
			break;
		}

		case JSONEntityKind::ent_array:
		{
			for (const auto& x : json.array())
				sum += recursive_add_numbers(*x, ignore_red);
			break;
		}

		case JSONEntityKind::ent_number:
		{
			sum += json.numberValue();
			break;
		}

		default:
			// intentionally left empty
			break;
		}

		return sum;
	}

	int part_one(const JSONEntity& json)
	{
		return recursive_add_numbers(json, false);
	}

	int part_two(const JSONEntity& json)
	{
		return recursive_add_numbers(json, true);
	}

	t_output main(const t_input& input)
	{
		auto t0 = chrono::steady_clock::now();
		JSONEntity json;
		json.load(input[0]);
		auto p1 = part_one(json);
		auto p2 = part_two(json);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
