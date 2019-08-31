#include <iostream>
#include "Ring.h"

using namespace std;

int main()
{
    Ring<string> texts{"one", "two", "three", "four"};//Initializer list in constructor uses curly brackets

    texts.add("five");

    for(auto &it: texts)
    {
        cout << it << endl;
    }

    return 0;
}
