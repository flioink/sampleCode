#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;
using namespace std::placeholders;

bool checkSize(const string& s, string::size_type sz)
{
    return s.size() >= sz;
}

void elimDups(vector<string>& vs)
{
    sort(vs.begin(), vs.end());
    auto newEnd = unique(vs.begin(), vs.end());
    vs.erase(newEnd, vs.end());
}

void biggies(vector<string>& vs, string::size_type sz)
{
    elimDups(vs);
    auto it = stable_partition(vs.begin(), vs.end(), bind(checkSize, _1, sz));
    for_each(vs.begin(), it, [](const string& s)
             {cout << s << " ";});
}

int main()
{
    vector<string> vec{"one","two","three","four","five"};

    biggies(vec, 4);

}

