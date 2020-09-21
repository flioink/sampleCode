#include "StrVec.h"
#include <algorithm>


    StrVec::StrVec(initializer_list<string> il)
    {
        rangeInit(il.begin(), il.end());
    }

    StrVec::StrVec(const StrVec& rhs)
    {
        rangeInit(rhs.begin(), rhs.end());
    }

    StrVec& StrVec::operator=(const StrVec& rhs)
    {
        if(this != &rhs)
        {
            free();
            auto newData = allocAndCopy(rhs.begin(), rhs.end());
            elements = newData.first;
            firstFree = cap = newData.second;
        }
        return* this;
    }

    StrVec::StrVec(StrVec&& rhs)noexcept
    {
        elements = rhs.elements;
        firstFree = rhs.firstFree;
        cap = rhs.cap;
        rhs.elements = rhs.firstFree = rhs.cap = nullptr;
    }

    StrVec& StrVec::operator=(StrVec&& rhs)noexcept
    {
        if(this != &rhs)
        {
            free();
            elements = rhs.elements;
            firstFree = rhs.firstFree;
            cap = rhs.cap;
            rhs.elements = rhs.firstFree = rhs.cap = nullptr;
        }
        return* this;
    }

    StrVec::~StrVec()
    {
        free();
    }

    StrVec& StrVec::operator=(initializer_list<string> il)
    {
        //*this = StrVec(il);
        free();
        auto newData = allocAndCopy(il.begin(), il.end());
        elements = newData.first;
        firstFree = cap = newData.second;
        return* this;
    }

    void StrVec::push_back(const string& s)
    {
        checkAlloc();
        alloc.construct(firstFree++, s);
    }

    void StrVec::reserve(size_t newCap)
    {
        if(newCap <= capacity())return;
        allocAndMove(newCap);
    }

    void StrVec::resize(size_t cnt)
    {
        resize(cnt, string());
    }

    void StrVec::resize(size_t cnt, const string& s)
    {
        if(cnt > size())
        {
            if(cnt > capacity())reserve(2* cnt);
            for(size_t i = size(); i != cnt; ++i)
            {
                alloc.construct(firstFree++, s);
            }
        }
        else if(cnt < size())
        {
            while(firstFree != elements + cnt)
            {
                alloc.destroy(--firstFree);
            }
        }

    }

    pair<string*, string*> StrVec::allocAndCopy(const string* b, const string* e)
    {
        auto newData = alloc.allocate(e - b);
        return {newData, std::uninitialized_copy(b, e, newData)};

    }

    void StrVec::reallocate()
    {
        size_t newCap = size() ? 2*size() : 1;
        allocAndMove(newCap);
    }

    void StrVec::free()
    {
        std::for_each(elements, firstFree, [this](string& s){alloc.destroy(&s);});
        alloc.deallocate(elements, cap - elements);
    }

    void StrVec::allocAndMove(size_t newCap)
    {
        auto newData = alloc.allocate(newCap);
        auto dest = newData;
        auto elem = elements;

        for(size_t i = 0; i != size(); ++i)
        {
            alloc.construct(dest++, std::move(*elem++));
        }
        free();

        elements = newData;
        firstFree = dest;
        cap = elements + newCap;
    }

    void StrVec::rangeInit(const string* first, const string* last)
    {
        auto newData = allocAndCopy(first, last);
        elements = newData.first;
        firstFree = cap = newData.second;
    }

    bool operator==(const StrVec& lhs, const StrVec& rhs)
    {
        return lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    bool operator!=(const StrVec& lhs, const StrVec& rhs)
    {
        return !(lhs == rhs);
    }
    bool operator<(const StrVec& lhs, const StrVec& rhs)
    {
        return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    bool operator>(const StrVec& lhs, const StrVec& rhs)
    {
        return rhs < lhs;
    }

    bool operator<=(const StrVec& lhs, const StrVec& rhs)
    {
        return !(rhs < lhs);
    }

    bool operator>=(const StrVec& lhs, const StrVec& rhs)
    {
        return !(lhs < rhs);
    }
