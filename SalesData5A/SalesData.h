#ifndef SALESDATA_H_INCLUDED
#define SALESDATA_H_INCLUDED

#include <iostream>
using std::string;
using std::istream;
using std::ostream;

class SalesData
{

    friend istream& operator>>(istream& is, SalesData& item);
    friend ostream& operator<<(ostream& os, const SalesData& item);
    friend SalesData operator+(const SalesData& lhs, const SalesData& rhs);

public:
    SalesData() = default;
    SalesData(const string& s):bookNo(s){}
    SalesData(const string& s, unsigned u, double p):bookNo(s), uSold(u), revenue(u*p){}
    //SalesData(const SalesData& rhs);
    SalesData(istream& is);

    SalesData& operator=(const string& s);

    SalesData& operator+=(const SalesData& rhs);

    string isbn()const{return bookNo;}

private:
    inline double avgPrice()const;
    std::string bookNo{""};
    unsigned uSold{0};
    double revenue{0.0};
};

inline double SalesData::avgPrice()const
{
    return uSold ? revenue/ uSold : 0;
}

istream& operator>>(istream& is, SalesData& item);
ostream& operator<<(ostream& os, const SalesData& item);
SalesData operator+(const SalesData& lhs, const SalesData& rhs);

#endif // SALESDATA_H_INCLUDED
