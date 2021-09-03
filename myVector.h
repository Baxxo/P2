#ifndef MYVECTOR_H
#define MYVECTOR_H

template <class T>
class MyVector {
 private:
  T *v;
  unsigned int size;      // numero celle popolate
  unsigned int capacity;  // dimensione totale

  void destroy(T *v);
  T *copy(unsigned int c, unsigned int s);

 public:
  class Iterator {
    friend class MyVector;

   private:
    T *ptr;

   public:
    Iterator(T &p);
    Iterator(T *p = nullptr);

    T *operator->() const;

    T &operator*() const;

    Iterator operator+(int i) const;

    Iterator &operator++();
    Iterator operator++(int i);

    Iterator &operator--();
    Iterator operator--(int i);
    T &operator[](int i) const;

    bool operator==(const Iterator &o) const;
    bool operator!=(const Iterator &o) const;
    bool operator<(const Iterator &o) const;
    bool operator>(const Iterator &o) const;
  };

  class Const_iterator {
    friend class MyVector;

   private:
    const T *ptr;

   public:
    Const_iterator(T &p);
    Const_iterator(T *p = nullptr);

    const T *operator->() const;

    const T &operator*() const;

    Const_iterator operator+(int i) const;

    Const_iterator &operator++();
    Const_iterator operator++(int i);

    Const_iterator &operator--();
    Const_iterator operator--(int i);

    const T &operator[](int i) const;

    bool operator==(const Const_iterator &o) const;
    bool operator!=(const Const_iterator &o) const;
  };

  Iterator copy(Iterator first, Iterator last, Iterator destination);

  MyVector(const T &p, unsigned int sz = 0);
  MyVector(unsigned int s = 0, unsigned int c = 1);
  ~MyVector();

  MyVector(const MyVector &o);

  unsigned int getSize() const;

  Iterator begin();
  Iterator end();
  Iterator search(const T &o);  // forse da mettere const

  Const_iterator cbegin() const;
  Const_iterator cend() const;
  Const_iterator csearch(const T &o) const;  // forse da mettere const

  T &operator[](unsigned int i) const;

  void push_back(const T &o);
  void pop_back();  // deve andare void

  bool erase(Iterator i);

  // bool erase(Const_iterator it);

  Iterator erase(Iterator it1, Iterator it2);

  bool isEmpty() const;

  void clear();
};

// --- INIZIO ITERATOR

template <class T>
MyVector<T>::Iterator::Iterator(T *p) : ptr(p) {}

template <class T>
MyVector<T>::Iterator::Iterator(T &p) : ptr(T(p)) {}

template <class T>
T *MyVector<T>::Iterator::operator->() const {
  return ptr;
}

template <class T>
T &MyVector<T>::Iterator::operator*() const {
  return *ptr;
}

template <class T>
typename MyVector<T>::Iterator MyVector<T>::Iterator::operator+(int i) const {
  return (ptr + i);
}

template <class T>
typename MyVector<T>::Iterator &MyVector<T>::Iterator::operator++() {
  ++ptr;
  return *this;
}

template <class T>
typename MyVector<T>::Iterator MyVector<T>::Iterator::operator--(int i) {
  Iterator tmp = *this;
  --ptr;
  return tmp;
}

template <class T>
typename MyVector<T>::Iterator MyVector<T>::Iterator::operator++(int i) {
  Iterator tmp = *this;
  ++ptr;
  return tmp;
}

template <class T>
typename MyVector<T>::Iterator &MyVector<T>::Iterator::operator--() {
  --ptr;
  return *this;
}

template <class T>
bool MyVector<T>::Iterator::operator==(const MyVector<T>::Iterator &o) const {
  return o.ptr == ptr;
}

template <class T>
bool MyVector<T>::Iterator::operator!=(const MyVector<T>::Iterator &o) const {
  return o.ptr != ptr;
}

template <class T>
T &MyVector<T>::Iterator::operator[](int i) const {
  return *(ptr + i);
}

// --- FINE ITERATOR

// --- INIZIO CONST ITERATOR

template <class T>
MyVector<T>::Const_iterator::Const_iterator(T *p) : ptr(p) {}

template <class T>
MyVector<T>::Const_iterator::Const_iterator(T &p) : ptr(T(p)) {}

template <class T>
const T *MyVector<T>::Const_iterator::operator->() const {
  return ptr;
}

template <class T>
const T &MyVector<T>::Const_iterator::operator*() const {
  return *ptr;
}

template <class T>
typename MyVector<T>::Const_iterator &MyVector<T>::Const_iterator::
operator++() {
  ++ptr;
  return *this;
}

template <class T>
typename MyVector<T>::Const_iterator MyVector<T>::Const_iterator::operator++(
    int i) {
  Const_iterator tmp = Const_iterator(this);
  ++ptr;
  return tmp;
}

