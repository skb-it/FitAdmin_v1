#ifndef CZLONEK_H
#define CZLONEK_H

#include "osoba.h"

#include <QDateTime>
#include <string>

using namespace std;

class Czlonek : public Osoba
{
    bool aktywny;
    QDate dataAktywacji;
    QDate dataWygasniecia;
    string nazwaKarnetu;
    int pozostalychWejsc;

public:
    Czlonek(const string &imie,
            const string &nazwisko,
            bool aktywny,
            const QDate &dataAktywacji,
            const QDate &dataWygasniecia,
            const string &nazwaKarnetu,
            int pozostalychWejsc);

    string getNumerKarnetu() const;
    string getNazwaKarnetu() const;
    bool czyAktywny() const;
    QDate getDataAktywacji() const;
    QDate getDataWygasniecia() const;
    int getPozostalychWejsc() const;
    void setPozostalychWejsc(int pozostalychWejsc);
    void setDataAktywacji(const QDate &data);
};

#endif // CZLONEK_H
