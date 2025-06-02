#ifndef OSOBA_H
#define OSOBA_H

#include <string>

using namespace std;

class Osoba {
public:
    Osoba(const string& imie, const string& nazwisko);

    string getImie() const;
    string getNazwisko() const;

protected:
    string imie;
    string nazwisko;
};

#endif // OSOBA_H
