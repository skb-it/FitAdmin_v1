#include "czlonek.h"

using namespace std;

Czlonek::Czlonek(
    const string& imie,
    const string& nazwisko,
    bool aktywny,
    const QDate& dataAktywacji,
    const QDate& dataWygasniecia,
    const string& nazwaKarnetu,
    int pozostalychWejsc
    )
    : Osoba(imie, nazwisko),
    aktywny(aktywny),
    dataAktywacji(dataAktywacji),
    dataWygasniecia(dataWygasniecia),
    nazwaKarnetu(nazwaKarnetu),
    pozostalychWejsc(pozostalychWejsc)
{}

int Czlonek::getPozostalychWejsc() const {
    return pozostalychWejsc;
}
void Czlonek::setPozostalychWejsc(int pozostalychWejsc){
    this->pozostalychWejsc = pozostalychWejsc;
}

string Czlonek::getNazwaKarnetu() const {
    return nazwaKarnetu;
}

bool Czlonek::czyAktywny() const {
    return aktywny;
}

QDate Czlonek::getDataAktywacji() const {
    return dataAktywacji;
}

QDate Czlonek::getDataWygasniecia() const {
    return dataWygasniecia;
}
