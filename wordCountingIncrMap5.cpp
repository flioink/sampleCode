#include <iostream>
#include <map>

using namespace std;

int main()
{
    string s;

    map<string, size_t> mp;

    int j = 4;

    while(j--)
    {
        cout << "Enter a string: ";
        cin >> s;

        pair<map<string, size_t>::iterator, bool> entry = mp.insert({s, 1});

        if(!entry.second)
        {
            ++entry.first->second;
        }

    }
    for(auto& it: mp)
    {
        cout << it.first << " " << it.second << endl;
    }

}
