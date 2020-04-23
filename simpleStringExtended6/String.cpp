#include "String.h"
#include <algorithm>
#include <iostream>

    String::String(const char* c1)
    {
        auto c2 = const_cast<char*>(c1);
        while(*c2)
        {
            ++c2;
        }

        rangeInit(c1, ++c2);
    }

    String::String(const String& rhs)
    {
        rangeInit(rhs.elements, rhs.firstFree);
    }

    String& String::operator=(const String& rhs)
    {
        if(this != &rhs)
        {
           free();
           auto newData = allocAndCopy(rhs.elements, rhs.firstFree);//same here, no iterators
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
            if(cnt > capacity())reserve(2* cnt);
            for(size_t i = size(); i != cnt; ++i)
            {
                *lastElem++ = c;
                alloc.construct(firstFree++, '\0');
            }
        }
        else if(cnt < size())
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
        return{newData, std::uninitialized_copy(b, e, newData)};
    }

    void String::reallocate()
    {
        size_t newCap = size() ? (2* size()) + 1 : 1;
        allocAndMove(newCap);
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
        lastElem = dest - 1;
        firstFree = dest;
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
        for(char c; (c = is.get()) != '\n';)
        {
            rhs.push_back(c);
        }
        return is;
    }

    bool operator==(const String& lhs, const String& rhs)
    {
        return lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin());
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

    bool operator<=(const String& lhs, const String& rhs)
    {
        return !(rhs < lhs);
    }

    bool operator>=(const String& lhs, const String& rhs)
    {
        return !(lhs < rhs);
    }

