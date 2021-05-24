template <class T>
class DeepPtr{
private:
	T* ptr;
public:
	DeepPtr(T* p = nullptr);

	DeepPtr(const DeepPtr& o);
	~DeepPtr();
	DeepPtr<T>& operator= (const DeepPtr& o);
/*
	operator bool() const;
	bool operator !() const;
*/
	T& operator*() const;
	T* oprerator ->() const;

	bool operator == (const DeepPtr& o) const;
	bool operator != (const DeepPtr& o) const;
};

template <class T>
DeepPtr<T>::DeepPtr(T* p) : ptr(p) {}

template <class T>
DeepPtr<T>::DeepPtr(const DeepPtr& o) : ptr(o ? o.ptr->clone() : nullptr) {}

template <class T>
DeepPtr<T>::~DeepPtr(const DeepPtr& o) { delete ptr;}

template <class T>
DeepPtr& DeepPtr<T>::operator= (const DeepPtr& o){
	if(this != &o){
		delete ptr;
		ptr = o ? o.ptr->clone() : nullptr;
	}

	return *this;
}

/*
template <class T>
DeepPtr<T>::operator bool() const{ return ptr != nullptr;}

template <class T>
bool DeepPtr<T>::operator ! const{ return ptr == nullptr;}
*/

template <class T>
T& DeepPtr<T>::operator* const{ return ptr;}

template <class T>
T* DeepPtr<T>::operator-> const{ return ptr;}

template<class T>
bool DeepPtr<T>::operator==(const DeepPtr& o) const {
    return ptr == o;
}

template<class T>
bool DeepPtr<T>::operator!=(const DeepPtr& o) const {
    return ptr != o;
}