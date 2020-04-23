#include "TextQuery.h"

    String::String(const char* c1)
    {
        auto c2 = const_cast<char*> (c1);
        while(*c2)
        {
            ++c2;
        }
        rangeInit(c1, ++c2);
    }

    String::String(const String& rhs)
    {
        rangeInit(rhs.begin(), rhs.end());
    }

    String& String::operator=(const String& rhs)
    {
        if(this != &rhs)
        {
            auto newData = allocAndCopy(rhs.begin(), rhs.end());
            free();
            elements = newData.first;
            firstFree = cap = newData.second;
            lastElem = firstFree - 1;
        }
        return* this;
    }

    String::String(String&& rhs)noexcept
    {
            elements = rhs.elements;
            lastElem = rhs.lastElem;
            firstFree = rhs.firstFree;
            cap = rhs.cap;
            rhs.elements = rhs.lastElem = rhs.firstFree = rhs.cap = nullptr;
    }

    String& String::operator=(String&& rhs)noexcept
    {
        if(this != &rhs)
        {
            free();
            elements = rhs.elements;
            lastElem = rhs.lastElem;
            firstFree = rhs.firstFree;
            cap = rhs.cap;
            rhs.elements = rhs.lastElem = rhs.firstFree = rhs.cap = nullptr;
        }
        return* this;

    }

    String::~String()
    {
        free();
    }

    void String::push_back(const char c)
    {
        checkAlloc();
        *lastElem = c;
        lastElem = firstFree;
        alloc.construct(firstFree++, '\0');
    }

    void String::reserve(size_t newCap)
    {
        if(newCap <= capacity())return;
        allocAndMove(newCap);
    }

    void String::resize(size_t cnt)
    {
        resize(cnt, ' ');
    }

    void String::resize(size_t cnt, const char c)
    {
        if(cnt > size())
        {
            if(cnt > capacity())reserve(2*size());
            for(size_t i = size(); i != cnt + 1; ++i)
            {
                *lastElem = c;
                alloc.construct(firstFree++, '\0');
            }

        }
        else if(cnt < capacity())
        {
            while(lastElem != elements + cnt)
            {
                --lastElem;
                alloc.destroy(--firstFree);
            }
            *lastElem = '\0';
        }

    }

    pair<char*, char*> String::allocAndCopy(const char* b, const char* e)
    {
        auto newData = alloc.allocate(e - b);
        return {newData, std::uninitialized_copy(b, e, newData)};
    }

    void String::reallocate()
    {

    }

    void String::free()
    {
        std::for_each(elements, lastElem, [this](char& c){alloc.destroy(&c);});
        alloc.deallocate(elements, cap - elements);
    }

    void String::allocAndMove(size_t newCap)
    {
        auto newData = alloc.allocate(newCap);
        auto dest = newData;
        auto elem = elements;
        for(size_t i = 0; i != size() + 1; ++i)
        {

            alloc.construct(dest++, std::move(*elem++));
        }
        free();

        elements = newData;
        firstFree = dest;
        lastElem = firstFree - 1;
        cap = elements + newCap;
    }

    void String::rangeInit(const char* first, const char* last)
    {
        auto newData = allocAndCopy(first, last);
        elements = newData.first;
        firstFree = cap = newData.second;
        lastElem = firstFree - 1;
    }

    ostream& operator<<(ostream& os, const String& rhs)
    {
        os << rhs.cStr();
        return os;
    }

    istream& operator>>(istream& is, String& rhs)
    {
        for(char c; (c = is.get())!= '\n';)
        {
            rhs.push_back(c);
        }
        return is;
    }

    bool operator==(const String& lhs, const String& rhs)
    {
        return std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    bool operator!=(const String& lhs, const String& rhs)
    {
        return !(lhs == rhs);
    }

    bool operator<(const String& lhs, const String& rhs)
    {
        return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    bool operator>(const String& lhs, const String& rhs)
    {
        return rhs < lhs;
    }

    bool operator>=(const String& lhs, const String& rhs)
    {
        return !(rhs < lhs);
    }

    bool operator<=(const String& lhs, const String& rhs)
    {
        return !(lhs < rhs);
    }

///////////////////////////////////////////////////////////////


    StrVec::StrVec(initializer_list<String> il)
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
            auto newData = allocAndCopy(rhs.begin(), rhs.end());
            free();
            elements = newData.first;
            firstFree = cap = newData.second;
        }
        return* this;
    }

    StrVec::StrVec(StrVec&& rhs)noexcept
    :elements(rhs.elements), firstFree(rhs.firstFree), cap(rhs.cap)
    {
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

    void StrVec::push_back(const String& s)
    {
        checkAlloc();
        alloc.construct(firstFree++, s);
    }

    void StrVec::reserve(size_t newCap)
    {
        if(newCap < capacity())return;
        allocAndMove(newCap);
    }

    void StrVec::resize(size_t cnt)
    {
        resize(cnt, String());
    }

    void StrVec::resize(size_t cnt, const String& s)
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

    pair<String*, String*> StrVec::allocAndCopy(const String* b, const String* e)
    {
        auto newData = alloc.allocate(e - b);
        return{newData, std::uninitialized_copy(b, e, newData)};
    }

    void StrVec::reallocate()
    {
        size_t newCap = size() ? 2*size() : 1;
        allocAndMove(newCap);
    }

    void StrVec::free()
    {
        std::for_each(elements, firstFree, [this](String& s){alloc.destroy(&s);});
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

    void StrVec::rangeInit(const String* first, const String* last)
    {
        auto newData = allocAndCopy(first, last);
        elements = newData.first;
        firstFree = cap = newData.second;
    }

    TextQuery::TextQuery(ifstream& ifs):input(new StrVec)
    {
        size_t lineNo{0};
        for(String line; ifs >> line; ++lineNo)
        {
            stringstream lineStr(line);
        }
    }

    QueryResult TextQuery::query(const String& s)const
    {

    }

    ostream& print(ostream& os, const QueryResult& qr)
    {

    }
