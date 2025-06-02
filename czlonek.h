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
    QDate dataAktywacji;
    QDate dataWygasniecia;
    int pozostalychWejsc;

public:
    Czlonek(
            const string& imie,
            const string& nazwisko,
            bool aktywny,
            const QDate& dataAktywacji,
            const QDate& dataWygasniecia,
            const string& nazwaKarnetu,
            int pozostalychWejsc
    );

    string getImie() const;
    string getNazwisko() const;
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
