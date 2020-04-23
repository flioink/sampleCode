#include "TextQuery.h"
#include <iostream>



int main()
{
    StrVec sVec1;
    String S1 = "Hello";
    String S2 = "My";
    String S3 = "Custom";
    String S4 = "Classes";

    sVec1.push_back(S1);
    sVec1.push_back(S2);
    sVec1.push_back(S3);
    sVec1.push_back(S4);


    for(auto& it: sVec1)
    {
        cout << it << " ";
    }

}

