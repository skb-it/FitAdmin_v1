#include "trenerzy_manager.h"
#include <QFile>
#include <QTextStream>

void TrenerzyManager::dodajTrenera(const Trener& t) {
    trenerzy.push_back(t);
}
void TrenerzyManager::usunTrenera(int index) {
    if(index >= 0 && index < (int)trenerzy.size()) trenerzy.erase(trenerzy.begin() + index);
}
std::vector<Trener>& TrenerzyManager::getTrenerzy() { return trenerzy; }
const Trener& TrenerzyManager::getTrener(int index) const { return trenerzy.at(index); }

bool TrenerzyManager::zapiszDoPliku(const QString& sciezkaPliku) const {
    QFile plik(sciezkaPliku);
    if (!plik.open(QIODevice::WriteOnly | QIODevice::Text)) return false;
    QTextStream out(&plik);
    for (const Trener& t : trenerzy)
        out << t.getId() << "," << QString::fromStdString(t.getImie()) << "," << QString::fromStdString(t.getNazwisko()) << "\n";
    plik.close();
    return true;
}
bool TrenerzyManager::wczytajZPliku(const QString& sciezkaPliku) {
    QFile plik(sciezkaPliku);
    if (!plik.open(QIODevice::ReadOnly | QIODevice::Text)) return false;
    trenerzy.clear();
    QTextStream in(&plik);
    while(!in.atEnd()) {
        QString linia = in.readLine();
        QStringList pola = linia.split(",");
        if (pola.size() != 3) continue;
        int id = pola[0].toInt();
        trenerzy.emplace_back(id, pola[1].toStdString(), pola[2].toStdString());
    }
    plik.close();
    return true;
}
