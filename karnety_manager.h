// karnety_manager.h
#ifndef KARNETY_MANAGER_H
#define KARNETY_MANAGER_H

#include "karnet.h"
#include <vector>
#include <QString>

class KarnetyManager {
public:
    void dodajKarnet(const Karnet& k);
    void usunKarnet(int index);
    std::vector<Karnet>& getKarnety();
    const Karnet& getKarnet(int index) const;

    // Nowe metody do zapisu i odczytu z pliku
    bool zapiszDoPliku(const QString& sciezkaPliku) const;
    bool wczytajZPliku(const QString& sciezkaPliku);

private:
    std::vector<Karnet> karnety;
};

#endif // KARNETY_MANAGER_H
