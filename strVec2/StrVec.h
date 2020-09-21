#ifndef STRVEC_H_INCLUDED
#define STRVEC_H_INCLUDED

#include <memory>

using std::string;
using std::pair;
using std::allocator;
using std::initializer_list;

class StrVec
{
    friend bool operator==(const StrVec&, const StrVec&);
    friend bool operator!=(const StrVec&, const StrVec&);
    friend bool operator<(const StrVec&, const StrVec&);
    friend bool operator>(const StrVec&, const StrVec&);
    friend bool operator<=(const StrVec&, const StrVec&);
    friend bool operator>=(const StrVec&, const StrVec&);
public:
    StrVec():elements(nullptr), firstFree(nullptr), cap(nullptr){}
    StrVec(initializer_list<string> il);
    StrVec(const StrVec& rhs);
    StrVec& operator=(const StrVec& rhs);
    StrVec(StrVec&& rhs)noexcept;
    StrVec& operator=(StrVec&& rhs)noexcept;
    ~StrVec();

    StrVec& operator=(initializer_list<string> il);

    size_t size()const{return firstFree - elements;}
    size_t capacity()const{return cap - elements;}
    string* begin()const{return elements;}
    string* end()const{return firstFree;}
    string& at(size_t pos){return *(elements + pos);}

    void push_back(const string& s);

    void reserve(size_t newCap);
    void resize(size_t cnt);
    void resize(size_t cnt, const string& s);

private:
    pair<string*, string*> allocAndCopy(const string* b, const string* e);
    void checkAlloc(){if(size() == capacity()) reallocate();}
    void reallocate();
    void free();
    void allocAndMove(size_t newCap);
    void rangeInit(const string* first, const string* last);

    string* elements;
    string* firstFree;
    string* cap;
    allocator<string> alloc;
};

bool operator==(const StrVec&, const StrVec&);
bool operator!=(const StrVec&, const StrVec&);
bool operator<(const StrVec&, const StrVec&);
bool operator>(const StrVec&, const StrVec&);
bool operator<=(const StrVec&, const StrVec&);
bool operator>=(const StrVec&, const StrVec&);


#endif // STRVEC_H_INCLUDED
