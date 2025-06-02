#include "zajecia_manager.h"
#include <QFile>
#include <QTextStream>

void ZajeciaManager::dodajZajecia(const Zajecia& z) { zajecia.push_back(z); }
void ZajeciaManager::usunZajecia(int index) { if(index >= 0 && index < (int)zajecia.size()) zajecia.erase(zajecia.begin() + index); }
std::vector<Zajecia>& ZajeciaManager::getZajecia() { return zajecia; }

bool ZajeciaManager::zapiszDoPliku(const QString& sciezkaPliku) const {
    QFile plik(sciezkaPliku);
    if (!plik.open(QIODevice::WriteOnly | QIODevice::Text)) return false;
    QTextStream out(&plik);
    for (const Zajecia& z : zajecia) {
        out << z.getIdTrenera() << ","
            << z.getTrenerImieNazwisko() << ","
            << z.getStart().toString(Qt::ISODate) << ","
            << z.getEnd().toString(Qt::ISODate) << ","
            << z.getSala() << ","
            << z.getLimitMiejsc() << ","
            << z.getWolnychMiejsc() << "\n";
    }
    plik.close();
    return true;
}

bool ZajeciaManager::wczytajZPliku(const QString& sciezkaPliku) {
    QFile plik(sciezkaPliku);
    if (!plik.open(QIODevice::ReadOnly | QIODevice::Text)) return false;
    zajecia.clear();
    QTextStream in(&plik);
    while(!in.atEnd()) {
        QString linia = in.readLine();
        QStringList pola = linia.split(",");
        if (pola.size() != 7) continue;
        int idTrenera = pola[0].toInt();
        QString trenerImieNazwisko = pola[1];
        QDateTime start = QDateTime::fromString(pola[2], Qt::ISODate);
        QDateTime end = QDateTime::fromString(pola[3], Qt::ISODate);
        QString sala = pola[4];
        int limitMiejsc = pola[5].toInt();
        int wolnychMiejsc = pola[6].toInt();
        Zajecia z(idTrenera, trenerImieNazwisko, start, end, sala, limitMiejsc);
        z.setWolnychMiejsc(wolnychMiejsc);
        zajecia.push_back(z);
    }
    plik.close();
    return true;
}
