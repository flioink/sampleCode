#ifndef TEXTQUERY_H_INCLUDED
#define TEXTQUERY_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <sstream>
#include <algorithm>

using std::string;
using std::vector;
using std::shared_ptr;
using std::weak_ptr;
using std::make_shared;
using std::map;
using std::set;
using std::initializer_list;
using std::cout;
using std::endl;
using std::cin;
using std::ifstream;
using std::ostream;
using std::getline;
using std::stringstream;
using std::pair;
using std::allocator;
using std::istream;
using std::ostream;

class String
{
    friend ostream& operator<<(ostream& os, const String& rhs);
    friend istream& operator>>(istream& is, String& rhs);
    friend bool operator==(const String& lhs, const String& rhs);
    friend bool operator!=(const String& lhs, const String& rhs);
    friend bool operator<(const String& lhs, const String& rhs);
    friend bool operator>(const String& lhs, const String& rhs);
    friend bool operator>=(const String& lhs, const String& rhs);
    friend bool operator<=(const String& lhs, const String& rhs);

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

    void push_back(const char c);
    const char* cStr()const{return elements;}

    void reserve(size_t newCap);
    void resize(size_t cnt);
    void resize(size_t cnt, const char c);
private:
    pair<char*, char*> allocAndCopy(const char* b, const char* e);
    void checkAlloc(){if(capacity() == size())reallocate();}
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
bool operator>=(const String& lhs, const String& rhs);
bool operator<=(const String& lhs, const String& rhs);

class StrVec
{


public:
    StrVec():elements(nullptr), firstFree(nullptr), cap(nullptr){}
    StrVec(initializer_list<String> il);
    StrVec(const StrVec& rhs);
    StrVec& operator=(const StrVec& rhs);
    StrVec(StrVec&& rhs)noexcept;
    StrVec& operator=(StrVec&& rhs)noexcept;
    ~StrVec();

    String* begin()const{return elements;}
    String* end()const{return firstFree;}
    size_t size()const{return firstFree - elements;}
    size_t capacity()const{return cap - elements;}

    void push_back(const String& s);

    void reserve(size_t newCap);
    void resize(size_t cnt);
    void resize(size_t cnt, const String& s);

private:
    pair<String*, String*> allocAndCopy(const String* b, const String* e);
    void checkAlloc(){if(capacity() == size())reallocate();}
    void reallocate();
    void free();
    void allocAndMove(size_t newCap);
    void rangeInit(const String* first, const String* last);

    String* elements;
    String* firstFree;
    String* cap;
    allocator<String> alloc;
};
class QueryResult;

class TextQuery
{
public:
    TextQuery(ifstream& ifs);
    QueryResult query(const String& s)const;

private:
    shared_ptr<StrVec> input;
    map<String, shared_ptr<set<size_t>>> dict;
};

class QueryResult
{
public:
    QueryResult(const String& s, shared_ptr<StrVec> sv, shared_ptr<set<size_t>> st)
    :word(s), in(sv), nos(st){}
    friend ostream& print(ostream& os, const QueryResult& qr);

private:
    String word;
    shared_ptr<StrVec> in;
    shared_ptr<set<size_t>> nos;
};

ostream& print(ostream& os, const QueryResult& qr);

#endif // TEXTQUERY_H_INCLUDED
