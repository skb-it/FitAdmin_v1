#ifndef ZAJECIA_H
#define ZAJECIA_H

#include <QString>
#include <QDateTime>

class Zajecia {
    int idTrenera;
    QString trenerImieNazwisko;
    QDateTime start, end;
    QString sala;
    int limitMiejsc;
    int wolnychMiejsc;

public:
    Zajecia(int idTrenera, const QString& trenerImieNazwisko,
            const QDateTime& start, const QDateTime& end,
            const QString& sala, int limitMiejsc);

    int getIdTrenera() const;
    QString getTrenerImieNazwisko() const;
    QDateTime getStart() const;
    QDateTime getEnd() const;
    QString getSala() const;
    int getLimitMiejsc() const;
    int getWolnychMiejsc() const;

    void setWolnychMiejsc(int v);
};

#endif // ZAJECIA_H
