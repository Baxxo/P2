#ifndef MYVECTOR_H
#define MYVECTOR_H

template <class T>
class MyVector
{
private:
    T* v;
    unsigned int size; //numero celle popolatr
    unsigned int capacity; //dimensione totale
    class Iterator
    {
        friend class MyVector;
    public:
        T* ptr;//DeepPtr<T>* ptr;
        bool pastTheEnd;
        Iterator(T* p, bool pte=false);
        Iterator();
        T* operator ->() const;
        T& operator * () const;
        Iterator& operator++();
        Iterator& operator--();
        bool operator == (const Iterator& o) const;
        bool operator != (const Iterator& o) const;
    };
public:
    MyVector(T* p, unsigned int sz=0);
    ~MyVector();
    MyVector(const MyVector& o);
    unsigned int getSize() const;
    T &operator[](unsigned int i) const;

    Iterator begin();
    Iterator end();

    bool add(const T& o);
};

#endif // MYVECTOR_H
