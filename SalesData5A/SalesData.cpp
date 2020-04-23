#include "SalesData.h"

/*SalesData::SalesData(const SalesData& rhs)
{
    bookNo = rhs.bookNo;
    uSold = rhs.uSold;
    revenue = rhs.revenue;
}
*/

SalesData::SalesData(istream& is): SalesData()
{
    is >> *this;
}

istream& operator>>(istream& is, SalesData& item)
{
    double price{0.0};
    is >> item.bookNo >> item.uSold >> price;
    if(is)
    item.revenue = item.uSold * price;
    else
        item = SalesData();

    return is;
}

ostream& operator<<(ostream& os, const SalesData& item)
{
    os << item.isbn() << " " << item.uSold << " " << item.revenue;
    return os;
}

SalesData& SalesData::operator+=(const SalesData& rhs)
{
    uSold += rhs.uSold;
    revenue += rhs.revenue;
    return* this;
}

SalesData operator+(const SalesData& lhs, const SalesData& rhs)
{
    SalesData sum = lhs;
    sum += rhs;
    return sum;
}

SalesData& SalesData::operator=(const string& s)//new stuff
{
    *this = SalesData(s);
    return* this;
}
