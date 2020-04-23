#include <iostream>
#include "SalesData.h"

using namespace std;

int main()
{
    string strCp5("C++ Primer 5th");
    SalesData cp5;
    cp5 = strCp5;
    cout << cp5 << std::endl;

    return 0;
}
