#include "czlonkowie_manager.h"
#include <QFile>
#include <QTextStream>

void CzlonkowieManager::dodajCzlonka(const Czlonek& czlonek) {
    listaCzlonkow.push_back(czlonek);
}

vector<Czlonek> CzlonkowieManager::getCzlonkowie() const{
    return listaCzlonkow;
}

void CzlonkowieManager::zapiszDoPliku(const QString& nazwaPliku) {
    QFile file(nazwaPliku);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const auto& czlonek : listaCzlonkow) {
            out << QString::fromStdString(czlonek.getImie()) << ","
                << QString::fromStdString(czlonek.getNazwisko()) << ","
                << QString::fromStdString(czlonek.getNazwaKarnetu()) << ","
                << QString::number(czlonek.getPozostalychWejsc()) << ","
                << (czlonek.czyAktywny() ? "1" : "0") << ","
                << czlonek.getDataAktywacji().toString("yyyy-MM-dd") << ","
                << czlonek.getDataWygasniecia().toString("yyyy-MM-dd") << "\n";
        }
        file.close();
    }
}

bool CzlonkowieManager::wczytajZPliku(const QString& nazwaPliku) {
    QFile file(nazwaPliku);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    listaCzlonkow.clear();
    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        if (fields.size() != 7)
            continue;

        std::string imie = fields[0].toStdString();
        std::string nazwisko = fields[1].toStdString();
        std::string nazwaKarnetu = fields[2].toStdString();
        int pozostalychWejsc = fields[3].toInt();
        bool aktywny = (fields[4] == "1");
        QDate dataAktywacji = QDate::fromString(fields[5], "yyyy-MM-dd");
        QDate dataWygasniecia = QDate::fromString(fields[6], "yyyy-MM-dd");

        Czlonek czlonek(imie, nazwisko, aktywny, dataAktywacji, dataWygasniecia, nazwaKarnetu, pozostalychWejsc);

        listaCzlonkow.push_back(czlonek);
    }

    file.close();
    return true;
}
