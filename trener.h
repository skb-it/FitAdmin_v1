#ifndef TRENER_H
#define TRENER_H

#include "osoba.h"

class Trener : public Osoba
{
    int id;

public:
    Trener(int id, const string &imie, const string &nazwisko);

    int getId() const;
};

#endif // TRENER_H
