#ifndef DEEPPTR_H
#define DEEPPTR_H
template <class T>
class DeepPtr{
private:
	T* ptr;
public:
	DeepPtr(const T* p = nullptr);

	DeepPtr(const DeepPtr<T>& o);
	~DeepPtr();
	DeepPtr<T>& operator= (const DeepPtr& o);

	T& operator*() const;
	T* operator -> () const;
};

template <class T>
DeepPtr<T>::DeepPtr(const T* p) : ptr(p) {}

template <class T>
DeepPtr<T>::DeepPtr(const DeepPtr<T>& o) : ptr(o.ptr ? o.ptr->clone() : nullptr) {}

template <class T>
DeepPtr<T>::~DeepPtr() { if(ptr) delete ptr;}

template <class T>
DeepPtr<T>& DeepPtr<T>::operator= (const DeepPtr<T>& o){
	if(this != &o){
		if(ptr) delete ptr;
		ptr = o.ptr ? o.ptr->clone() : nullptr;
	}

	return *this;
}

template <class T>
T& DeepPtr<T>::operator*() const{ return *ptr;}

template <class T>
T* DeepPtr<T>::operator->() const{ return ptr;}

#endif // DEEPPTR_H
