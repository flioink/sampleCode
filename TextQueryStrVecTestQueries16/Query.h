#ifndef QUERY_H_INCLUDED
#define QUERY_H_INCLUDED

#include "TextQuery.h"

class QueryBase
{
    friend class Query;
public:
    using lineNo = TextQuery::lineNo;
    virtual ~QueryBase() = default;
private:
    virtual string rep()const = 0;
    virtual QueryResult eval(const TextQuery& tq)const = 0;
};

class Query
{
    friend Query operator~(const Query& qr);
    friend Query operator&(const Query& lhs, const Query& rhs);
    friend Query operator|(const Query& lhs, const Query& rhs);
public:
    Query(const string& s);

    string rep()const{return q->rep();}
    QueryResult eval(const TextQuery& tq)const
    {
        return q->eval(tq);
    }
private:
    shared_ptr<QueryBase> q;
    Query(shared_ptr<QueryBase> qb):q(qb){}
};
inline ostream& operator<<(ostream& os, const Query& qr)
{
    return os << qr.rep();
}

class WordQuery : public QueryBase
{
    friend class Query;

    string rep()const override
    {
        return queryWord;
    }
    QueryResult eval(const TextQuery& tq)const override
    {
        return tq.query(queryWord);
    }

    WordQuery(const string& s):queryWord(s){}

    string queryWord;
};

inline Query::Query(const string& s):q(new WordQuery(s)){}

class NotQuery : public QueryBase
{
    friend Query operator~(const Query& qr);
    string rep()const override
    {
        return "~(" + query.rep() + ")";
    }

    QueryResult eval(const TextQuery& tq)const override;

    NotQuery(const Query& qry):query(qry){}
    Query query;
};

class BinaryQuery : public QueryBase
{
protected:
    BinaryQuery(const Query& l, const Query& r, const string& s):
    lhs(l), rhs(r), opSym(s){}

    string rep()const override
    {
        return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";
    }

    Query lhs, rhs;
    string opSym;
};

class AndQuery : public BinaryQuery
{
    friend Query operator&(const Query& lhs, const Query& rhs);
    AndQuery(const Query& l, const Query& r):
    BinaryQuery(l, r, "&"){}
    QueryResult eval(const TextQuery& tq)const override;
};

class OrQuery : public BinaryQuery
{
    friend Query operator|(const Query& lhs, const Query& rhs);
    OrQuery(const Query& l, const Query& r):
    BinaryQuery(l, r, "&"){}
    QueryResult eval(const TextQuery& tq)const override;
};

inline Query operator~(const Query& qr)
{
    return shared_ptr<QueryBase>(new NotQuery(qr));
}

inline Query operator&(const Query& lhs, const Query& rhs)
{
    return shared_ptr<QueryBase>(new AndQuery(lhs, rhs));
}

inline Query operator|(const Query& lhs, const Query& rhs)
{
    return shared_ptr<QueryBase>(new OrQuery(lhs, rhs));
}

#endif // QUERY_H_INCLUDED
