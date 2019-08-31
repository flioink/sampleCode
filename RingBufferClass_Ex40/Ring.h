#ifndef RING_H_INCLUDED
#define RING_H_INCLUDED

#include <memory>
#include <initializer_list>


template <typename T>
class Ring
{
private:
    int _size{0};
    int _pos{0};
    std::unique_ptr<T[]> _values{nullptr};

public:

    class iterator;

    Ring(std::initializer_list<T> ls): _size(ls.size()), _values(new T[_size])
    {
        int i = 0;

        for(typename std::initializer_list<T>::iterator it = ls.begin(); it != ls.end(); it++)
        {
            _values[i++] = *it;
        }
    }

    Ring(int size): _size(size), _values(new T[_size])
    {

    }

    iterator begin()
    {
        return iterator(0, *this);
    }

    iterator end()
    {
        return iterator(_size, *this);
    }

    int size()
    {
        return _size;
    }

    T& get(int pos)
    {
        return _values[pos];
    }

    void add(T value)
    {
        _values[_pos++] = value;

        if(_pos == _size)
        {
            _pos = 0;
        }
    }

};

template <typename T>
class Ring<T>::iterator
{
private:
    int _pos{0};
    Ring& _ring{nullptr};

public:

    iterator(int pos, Ring& aRing): _pos(pos), _ring(aRing)
    {

    }

    iterator& operator++()
    {
        ++_pos;
        return* this;
    }

    iterator& operator++(int)
    {
        _pos++;
        return* this;
    }

    T& operator*()
    {
        return _ring.get(_pos);
    }

    bool operator!=(const iterator& other)const
    {
        return _pos != other._pos;
    }
};


#endif // RING_H_INCLUDED
