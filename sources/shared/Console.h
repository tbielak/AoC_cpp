#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include "stl.h"

// Coloring via escape sequences works fine in Linux out of the box.
// In Windows we have to enable it.
//
// See setup() below -> enabling Console Virtual Terminal Sequences in Windows.
// Feature supported by cmd.exe and conhost.exe starting from Windows 10 TH2 v1511.

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include "Windows.h"
#endif

namespace AoC
{
    class Console
    {
    public:
        Console();
        void disable_colors();
        void setup();

        template <class T> Console& operator<<(const T& data)
        {
            stringstream ss;
            ss << data;
            string s = ss.str();
            for (size_t i = 0; i < _colors.size(); i++)
            {
                while (1)
                {
                    size_t pos = s.find(_colors[i]);
                    if (pos == string::npos)
                        break;

                    s.erase(pos, 3);
                    if (_colors_enabled)
                        s.insert(pos, _escapes[i]);
                }
            }

            cout << s;
            return *this;
        }

        Console& operator<<(ostream& (*manipulator)(ostream&))
        {
            cout << manipulator;
            return *this;
        }

    private:
        bool _colors_enabled;
        const vector<string> _colors = { "{d}", "{y}", "{w}", "{g}", "{r}" };
        const vector<string> _escapes = { "\033[0m", "\x1B[93m", "\x1B[97m", "\x1B[92m", "\x1B[91m" };
    };
}

#endif
