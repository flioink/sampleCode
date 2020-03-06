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
using std::out_of_range;
using std::runtime_error;

class StrBlobPtr;

class StrBlob
{
public:
    using size_type = vector<string>::size_type;
    friend class StrBlobPtr;
    StrBlobPtr begin();
    StrBlobPtr end();

    StrBlob():data(make_shared<vector<string>>()){}
    StrBlob(initializer_list<string> il):data(make_shared<vector<string>>(il)){}
    bool empty(){return data->empty();}
    size_t size(){return data->size();}

    void push_back(const string& s){data->push_back(s);}
    void pop_back(){check(0, "pop_back on empty StrBlob"); data->pop_back();}

    string& front()const{check(0, "front on empty StrBlob"); return data->front();}
    string& back()const{check(0, "back on empty StrBlob"); return data->back();}

private:
    shared_ptr<vector<string>>data;
    void check(size_t i, const string& msg)const
    {
        if(i >= data->size())
        {
            throw out_of_range(msg);
        }
    }
};

class StrBlobPtr
{
public:
    StrBlobPtr():curr(0){}
    StrBlobPtr(const StrBlob& a, size_t sz = 0):wptr(a.data), curr(sz){}
    bool operator!=(const StrBlobPtr& other)const{return curr != other.curr;}

    string& operator*()
    {
        auto pq = check(curr, "drf past end");
        return (*pq)[curr];
    }
    StrBlobPtr& operator++(){++curr; return* this;}

private:
    weak_ptr<vector<string>> wptr;
    size_t curr;

    shared_ptr<vector<string>> check(size_t i, const string& msg)const
    {
        shared_ptr<vector<string>> ret = wptr.lock();
        if(!ret){throw runtime_error("unbound StrBlob");}
        if(i >= ret->size()){throw out_of_range(msg);}
        return ret;
    }
};

class QueryResult;

class TextQuery
{
public:
    TextQuery(ifstream& ifs);
    QueryResult query(const string& s)const;

private:
    StrBlob input;
    map<string, shared_ptr<set<StrBlob::size_type>>> dict;
};

class QueryResult
{
public:
    QueryResult(const string& s, StrBlob sb, shared_ptr<set<StrBlob::size_type>>st)
    :word(s), in(sb), nos(st){}
    friend ostream& print(ostream& out, const QueryResult& qr);
    set<StrBlob::size_type>::iterator begin()const{return nos->begin();}
    set<StrBlob::size_type>::iterator end()const{return nos->end();}

    shared_ptr<StrBlob> getFile()const{return make_shared<StrBlob>(in);}

private:
    string word;
    StrBlob in;
    shared_ptr<set<StrBlob::size_type>> nos;
};
ostream& print(ostream& out, const QueryResult& qr);

#endif // TEXTQUERY_H_INCLUDED






































