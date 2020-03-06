#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>


using namespace std;

int main()
{
    ifstream ifs("input.txt");
    ofstream ofo("odds.txt"), ofe("evens.txt");

    istream_iterator<int>in (ifs), eof;
    ostream_iterator<int> odds(ofo, " "), evens(ofe, "\n");

    for_each(in, eof, [&odds, &evens](int i)
             { *(i%2 ? odds : evens)++ = i;});

}

