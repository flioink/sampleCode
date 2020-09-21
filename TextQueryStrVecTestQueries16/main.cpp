#include <iostream>
#include "TextQuery.h"
#include "Query.h"

using namespace std;

int main()
{
    ifstream file("D:\\DL\\orgasmatron.txt");
    if(!file)cout << "Error";

    while(true)
    {
        string s1, s2;

        cout << "Enter string: ";
        cin >> s1 >> s2;

        Query q1 = Query(s1) & Query(s2);
        const QueryResult qr = q1.eval(file);

        print(cout, qr);
    }
}
