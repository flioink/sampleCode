#include <iostream>
//#include <>

using namespace std;

class HazPtr
{
public:
    HazPtr(const string& s):ps(new string(s)), cnt(new size_t(1)), i(1){}
    HazPtr(const HazPtr& rhs):ps(rhs.ps), cnt(rhs.cnt), i(rhs.i){++cnt;}
    HazPtr& operator=(const HazPtr& rhs)
    {
        ++*cnt;
        if(--*cnt == 0)
        {
            delete ps;
            delete cnt;
        }

        ps = rhs.ps;
        cnt = rhs.cnt;
        i = rhs.i;
        return* this;
    }


    ~HazPtr()
    {
        if(--*cnt == 0)
        {
            delete ps;
            delete cnt;
        }
    }
private:
    string* ps;
    size_t* cnt;
    int i;
};

int main()
{

}
