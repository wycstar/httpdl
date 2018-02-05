#include "Config.h"

using namespace std;

Config::Config(string filename, string delimiter,string comment):
    _delimiter(delimiter),
    _comment(comment)
{
    std::ifstream in(filename.c_str());
    if (!in) THROW_SYSTEM_ERROR();
    in >> (*this);
}

Config::Config():
    _delimiter(string(1, '=')), _comment(string(1, '#'))
{
    
}

bool Config::is_key_exist(const string& key) const
{
    CONST_MAP_ITERATOR p = _contents.find(key);
    return (p != _contents.end());
}

void Config::trim(string& inout_s)
{
    static const char whitespace[] = " \n\t\v\r\f";
    inout_s.erase(0, inout_s.find_first_not_of(whitespace));
    inout_s.erase(inout_s.find_last_not_of(whitespace) + 1U);
}

std::ostream& operator<<(std::ostream& os, const Config& cf)
{
    for (CONST_MAP_ITERATOR p = cf._contents.begin(); p != cf._contents.end(); ++p)
    {
        os << p->first << " " << cf._delimiter << " ";
        os << p->second << std::endl;
    }
    return os;
}

void Config::remove(const string& key)
{
    _contents.erase(_contents.find(key));
    return;
}

std::istream& operator>>(std::istream& is, Config& cf)
{
    using pos = string::size_type;
    const string& delim = cf._delimiter;
    const string& comm = cf._comment;
    const pos skip = delim.length();

    string nextline = "";

    while (is || nextline.length() > 0)
    {
        string line;
        if (nextline.length() > 0)
        {
            line = nextline;
            nextline = "";
        }
        else
        {
            std::getline(is, line);
        }
        line = line.substr(0, line.find(comm));
        pos delimPos = line.find(delim);
        if (delimPos < string::npos)
        {
            string key = line.substr(0, delimPos);
            line.replace(0, delimPos + skip, "");
            bool terminate = false;
            while (!terminate && is)
            {
                std::getline(is, nextline);
                terminate = true;

                string nlcopy = nextline;
                Config::trim(nlcopy);
                if (nlcopy == "") continue;

                nextline = nextline.substr(0, nextline.find(comm));
                if (nextline.find(delim) != string::npos)
                    continue;

                nlcopy = nextline;
                Config::trim(nlcopy);
                if (nlcopy != "") line += "\n";
                line += nextline;
                terminate = false;
            }
            Config::trim(key);
            Config::trim(line);
            cf._contents[key] = line;
        }
    }
    return is;
}
bool Config::is_exist(std::string filename)
{
    bool exist = false;
    std::ifstream in(filename.c_str());
    if (in) exist = true;
    return exist;
}

void Config::read_file(string filename, string delimiter, string comment)
{
    _delimiter = delimiter;
    _comment = comment;
    std::ifstream in(filename.c_str());
    if (!in) THROW_SYSTEM_ERROR();
    in >> (*this);
}