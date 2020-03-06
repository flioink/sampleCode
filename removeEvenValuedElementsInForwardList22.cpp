#include <iostream>
#include <forward_list>


using namespace std;

void remNum(forward_list<int>& ls)
{


    for(auto curr = ls.begin(), prev = ls.before_begin(); curr != ls.end();)
    {
        if(*curr % 2)
        {
            curr = ls.insert_after(prev, *curr);
            advance(curr, 2);
            advance(prev, 2);
        }
        else
        {
            curr = ls.erase_after(prev);
        }
    }


}

int main()
{
  forward_list<int> ls{1,2,3,4,5,6,7,8,9};

    remNum(ls);
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


