template <class T>
typename MyVector<T>::Const_iterator &MyVector<T>::Const_iterator::
operator--() {
  --ptr;
  return *this;
}

template <class T>
typename MyVector<T>::Const_iterator MyVector<T>::Const_iterator::operator--(
    int i) {
  Const_iterator tmp = Const_iterator(this);
  --ptr;
  return tmp;
}

template <class T>
bool MyVector<T>::Const_iterator::operator==(
    const MyVector<T>::Const_iterator &o) const {
  return o.ptr == ptr;
}

template <class T>
bool MyVector<T>::Const_iterator::operator!=(
    const MyVector<T>::Const_iterator &o) const {
  return o.ptr != ptr;
}

template <class T>
const T &MyVector<T>::Const_iterator::operator[](int i) const {
  return *(ptr + i);
}
// --- FINE CONST ITERATOR

template <class T>
MyVector<T>::MyVector(const T &p, unsigned int sz)
    : v(new T[(sz >= 0 ? sz : 0)]), size(sz), capacity(sz) {
  for (unsigned int i = 0; i < capacity; i++) {
    v[i] = p;
  }
}

template <class T>
MyVector<T>::MyVector(unsigned int s, unsigned int c)
    : v(new T[c]), size(s), capacity(c) {}

template <class T>
MyVector<T>::~MyVector() {
  destroy(v);
}

template <class T>
MyVector<T>::MyVector(const MyVector &o)
    : v(o.copy(o.size, o.capacity)), size(o.size), capacity(o.capacity) {}

template <class T>
T *MyVector<T>::copy(unsigned int s, unsigned int c) {
  if (s <= c && size <= s) {
    T *tmp = new T[c];
    for (int i = 0; i < size; i++) {
      tmp[i] = v[i];
    }
    return tmp;
  } else
    return nullptr;
}

template <class T>
unsigned int MyVector<T>::getSize() const {
  return size;
}

template <class T>
void MyVector<T>::destroy(T *v) {
  if (v) delete[] v;
}

template <class T>
typename MyVector<T>::Iterator MyVector<T>::begin() {
  return Iterator(v);
}

template <class T>
typename MyVector<T>::Iterator MyVector<T>::end() {
  return Iterator(v + size);
}

template <class T>
typename MyVector<T>::Const_iterator MyVector<T>::cbegin() const {
  return Const_iterator(v);
}

template <class T>
typename MyVector<T>::Const_iterator MyVector<T>::cend() const {
  return Const_iterator(v + size);
}

template <class T>
typename MyVector<T>::Iterator MyVector<T>::search(const T &o) {
  Iterator it = begin();
  for (; it != end() && *it != o; ++it)
    ;
  if (it == end()) return begin();
  return it;
}

template <class T>
typename MyVector<T>::Const_iterator MyVector<T>::csearch(const T &o) const {
  Const_iterator it = cbegin();
  for (; it != cend() && *it != o; ++it)
    ;

  if (it == cend()) return cbegin();
  return it;
}

template <class T>
T &MyVector<T>::operator[](unsigned int i) const {
  return v[i];
}

template <class T>
void MyVector<T>::push_back(const T &o) {
  if (size >= capacity) {
    capacity *= 2;
    T *tmp = copy(size, capacity);
    destroy(v);
    v = tmp;
  }
  v[size++] = o;
}

template <class T>
void MyVector<T>::pop_back() {
  if (size) {
    size--;
  }
}

template <class T>
bool MyVector<T>::erase(Iterator i) {
  MyVector::Iterator it = erase(i, i + 1);
  if (it != nullptr) {
    return true;
  }
  return false;
}

template <class T>
typename MyVector<T>::Iterator MyVector<T>::erase(Iterator it1, Iterator it2) {
  if (!size) return nullptr;
  if (it1 < begin()) return erase(begin(), it2);
  if (it2 > end()) return erase(it1, end());

  copy(it2, end(), it1);

  int offset = static_cast<int>(it2.ptr - it1.ptr);
  size = size - offset;
  return it1;
}

template <class T>
typename MyVector<T>::Iterator MyVector<T>::copy(Iterator first, Iterator last,
                                                 Iterator destination) {
  while (first != last) {
    *destination = *first;
    ++first;
    ++destination;
  }

  return destination;
}

template <class T>
bool MyVector<T>::isEmpty() const {
  return size == 0;
}

template <class T>
void MyVector<T>::clear() {
  destroy(v);
  size = 0;
  capacity = 1;
  v = new T[capacity];
}

#endif  // MYVECTOR_H

template <class T>
bool MyVector<T>::Iterator::operator<(const MyVector::Iterator &o) const {
  return ptr < o.ptr;
}

template <class T>
bool MyVector<T>::Iterator::operator>(const MyVector::Iterator &o) const {
  return ptr > o.ptr;
}
