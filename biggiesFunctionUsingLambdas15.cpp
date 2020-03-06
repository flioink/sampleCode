#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

void elimDups(vector<string>& vs)
{
    sort(vs.begin(), vs.end());
    auto newEnd = unique(vs.begin(), vs.end());
    vs.erase(newEnd, vs.end());
}

void biggies(vector<string>& vs, string::size_type sz)
{
    elimDups(vs);

    stable_sort(vs.begin(), vs.end(), [](const string& x, const string& y)
                {return x.size() < y.size();});
    auto it = find_if(vs.begin(), vs.end(), [sz](const string& s)
                      {return s.size() >= sz;});

    for_each(it, vs.end(), [](const string& s)
             {cout << s << " ";});
}

int main()
{
    vector<string> vec{"one","two","three","four","five"};

    biggies(vec, 4);

}

