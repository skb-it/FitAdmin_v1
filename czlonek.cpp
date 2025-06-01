#include "czlonek.h"
#include <sstream>

using namespace std;

int Czlonek::licznikKarnetow = 0;

string Czlonek::generujNumerKarnetu() {
    licznikKarnetow++;
    ostringstream ss;
    ss << "KN" << 1000 + licznikKarnetow; // np. KN1001, KN1002, ...
    return ss.str();
}

Czlonek::Czlonek(const string& imie, const string& nazwisko,
                 bool aktywny, const QDateTime& dataWygasniecia)
    : imie(imie), nazwisko(nazwisko), aktywny(aktywny),
    dataAktywacji(QDateTime::currentDateTime()), // ustawiamy teraz
    dataWygasniecia(dataWygasniecia),
    numerKarnetu(generujNumerKarnetu()) // generujemy numer
{}

string Czlonek::getImie() const {
    return imie;
}

string Czlonek::getNazwisko() const {
    return nazwisko;
}

string Czlonek::getNumerKarnetu() const {
    return numerKarnetu;
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
