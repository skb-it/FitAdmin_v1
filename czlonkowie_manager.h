#ifndef CZLONKOWIE_MANAGER_H
#define CZLONKOWIE_MANAGER_H

#include <vector>
#include "czlonek.h"
#include <QString>

using namespace std;

class CzlonkowieManager {
public:
    void dodajCzlonka(const Czlonek& czlonek);
    void zapiszDoPliku(const QString& nazwaPliku);

private:
    vector<Czlonek> listaCzlonkow;
};

extern CzlonkowieManager czlonkowieManager;

#endif // CZLONKOWIE_MANAGER_H
