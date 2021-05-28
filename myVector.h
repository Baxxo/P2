#ifndef MYVECTOR_H
#define MYVECTOR_H

#include "deepPtr.h"
/*
#include <iostream>
using std::cout;
using std::endl;*/

template <class T>
class MyVector
{
private:
  T* v;
  unsigned int size; //numero celle popolate
  unsigned int capacity; //dimensione totale

public:

  class Iterator
  {
    friend class MyVector;
    private:
      DeepPtr<T> ptr;
      bool pastTheEnd;

    public:
      Iterator(DeepPtr<T>* p);
      Iterator();

      DeepPtr<T>* operator ->() const;

      DeepPtr<T>& operator * () const;

      Iterator &operator++();
      Iterator operator++(int i);

      Iterator &operator--();
      Iterator operator--(int i);
      DeepPtr<T>& operator [](int i) const;

      bool operator == (const Iterator& o) const;
      bool operator != (const Iterator& o) const;
  };

  MyVector(T* p=nullptr, unsigned int sz=0);
  ~MyVector();

  MyVector(const MyVector& o);

  unsigned int getSize() const;

  Iterator begin();
  Iterator end();
  Iterator search(const DeepPtr<T>& o); //forse da mettere const

  DeepPtr<T>& operator[](unsigned int i) const;

  bool push_back(const T *o);//deve andare void
  bool pop_back(); //deve andare void

  bool remove(const T &o);

  bool isEmpty() const;
};

// --- INIZIO ITERATOR

template<class T>
MyVector<T>::Iterator::Iterator(DeepPtr<T> *p): ptr(p){}

template<class T>
MyVector<T>::Iterator::Iterator(): ptr(nullptr), pastTheEnd(false){}

template<class T>
DeepPtr<T> *MyVector<T>::Iterator::operator ->() const
{
  return ptr;
}

template<class T>
DeepPtr<T> &MyVector<T>::Iterator::operator *() const
{
  return *ptr;
}

template<class T>
typename MyVector<T>::Iterator &MyVector<T>::Iterator::operator++()
{
  if(ptr!= nullptr)
    {
      ptr=ptr+1;
        if(!pastTheEnd)
        {
            if(ptr+1==nullptr) pastTheEnd=true;
        }
    }
  return *this;
}

template<class T>
typename MyVector<T>::Iterator MyVector<T>::Iterator::operator++(int i)
{
  if(ptr!= nullptr)
    {
        if(!pastTheEnd)
        {
            ptr = ptr + i;
            if(ptr+i==nullptr) pastTheEnd=true;
        }
    }
  return *this;
}

template<class T>
typename MyVector<T>::Iterator &MyVector<T>::Iterator::operator--()
{
  if(ptr!=nullptr)
  {
      ptr=ptr-1;
      if(pastTheEnd) pastTheEnd=false;
  }
  return *this;
}

template<class T>
typename MyVector<T>::Iterator MyVector<T>::Iterator::operator--(int i)
{
  if(ptr!=nullptr)
  {
      ptr=ptr-i;
      if(pastTheEnd) pastTheEnd=false;
  }
  return *this;
}

template<class T>
bool MyVector<T>::Iterator::operator ==(const MyVector::Iterator &o) const
{
  return o.ptr == ptr;
}

template<class T>
bool MyVector<T>::Iterator::operator !=(const MyVector::Iterator &o) const
{
  return o.ptr != ptr;
}

template<class T>
DeepPtr<T> &MyVector<T>::Iterator::operator [](int i) const
{
  return *(ptr+i);
}

// --- FINE ITERATOR

template<class T>
MyVector<T>::MyVector(T *p, unsigned int sz): v(new T[(sz>=0?sz:0)]), size(sz), capacity(sz)
{
  if(p == nullptr){
      for(unsigned int i=0;i<sz;i++){
          v[i] = nullptr;
        }
    }else{
      for(unsigned int i=0;i<sz;i++){
          v[i] = *p;
        }
    }
}

template<class T>
MyVector<T>::~MyVector()
{
  if(v) delete[] v;
}

template<class T>
unsigned int MyVector<T>::getSize() const
{
  return size;
}

template<class T>
typename MyVector<T>::Iterator MyVector<T>::begin()
{
  return v[0];
}

template<class T>
typename MyVector<T>::Iterator MyVector<T>::end()
{
  return v[size-1];
}

template<class T>
typename MyVector<T>::Iterator MyVector<T>::search(const DeepPtr<T> &o)
{//da controllare
  Iterator it = begin();
  for(;it!=end() && *it != o;++it){
      if(it == end()) return Iterator(0); // soprattutto questo
    }
  return it;
}

template<class T>
DeepPtr<T> &MyVector<T>::operator[](unsigned int i) const
{
  return v[i];
}

template<class T>
bool MyVector<T>::push_back(const T *o)
{
  if(o != nullptr){
      if(size >= capacity){

          //devo aumentare la dimensione dell'array
          T* temp = new T[size*2+1];

          unsigned int i=0;
          for (; i < size; i++) {
              temp[i] = v[i];
            }
          //aggiungo l' elemento
          temp[i] = *o;
          v = temp;
          size = i+1;
          capacity = i*2+1;
          return true;
        }else{
          //aggiungo l' elemento
          v[size++] = *o;
          return true;
        }
    }
  return false;
}

template<class T>
bool MyVector<T>::pop_back()
{
  if(size){
       size--;
       return true;
    }
  return false;
}

template<class T>
bool MyVector<T>::remove(const T &o)
{
  for (unsigned int i = 0; i < size; ++i) {
      if(v[i] == o ){
          for(unsigned int j=i;j<size-1;j++){
              v[j] = v[j+1];
            }
          size--;
          return true;
        }
    }
  return false;
}

template<class T>
bool MyVector<T>::isEmpty() const
{
  return !size;
}

#endif // MYVECTOR_H