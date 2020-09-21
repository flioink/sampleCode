#include "TextQuery.h"
//#include <iostream>
#include <sstream>

TextQuery::TextQuery(ifstream& ifs):input(std::make_shared<vector<string>>())
{
    string line;
    while(getline(ifs, line))
    {
        input->push_back(line);
        std::istringstream lineStr(line);
        size_t n = input->size() - 1;
        string word;

        while(lineStr >> word)
        {
            word = cleanupStr(word);
            auto& pos = wm[word];
            if(!pos){pos.reset(new set<lineNo>);}
            pos->insert(n);
        }
    }
}

QueryResult TextQuery::query(const string& s)const
{
    static shared_ptr<set<lineNo>> nodata(new set<lineNo>);

    auto found = wm.find(s);

    if(found != wm.end())
    {
        return QueryResult(s, input, (*found).second);
    }
    else
    {
        return QueryResult(s, input, nodata);
    }
}

string TextQuery::cleanupStr(const string& s)
{
    string tmp{""};

    for(auto it = s.begin(); it != s.end(); ++it)
    {
        if(!ispunct(*it))
        {
            tmp += tolower(*it);
        }
    }
    return tmp;
}

ostream& print(ostream& os, const QueryResult& qr)
{
    os << qr.word << " appears on " << qr.nos->size()
    << " " << (qr.nos->size() == 1 ? "line." : "lines.") << std::endl;

    for(auto i : *qr.nos)
    {
        os << "\t(line " << i + 1 << ") " << qr.in->at(i) << std::endl;
    }
    return os;
}

