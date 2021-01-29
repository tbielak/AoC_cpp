#include "Options.h"

namespace AoC
{
    Options::Options()
    :   colors(true), help(false), available(false), speed(false), day(-1), solution(-1)
    {
    }

    void Options::parse(int argc, char* argv[])
    {
        for (int i = 1; i < argc; i++)
        {
            string x = argv[i];
            if (x == "-c")
                colors = false;
            if (x == "-h")
                help = true;
            if (x == "-a")
                available = true;
            if (x == "-s")
                speed = true;
            if (x == "-p" && argc > i + 1)
                which_puzzle(argv[++i]);
            if (x == "-i" && argc > i + 1)
                input_filename = argv[++i];
        }
    }

    void Options::which_puzzle(const string& s)
    {
        string sday, ssol;
        size_t pos = s.find_first_of(':');
        sday = (pos == string::npos) ? s : s.substr(0, pos);
        ssol = (pos == string::npos) ? "0" : s.substr(pos + 1);
        try
        {
            day = stoi(sday);
            solution = stoi(ssol) - 1;
        }
        catch (exception&)
        {
            day = -1;
            solution = -1;
        }
    }
}
