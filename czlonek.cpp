#include "czlonek.h"

using namespace std;

Czlonek::Czlonek(const string& imie, const string& nazwisko,
                 bool aktywny, const QDateTime& dataWygasniecia,
                 const string& nazwaKarnetu, int pozostalychWejsc)
    : imie(imie), nazwisko(nazwisko), aktywny(aktywny),
    dataAktywacji(QDateTime::currentDateTime()),
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

string Czlonek::getImie() const {
    return imie;
}

string Czlonek::getNazwisko() const {
    return nazwisko;
}

bool Czlonek::czyAktywny() const {
    return aktywny;
}

QDateTime Czlonek::getDataAktywacji() const {
    return dataAktywacji;
}

QDateTime Czlonek::getDataWygasniecia() const {
    return dataWygasniecia;
}
