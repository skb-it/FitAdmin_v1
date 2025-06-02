#include "sprzet_manager.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>

SprzetManager::SprzetManager(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Edytuj sprzęt");

    lineEditNazwa = new QLineEdit(this);
    spinBoxIlosc = new QSpinBox(this);
    spinBoxIlosc->setMinimum(1);
    spinBoxIlosc->setMaximum(1000);

    comboStan = new QComboBox(this);
    comboStan->addItems({"Sprawny", "Uszkodzony", "W naprawie"});

    dateEditPrzeglad = new QDateEdit(QDate::currentDate(), this);
    dateEditPrzeglad->setCalendarPopup(true);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    auto *formLayout = new QFormLayout;
    formLayout->addRow("Nazwa:", lineEditNazwa);
    formLayout->addRow("Ilość:", spinBoxIlosc);
    formLayout->addRow("Stan:", comboStan);
    formLayout->addRow("Data przeglądu:", dateEditPrzeglad);

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
}

void SprzetManager::ustawDane(QString nazwa, int ilosc, QString stan, QDate przeglad)
{
    lineEditNazwa->setText(nazwa);
    spinBoxIlosc->setValue(ilosc);
    comboStan->setCurrentText(stan);
    dateEditPrzeglad->setDate(przeglad);
}

QString SprzetManager::pobierzNazwa() const
{
    return lineEditNazwa->text();
}

int SprzetManager::pobierzIlosc() const
{
    return spinBoxIlosc->value();
}

QString SprzetManager::pobierzStan() const
{
    return comboStan->currentText();
}

QDate SprzetManager::pobierzData() const
{
    return dateEditPrzeglad->date();
}
