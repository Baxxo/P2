#include "MyVector.h"


template<class T>
MyVector<T>::MyVector(T *p, unsigned int sz)
{

}

template<class T>
MyVector<T>::~MyVector()
{
    delete[] v;
}

template<class T>
unsigned int MyVector<T>::getSize() const
{
    return size;
}

template<class T>
T &MyVector<T>::operator[](unsigned int i) const
{
    return v[i];
}

template<class T>
typename MyVector<T>::Iterator MyVector<T>::begin()
{
    return v;
}

template<class T>
typename MyVector<T>::Iterator MyVector<T>::end()
{
    return v[size-1];
}

template<class T>
bool MyVector<T>::add(const T &o)
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
