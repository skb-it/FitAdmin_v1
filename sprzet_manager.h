#ifndef SPRZET_MANAGER_H
#define SPRZET_MANAGER_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QDateEdit>
#include <QDialogButtonBox>

class SprzetManager : public QDialog
{
    Q_OBJECT

public:
    explicit SprzetManager(QWidget *parent = nullptr);
    void ustawDane(QString nazwa, int ilosc, QString stan, QDate przeglad);
    QString pobierzNazwa() const;
    int pobierzIlosc() const;
    QString pobierzStan() const;
    QDate pobierzData() const;

private:
    QLineEdit *lineEditNazwa;
    QSpinBox *spinBoxIlosc;
    QComboBox *comboStan;
    QDateEdit *dateEditPrzeglad;
    QDialogButtonBox *buttonBox;
};

#endif // SPRZET_MANAGER_H
