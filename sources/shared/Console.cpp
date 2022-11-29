#include "Console.h"

namespace AoC
{
	Console::Console()
	:   _colors_enabled(true)
	{
	}

	void Console::disable_colors()
	{
		_colors_enabled = false;
	}

	void Console::setup()
	{
		#ifdef WIN32
		if (_colors_enabled)
		{
			DWORD mode;
			HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
			::GetConsoleMode(handle, &mode);
			::SetConsoleMode(handle, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
		}
		#endif
	}
}
