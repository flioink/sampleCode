#include "Query.h"
#include <algorithm>

QueryResult NotQuery::eval(const TextQuery& tq)const
{
    auto result = query.eval(tq);
    auto beg = result.begin(), end = result.end();
    auto sz = result.getFile()->size();
    auto retLines = std::make_shared<set<lineNo>>();

    for(size_t n = 0; n != sz; ++n)
    {
        if(beg == end || *beg != n)
        {
            retLines->insert(n);
        }
        else if(beg != end)
        {
            ++beg;
        }
    }

    return QueryResult(rep(), result.getFile(), retLines);
}

QueryResult AndQuery::eval(const TextQuery& tq)const
{
    auto left = lhs.eval(tq), right = rhs.eval(tq);
    auto retLines = std::make_shared<set<lineNo>>();

    std::set_intersection(left.begin(), left.end(), right.begin(), right.end(),
    std::inserter(*retLines, retLines->begin()));

    return QueryResult(rep(), left.getFile(), retLines);
}

QueryResult OrQuery::eval(const TextQuery& tq)const
{
    auto left = lhs.eval(tq), right = rhs.eval(tq);
    auto retLines = std::make_shared<set<lineNo>>(left.begin(), left.end());
    retLines->insert(right.begin(), right.end());

    return QueryResult(rep(), left.getFile(), retLines);
}
