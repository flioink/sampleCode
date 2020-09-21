#ifndef TEXTQUERY_H_INCLUDED
#define TEXTQUERY_H_INCLUDED

#include <map>
#include <set>
#include <vector>
#include <fstream>
#include <memory>
using std::vector;
using std::ostream;
using std::map;
using std::set;
using std::shared_ptr;
using std::string;
using std::ifstream;

class QueryResult;

class TextQuery
{
public:
    using lineNo = vector<string>::size_type;
    TextQuery(ifstream& ifs);
    QueryResult query(const string& s)const;
    static string cleanupStr(const string& s);
private:
    shared_ptr<vector<string>> input;
    map<string, shared_ptr<set<lineNo>>> wm;
};

class QueryResult
{
    friend ostream& print(ostream& os, const QueryResult& qr);
public:
    using lineNo = vector<string>::size_type;
    using lineIt = set<lineNo>::const_iterator;

    QueryResult(const string& s, shared_ptr<vector<string>> sv, shared_ptr<set<lineNo>> st):
    word(s), in(sv), nos(st){}

    lineIt begin(){return nos->begin();}
    lineIt end(){return nos->end();}
    set<lineNo>::size_type size()const{return nos->size();}
    shared_ptr<vector<string>> getFile(){return in;}

private:
    string word;
    shared_ptr<vector<string>> in;
    shared_ptr<set<lineNo>> nos;
};

ostream& print(ostream& os, const QueryResult& qr);

#endif // TEXTQUERY_H_INCLUDED
