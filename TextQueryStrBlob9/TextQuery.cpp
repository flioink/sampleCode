#include "TextQuery.h"

StrBlobPtr StrBlob::begin()
{
    return StrBlobPtr(*this);
}

StrBlobPtr StrBlob::end()
{
    return StrBlobPtr(*this, data->size());
}

TextQuery::TextQuery(ifstream& ifs)
{
    StrBlob::size_type lineNo{0};

    for(string line; getline(ifs, line); ++lineNo)
    {
        stringstream lineStr(line);
        input.push_back(line);
        for(string text, word; lineStr >> text; word.clear())
        {
            remove_copy_if(text.begin(), text.end(), back_inserter(word), ispunct);
            auto& pos = dict[word];
            if(!pos){pos.reset(new set<StrBlob::size_type>());}
            pos->insert(lineNo);
        }
    }

}

QueryResult TextQuery::query(const string& s)const
{
    static shared_ptr<set<StrBlob::size_type>> none(new set<StrBlob::size_type>());
    auto found = dict.find(s);

    if(found != dict.end())
    {
        return QueryResult(s, input, found->second);
    }
    else
    {
        return QueryResult(s, input, none);
    }
}

ostream& print(ostream& out, const QueryResult& qr)
{
    cout << qr.word << " appears on " << qr.nos->size()
    <<(qr.nos->size() == 1? " line." : " lines.") << endl;

    for(auto it = qr.begin(); it != qr.end(); ++it)
    {
        StrBlobPtr p(*qr.getFile(), *it);
        cout << "\t(line " << *it + 1 << ") " << *p << endl;
    }
}































