#include "czlonkowie_manager.h"
#include <QFile>
#include <QTextStream>

void CzlonkowieManager::dodajCzlonka(const Czlonek& czlonek) {
    listaCzlonkow.push_back(czlonek);
}

void CzlonkowieManager::zapiszDoPliku(const QString& nazwaPliku) {
    QFile file(nazwaPliku);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const auto& czlonek : listaCzlonkow) {
            out << QString::fromStdString(czlonek.getImie()) << ","
                << QString::fromStdString(czlonek.getNazwisko()) << ","
                << QString::fromStdString(czlonek.getNazwaKarnetu()) << ","
                << (czlonek.czyAktywny() ? "1" : "0") << ","
                << czlonek.getDataAktywacji().toString("yyyy-MM-dd hh:mm") << ","
                << czlonek.getDataWygasniecia().toString("yyyy-MM-dd hh:mm") << "\n";
        }
        file.close();
    }
}

