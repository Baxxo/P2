#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>
using std::cout;
using std::endl;

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
      T* ptr;//DeepPtr<T>* ptr;
      bool pastTheEnd;

    public:
      Iterator(T* p, bool pte=false): ptr(p), pastTheEnd(pte){}
      Iterator(): ptr(nullptr), pastTheEnd(false){}

      T* operator ->() const {return ptr;}

      T& operator * () const {return *ptr;}

      Iterator& operator++(){
        if(ptr!= nullptr)
          {
              if(!pastTheEnd)
              {
                  if(ptr+1==nullptr)
                  {
                      ++ptr;
                      pastTheEnd=true;
                  }
                  else
                  {
                      ptr=ptr+1;
                  }
              }
          }
          return *this;
      }
      Iterator& operator--()
      {
          if(ptr!=nullptr)
          {
              if(pastTheEnd)
              {
                  --ptr;
                  pastTheEnd=false;
              }
              else
                  ptr=ptr-1;
          }
          return *this;
      }
      bool operator == (const Iterator& o) const{ return o.ptr == ptr;}
      bool operator != (const Iterator& o) const{ return o.ptr != ptr;}
  };

  MyVector(T* p=nullptr, unsigned int sz=0): v(new T[(sz>=0?sz:0)]), size(sz), capacity(sz)
  {
    if(p == nullptr){
        for(unsigned int i=0;i<sz;i++){
            //cout << "if i: " << i << endl;
            v[i] = nullptr;
          }
      }else{
        for(unsigned int i=0;i<sz;i++){
            //cout << "else i: " << i << endl;
            v[i] = *p;
          }
      }
  }
  ~MyVector()
  {
    delete[] v;
  }

  MyVector(const MyVector& o);

  unsigned int getSize() const
  {
    return size;
  }

  Iterator begin()
  {
    return v[0];
  }
  Iterator end()
  {
    return v[size-1];
  }

  T& operator[](unsigned int i) const{
    return v[i];
  }

  bool add(const T* o)
  {
    if(o != nullptr){
        //cout << "Capacity: " << capacity << " " << size<<endl;
        if(size >= capacity){
            //cout << " punto a" << endl;

            //devo aumentare la dimensione dell'array
            T* temp = new T[size*2+1];

            //cout << " punto b size: "<<size*2+1 << endl;
            unsigned int i=0;
            for (; i < size; i++) {
                temp[i] = v[i];
              }
            //aggiungo l' elemento
            temp[i] = *o;
            v = temp;
            size = i+1;
            capacity = i*2+1;
            //cout << " punto c inserito" << endl;
            //cout << "size: " << size << " capacity: " << capacity << endl;
            return true;
          }else{
            //cout << "Sono qui" << endl;
            //aggiungo l' elemento
            v[size++] = *o;
            //cout << "size: " << size << " capacity: " << capacity << endl;
            return true;
          }
        //cout << "NON inserito" << endl;
      }
    return false;
  }

  void remove(T& o){
      for (unsigned int i = 0; i < size; ++i) {
          if(v[i] == o ){
              for(unsigned int j=i;j<size-1;j++){
                  v[j] = v[j+1];
                }
              size--;
              return;
            }
        }
  }
};

#endif // MYVECTOR_H
