#include "sala.h"

Sala::Sala(unsigned int r, unsigned int c, string n)
    : righe(r), colonne(c), nome_sala(n) {}

Sala::Sala(const Sala &o)
    : righe(o.righe), colonne(o.colonne), nome_sala(o.nome_sala) {}

unsigned int Sala::getColonne() const { return colonne; }

string Sala::getNomesala() const { return nome_sala; }

Sala *Sala::clone() const { return new Sala(*this); }

unsigned int Sala::getRighe() const { return righe; }

bool Sala::operator==(const Sala &o) const {
  return colonne == o.colonne && righe == o.righe && nome_sala == o.nome_sala;
}

bool Sala::operator!=(const Sala &o) const {
  return colonne != o.colonne && righe != o.righe && nome_sala != o.nome_sala;
}
