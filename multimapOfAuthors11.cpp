#include <iostream>
#include <map>
#include <set>

using namespace std;

void remBook(multimap<string, string>& m, const string& auth, const string& work);

int main()
{
    multimap<string, string> authors{
        {"G.Orwell", "1984"},
        {"G.Orwell", "Animal Farm"},
        {"C.Sagan", "DHW"},
        {"C.Sagan", "Contact"},
        {"J.Vernes", "Nemo"},
        {"J.Vernes", "JTM"}
    };
    //remBook(authors, "J.Vernes", "JTM");
    map<string, set<string>> mp;

    for(auto& it: authors)
    {
        mp[it.first].insert(it.second);
    }

    for(auto& it: mp)
    {
        cout << it.first << " : ";
        for(auto& it2: it.second)
        {
            cout << it2 << " ";
        }
        cout << endl;
    }
}

void remBook(multimap<string, string>& m, const string& auth, const string& work)
{
    auto found = m.find(auth);
    auto cnt = m.count(auth);

    while(cnt)
    {
        if(found->second == work)
        {
            m.erase(found);
        }
        --cnt;
        ++found;
    }
}
