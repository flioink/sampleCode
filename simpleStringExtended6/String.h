#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED

#include <memory>
using std::pair;
using std::allocator;
using std::ostream;
using std::istream;

class String
{
    friend ostream& operator<<(ostream& os, const String& rhs);
    friend istream& operator>>(istream& is, String& rhs);
    friend bool operator==(const String& lhs, const String& rhs);
    friend bool operator!=(const String& lhs, const String& rhs);
    friend bool operator<(const String& lhs, const String& rhs);
    friend bool operator>(const String& lhs, const String& rhs);
    friend bool operator<=(const String& lhs, const String& rhs);
    friend bool operator>=(const String& lhs, const String& rhs);

public:
    String():String(""){}
    String(const char* c1);
    String(const String& rhs);
    String& operator=(const String& rhs);
    String(String&& rhs)noexcept;
    String& operator=(String&& rhs)noexcept;
    ~String();

    char* begin()const{return elements;}
    char* end()const{return lastElem;}
    size_t size()const{return lastElem - elements;}
    size_t capacity()const{return cap - elements;}
    size_t length()const{return size();}
    const char* cStr()const{return elements;}
    void push_back(const char c);

    void reserve(size_t newCap);
    void resize(size_t cnt);
    void resize(size_t cnt, const char c);

private:
    pair<char*, char*> allocAndCopy(const char* b, const char* e);
    void checkAlloc(){if(firstFree == cap) reallocate();}
    void reallocate();
    void free();
    void allocAndMove(size_t newCap);
    void rangeInit(const char* first, const char* last);

    char* elements;
    char* lastElem;
    char* firstFree;
    char* cap;
    allocator<char> alloc;
};

ostream& operator<<(ostream& os, const String& rhs);
istream& operator>>(istream& is, String& rhs);
bool operator==(const String& lhs, const String& rhs);
bool operator!=(const String& lhs, const String& rhs);
bool operator<(const String& lhs, const String& rhs);
bool operator>(const String& lhs, const String& rhs);
bool operator<=(const String& lhs, const String& rhs);
bool operator>=(const String& lhs, const String& rhs);


#endif // STRING_H_INCLUDED

































