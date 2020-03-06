#include <iostream>
#include <list>


using namespace std;

void findInsert(list<string>& ls, const string& toFind, const string& toAdd)
{


    for(auto curr = ls.begin(); curr != ls.end(); curr++)//postfix matters
    {
        if(*curr == toFind)
        {
            advance(curr, 1);
            curr = ls.insert(curr, toAdd);
            return;
        }
    }


}

int main()
{
  list<string> ls{"one", "two", "three", "four", "five"};

    findInsert(ls, "five", "3,14");

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


















