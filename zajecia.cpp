#include "zajecia.h"

Zajecia::Zajecia(int idTrenera, const QString& trenerImieNazwisko,
                 const QDateTime& start, const QDateTime& end,
                 const QString& sala, int limitMiejsc)
    : idTrenera(idTrenera),
    trenerImieNazwisko(trenerImieNazwisko),
    start(start),
    end(end),
    sala(sala),
    limitMiejsc(limitMiejsc),
    wolnychMiejsc(limitMiejsc)
{}

int Zajecia::getIdTrenera() const {
    return idTrenera;
}

QString Zajecia::getTrenerImieNazwisko() const {
    return trenerImieNazwisko;
}

QDateTime Zajecia::getStart() const {
    return start;
}

QDateTime Zajecia::getEnd() const {
    return end;
}

QString Zajecia::getSala() const {
    return sala;
}

int Zajecia::getLimitMiejsc() const {
    return limitMiejsc;
}

int Zajecia::getWolnychMiejsc() const {
    return wolnychMiejsc;
}

void Zajecia::setWolnychMiejsc(int v) {
    wolnychMiejsc = v;
}
