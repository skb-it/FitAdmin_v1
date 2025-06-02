// karnety_manager.cpp

#include "karnety_manager.h"
#include <QFile>
#include <QTextStream>

// Dodaje nowy karnet do listy
void KarnetyManager::dodajKarnet(const Karnet& k) {
    karnety.push_back(k);
}

// Usuwa karnet o podanym indeksie
void KarnetyManager::usunKarnet(int index) {
    if (index >= 0 && index < static_cast<int>(karnety.size()))
        karnety.erase(karnety.begin() + index);
}

// Zwraca referencję do wektora karnetów
std::vector<Karnet>& KarnetyManager::getKarnety() {
    return karnety;
}

// Zwraca stałą referencję do karnetu o podanym indeksie
const Karnet& KarnetyManager::getKarnet(int index) const {
    return karnety.at(index);
}

// Zapisuje wszystkie karnety do pliku tekstowego (CSV)
bool KarnetyManager::zapiszDoPliku(const QString& sciezkaPliku) const
{
    QFile plik(sciezkaPliku);
    if (!plik.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&plik);
    for (const Karnet& k : karnety) {
        out << k.getNazwa() << ","
            << k.getCena() << ","
            << k.getCzasTrwania() << ","
            << k.getLimitWejsc() << ","
            << (k.isAktywny() ? "1" : "0") << "\n";
    }
    plik.close();
    return true;
}

// Wczytuje karnety z pliku tekstowego (CSV)
bool KarnetyManager::wczytajZPliku(const QString& sciezkaPliku)
{
    QFile plik(sciezkaPliku);
    if (!plik.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&plik);
    karnety.clear();
    while (!in.atEnd()) {
        QString linia = in.readLine();
        QStringList pola = linia.split(",");
        if (pola.size() != 5)
            continue;

        QString nazwa = pola[0];
        double cena = pola[1].toDouble();
        int czasTrwania = pola[2].toInt();
        int limitWejsc = pola[3].toInt();
        bool aktywny = pola[4].trimmed() == "1";

        karnety.emplace_back(nazwa, cena, czasTrwania, limitWejsc, aktywny);
    }
    plik.close();
    return true;
}
