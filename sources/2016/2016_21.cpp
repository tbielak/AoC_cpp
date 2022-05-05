#include "2016_21.h"

namespace Day21_2016
{
	Operation::Operation(enum Command cmd, int x, int y)
	:	cmd(cmd), x(x), y(y), cx(0), cy(0)
	{
	}

	Operation::Operation(enum Command cmd, char cx, char cy)
	:	cmd(cmd), x(0), y(0), cx(cx), cy(cy)
	{
	}

	string Main::get_word(string& s, int skip /* = 0 */)
	{
		string w;
		for (int i = 0; i <= skip; i++)
		{
			size_t pos = s.find_first_of(' ');
			if (pos == string::npos)
			{
				w = s;
				s = "";
			}
			else
			{
				w = s.substr(0, pos);
				s = s.substr(pos + 1);
			}
		}

		return w;
	}

	t_operations Main::load(const vector<string>& input)
	{
		t_operations operations;

		for (auto s : input)
		{
			string w = get_word(s);
			if (w == "move")
			{
				string x = get_word(s, 1);
				string y = get_word(s, 2);
				operations.push_back(Operation(Command::move_position, stoi(x), stoi(y)));
			}
			else
			if (w == "reverse")
			{
				string x = get_word(s, 1);
				string y = get_word(s, 1);
				operations.push_back(Operation(Command::reverse_positions, stoi(x), stoi(y)));
			}
			else
			if (w == "rotate")
			{
				w = get_word(s);
				if (w == "based")
				{
					string cx = get_word(s, 4);
					operations.push_back(Operation(Command::rotate_based, cx[0], '?'));
				}
				else
				{
					string x = get_word(s);
					operations.push_back(Operation(w == "left" ? Command::rotate_left : Command::rotate_right, stoi(x), 0));
				}
			}
			else
			if (w == "swap")
			{
				w = get_word(s);
				if (w == "letter")
				{
					string cx = get_word(s);
					string cy = get_word(s, 2);
					operations.push_back(Operation(Command::swap_letter, cx[0], cy[0]));
				}
				else
				{
					string x = get_word(s);
					string y = get_word(s, 2);
					operations.push_back(Operation(Command::swap_position, stoi(x), stoi(y)));
				}
			}
		}

		return operations;
	}

	string Main::scramble(string password, const t_operations& operations)
	{
		for (const auto& op : operations)
		{
			switch (op.cmd)
			{
				case Command::swap_position:
				{
					swap(password[op.x], password[op.y]);
					break;
				}

				case Command::swap_letter:
				{
					for (int i = 0; i < (int)password.size(); i++)
					{
						if (password[i] == op.cx)
							password[i] = op.cy;
						else
						if (password[i] == op.cy)
							password[i] = op.cx;
					}

					break;
				}

				case Command::rotate_left:
				{
					rotate(password.begin(), password.begin() + (op.x % password.size()), password.end());
					break;
				}

				case Command::rotate_right:
				{
					rotate(password.rbegin(), password.rbegin() + (op.x % password.size()), password.rend());
					break;
				}

				case Command::rotate_based:
				{
					int idx = (int)password.find_first_of(op.cx);
					int count = (((idx >= 4) ? 2 : 1) + idx) % int(password.size());
					rotate(password.rbegin(), password.rbegin() + count, password.rend());
					break;
				}

				case Command::reverse_positions:
				{
					string target = password;
					int begin = op.y + op.x;
					for (int i = op.x; i <= op.y; i++)
						target[i] = password[begin - i];

					password = target;
					break;
				}

				case Command::move_position:
				{
					char letter = password[op.x];
					password.erase(op.x, 1);
					password.insert(password.begin() + op.y, letter);
					break;
				}
			}
		}

		return password;
	}
	
	AoC::Output Main::part_one(const vector<string>& input)
	{
		return scramble("abcdefgh", load(input));
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		t_operations operations = load(input);

		string password = "abcdefgh";
		string scrambled;
		do
		{
			scrambled = scramble(password, operations);
		} while (scrambled != "fbgdceah" && next_permutation(password.begin(), password.end()));

		return password;
	}
}
