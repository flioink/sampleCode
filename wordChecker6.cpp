#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <functional>

using namespace std;
using namespace std::placeholders;

string& punctStrip(string& s);
int wordCnt(const string& toFind, const string& s, int& n);

int main()
{
    ifstream ifs("masterText.txt");

    if(!ifs)
    {
        cout << "File access error!" << endl;
    }

    vector<string>vs;
    string line;
    int cnt = 0;

    while(getline(ifs, line))
    {
        vs.push_back(punctStrip(line));
    }

    string seek = "maSTeR";

    for(auto& it: seek)
    {
        it = tolower(it);
    }

    for(auto it = vs.begin(); it != vs.end(); ++it)
    {
        cnt = wordCnt(seek, *it, cnt);
    }
    cout << cnt << endl;

}

string& punctStrip(string& s)
{
    for(auto& it: s)
    {
        it = tolower(it);
    }

    for(size_t i = 0, len = s.size(); i < len; ++i)
    {
        if(ispunct(s[i]) && s[i] != '-')
        {
            s.erase(i--, 1);
        }
    }

    return s;
}

int wordCnt(const string& toFind, const string& s, int& n)
{
    for(size_t pos = 0; pos <= s.size() - toFind.size();)
    {
        if(s[pos] == toFind[0] && s.substr(pos, toFind.size())== toFind)
        {
            pos += toFind.size();
            ++n;
        }
        else
        {
            ++pos;
        }
    }
    return n;
}
