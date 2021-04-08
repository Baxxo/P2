#include "myvector.h"

template<class T>
MyVector::MyVector(T *p, unsigned int sz) : size(sz),v(new T[size]), capacity(sz)
{
    for(unsigned int i=0;i<size;++i){
        v[i] = new T(p);
    }
}

template<class T>
MyVector::~MyVector()
{
    delete[] v;
}

template<class T>
unsigned int MyVector::getSize() const
{
    return size;
}

template<class T>
T &MyVector::operator[](unsigned int i) const
{
    return v[i];
}

template<class T>
MyVector::Iterator MyVector::begin()
{
    return v;
}

template<class T>
MyVector::Iterator MyVector::end()
{
    return v[size-1];
}

template<class T>
bool MyVector::add(const T &o)
{
    if(capacity <= size){
        T* temp = new T[size*2];
        unsigned int i=0;
        for(;i<size;++i){
            temp[i] = v[i];
        }
        delete[] v;
        v = temp;
        v[i] = new T(o);
        return true;
    }else{
        v[size++] = new T(o);
        return true;
    }
    return false;
}
