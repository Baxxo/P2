#include "famiglia.h"
#include <QDebug>

Famiglia::Famiglia(string _name, unsigned int c)
    : membri(new Utente *[c]), capacity(c), size(0), name(_name) {
  //  qDebug() << "costrut famiglia";
}

Famiglia::Famiglia(const Famiglia &o)
    : membri(new Utente *[o.capacity]),
      capacity(o.capacity),
      size(o.size),
      name(o.name) {
  for (unsigned int i = 0; i < o.size; i++) {
    membri[i] = o.membri[i];
  }
}

void Famiglia::resize() {
  capacity *= 2;
  Utente **u = new Utente *[capacity];
  for (unsigned int i = 0U; i < size; i++) {
    u[i] = membri[i];
  }
  destroy(membri);
  membri = u;
}

void Famiglia::destroy(Utente **u) {
  if (u) delete[] u;
}

Famiglia::~Famiglia() { destroy(membri); }

void Famiglia::addMembro(Utente *u) {
  if (size >= capacity) {
    resize();
  }
  membri[size] = u;
  size++;
}

void Famiglia::removeMembro(Utente *u) {
  if (hasMembro(u)) {
    for (unsigned int i = 0U; i < size; i++) {
      if (*(membri[i]) == *u) {
        Utente **temp = new Utente *[capacity];
        for (unsigned int j = 0; j < i; j++) {
          temp[j] = membri[j];
        }
        for (unsigned int j = i + 1; j < size; j++) {
          temp[j - 1] = membri[j];
        }
        size--;
        destroy(membri);
        membri = temp;
      }
    }
  }
}

bool Famiglia::hasMembro(Utente *u) {
  for (unsigned int i = 0; i < size; ++i) {
    if (*u == *(membri[i])) {
      return true;
    }
  }
  return false;
}

unsigned int Famiglia::getSize() const { return size; }

Utente *&Famiglia::operator[](unsigned int i) const {
  if (i >= size) {
    throw std::out_of_range("Out of range");
  }

  return membri[i];
}

Utente *&Famiglia::operator[](int i) const {
  if (static_cast<unsigned int>(i) >= size) {
    throw std::out_of_range("Out of range");
  }
  return membri[i];
}

bool Famiglia::operator==(const Famiglia &f) const { return f.name == name; }

bool Famiglia::operator!=(const Famiglia &f) const { return f.name != name; }

Utente *&Famiglia::operator*() const { return *membri; }

Utente **Famiglia::operator->() const { return membri; }

bool Famiglia::isEmpty() const { return size == 0; }

Famiglia &Famiglia::operator=(const Famiglia &o) {
  if (this != &o) {
    capacity = o.capacity;
    size = o.size;
    membri = o.membri;
  }
  return *this;
}

Famiglia *Famiglia::clone() const { return new Famiglia(*this); }

string Famiglia::getName() const { return name; }

void Famiglia::setName(const string &value) { name = value; }

string Famiglia::toString() const {
  return "nome: " + name + " size:" + std::to_string(size);
}
