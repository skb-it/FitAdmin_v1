#ifndef CZLONEK_H
#define CZLONEK_H

#include <string>
#include <QDateTime>

using namespace std;

class Czlonek {
private:
    string imie;
    string nazwisko;
    string nazwaKarnetu;
    bool aktywny;
    QDateTime dataAktywacji;
    QDateTime dataWygasniecia;
    int pozostalychWejsc;

public:
    Czlonek(const string& imie, const string& nazwisko,
            bool aktywny, const QDateTime& dataWygasniecia,
            const string& nazwaKarnetu, int pozostalychWejsc);

    string getImie() const;
    string getNazwisko() const;
    string getNumerKarnetu() const;
    string getNazwaKarnetu() const;
    bool czyAktywny() const;
    QDateTime getDataAktywacji() const;
    QDateTime getDataWygasniecia() const;
    int getPozostalychWejsc() const;
    void setPozostalychWejsc(int pozostalychWejsc);
};

#endif // CZLONEK_H
