#ifndef CZLONEK_H
#define CZLONEK_H

#include <string>
#include <QDateTime>

using namespace std;

class Czlonek {
private:
    string imie;
    string nazwisko;
    string numerKarnetu;
    bool aktywny;
    QDateTime dataAktywacji;
    QDateTime dataWygasniecia;

    static int licznikKarnetow; // licznik do generowania nr karnetu

    string generujNumerKarnetu();

public:
    // Konstruktor bez numeru karnetu i daty aktywacji — ustawiane automatycznie
    Czlonek(const string& imie, const string& nazwisko,
            bool aktywny, const QDateTime& dataWygasniecia);

    // Gettery
    string getImie() const;
    string getNazwisko() const;
    string getNumerKarnetu() const;
    bool czyAktywny() const;
    QDateTime getDataAktywacji() const;
    QDateTime getDataWygasniecia() const;
};

#endif // CZLONEK_H
