#include <iostream>
#include <forward_list>


using namespace std;

void findInsert(forward_list<string>& ls, const string& toFind, const string& toAdd)
{
    auto prev = ls.before_begin();

    for(auto curr = ls.begin(); curr != ls.end(); prev = curr++)//postfix matters
    {
        if(*curr == toFind)
        {
            curr = ls.insert_after(curr, toAdd);
            return;
        }
    }

    prev = ls.insert_after(prev, toAdd);
}

int main()
{
    forward_list<string> ls{"one", "two", "three", "four", "five"};

    findInsert(ls, "three", "3,14");

    for(auto& it: ls)
    {
        cout << it << " ";
    }

    cout << endl;

    for(int i = 0, j = 0; i < 5; j = i++)
    {
        cout << j << " ";
    }
}


















