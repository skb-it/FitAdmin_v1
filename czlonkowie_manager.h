#ifndef CZLONKOWIE_MANAGER_H
#define CZLONKOWIE_MANAGER_H

#include <QString>
#include "czlonek.h"
#include <vector>

using namespace std;

class CzlonkowieManager
{
public:
    void dodajCzlonka(const Czlonek &czlonek);
    void zapiszDoPliku(const QString &nazwaPliku);
    bool wczytajZPliku(const QString &nazwaPliku);

    vector<Czlonek> getCzlonkowie() const;

private:
    vector<Czlonek> listaCzlonkow;
};

extern CzlonkowieManager czlonkowieManager;

#endif // CZLONKOWIE_MANAGER_H
