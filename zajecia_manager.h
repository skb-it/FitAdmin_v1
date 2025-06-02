#ifndef ZAJECIA_MANAGER_H
#define ZAJECIA_MANAGER_H

#include "zajecia.h"
#include <vector>

class ZajeciaManager
{
public:
    void dodajZajecia(const Zajecia &z);
    void usunZajecia(int index);
    std::vector<Zajecia> &getZajecia();
    bool zapiszDoPliku(const QString &sciezkaPliku) const;
    bool wczytajZPliku(const QString &sciezkaPliku);

private:
    std::vector<Zajecia> zajecia;
};

#endif // ZAJECIA_MANAGER_H
