#include "2017_09.h"

namespace Day09_2017
{
	AoC::Output Main::both_parts(const string& input)
	{
		int level = 0;
		int score = 0;
		int count = 0;
		bool garbage = false;

		for (int i = 0; i < (int)input.size(); i++)
			switch (input[i])
			{
				case '{':
				{
					if (garbage)
						count++;
					else
					{
						level++;
						score += level;
					}

					break;
				}

				case '}':
				{
					if (garbage)
						count++;
					else
						level--;

					break;
				}

				case '<':
				{
					if (garbage)
						count++;
					else
						garbage = true;

					break;
				}

				case '>':
				{
					garbage = false;
					break;
				}

				case ',':
				{
					if (garbage)
						count++;

					break;
				}

				case '!':
				{
					i++;
					break;
				}

				default:
				{
					count++;
					break;
				}
			}
		
		return make_pair(score, count);
	}
}
