#ifndef DEEPPTR_H
#define DEEPPTR_H

#include <iostream>
using namespace std;

template <class T>
class DeepPtr{
private:
	T* ptr;
public:
	DeepPtr(T* p = nullptr);
	DeepPtr(const DeepPtr<T>& o);

	~DeepPtr();
	DeepPtr<T>& operator= (const DeepPtr& o);

	bool operator ==(const DeepPtr& o) const;
	bool operator !=(const DeepPtr& o) const;

	T& operator*() const;
	T* operator -> () const;

	DeepPtr<T> &operator ++();
	DeepPtr<T> &operator --();
};

template <class T>
DeepPtr<T>::DeepPtr(T* p) : ptr(p) {}
template <class T>
DeepPtr<T>::DeepPtr(const DeepPtr<T>& o)  : ptr(o.ptr ? o.ptr->clone() : nullptr) {}

template <class T>
DeepPtr<T>::~DeepPtr() {cout << "distruttore deep "<< ptr->getName() << endl;if(ptr) delete ptr;}

template <class T>
DeepPtr<T>& DeepPtr<T>::operator= (const DeepPtr<T>& o) {
	if(this != &o){
		if(ptr) delete ptr;
		ptr = o.ptr ? o.ptr->clone() : nullptr;
	}

	return *this;
}

template<class T>
bool DeepPtr<T>::operator ==(const DeepPtr &o) const
{
  return ptr == o.ptr;
}

template<class T>
bool DeepPtr<T>::operator !=(const DeepPtr &o) const
{
  return ptr != o.ptr;
}

template <class T>
T& DeepPtr<T>::operator*() const{ return *ptr;}

template <class T>
T* DeepPtr<T>::operator->() const{ return ptr;}

template<class T>
DeepPtr<T> &DeepPtr<T>::operator ++()
{
  if(ptr + 1 != nullptr) ++ptr;
  return *this;
}

template<class T>
DeepPtr<T> &DeepPtr<T>::operator --()
{
  if(ptr - 1 != nullptr) --ptr;
  return *this;
}

#endif // DEEPPTR_H
