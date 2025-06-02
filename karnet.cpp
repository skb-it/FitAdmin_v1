// karnet.h
#ifndef KARNET_H
#define KARNET_H

#include <QString>

class Karnet
{
public:
    Karnet(const QString &nazwa, double cena, int czasTrwania, int limitWejsc, bool aktywny)
        : nazwa(nazwa)
        , cena(cena)
        , czasTrwania(czasTrwania)
        , limitWejsc(limitWejsc)
        , aktywny(aktywny)
    {}

    QString getNazwa() const { return nazwa; }
    double getCena() const { return cena; }
    int getCzasTrwania() const { return czasTrwania; }
    int getLimitWejsc() const { return limitWejsc; }
    bool isAktywny() const { return aktywny; }

    void setAktywny(bool status) { aktywny = status; }
    void setCena(double c) { cena = c; }
    void setCzasTrwania(int t) { czasTrwania = t; }
    void setLimitWejsc(int l) { limitWejsc = l; }
    void setNazwa(const QString &n) { nazwa = n; }

private:
    QString nazwa;
    double cena;
    int czasTrwania;
    int limitWejsc;
    bool aktywny;
};

#endif // KARNET_H
