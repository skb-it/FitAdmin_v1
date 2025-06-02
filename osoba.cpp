#include "osoba.h"

Osoba::Osoba(const string &imie, const string &nazwisko)
    : imie(imie)
    , nazwisko(nazwisko)
{}

string Osoba::getImie() const
{
    return imie;
}

string Osoba::getNazwisko() const
{
    return nazwisko;
}
