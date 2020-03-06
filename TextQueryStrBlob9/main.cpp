#include <iostream>
#include "TextQuery.h"

using namespace std;

int main()
{
    ifstream ifs("D:\\DL\\masterText.txt");

    TextQuery tq(ifs);

    while(true){
    string s;
    cout << "Enter the word to look for or press q to quit: ";
    if(!(cin >> s) || s == "q")break;
    print(cout, tq.query(s));

    }

    return 0;
}
