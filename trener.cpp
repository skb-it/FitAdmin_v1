#include "trener.h"

Trener::Trener(int id, const string& imie, const string& nazwisko)
    : Osoba(imie, nazwisko), id(id) {}

int Trener::getId() const {
    return id;
}
