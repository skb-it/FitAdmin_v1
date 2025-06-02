#ifndef TRENERZY_MANAGER_H
#define TRENERZY_MANAGER_H

#include <QString>
#include "trener.h"
#include <vector>

class TrenerzyManager
{
public:
    void dodajTrenera(const Trener &t);
    void usunTrenera(int index);
    std::vector<Trener> &getTrenerzy();
    const Trener &getTrener(int index) const;
    bool zapiszDoPliku(const QString &sciezkaPliku) const;
    bool wczytajZPliku(const QString &sciezkaPliku);

private:
    std::vector<Trener> trenerzy;
};

#endif // TRENERZY_MANAGER_H
