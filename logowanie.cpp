#include "logowanie.h"
#include "ui_logowanie.h"
#include <QMessageBox>

Logowanie::Logowanie(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Logowanie)
{
    ui->setupUi(this);
}

Logowanie::~Logowanie()
{
    delete ui;
}

void Logowanie::on_pushButtonZaloguj_clicked()
{
    QString login = ui->lineEditLogin->text();
    QString haslo = ui->lineEditHaslo->text();

    if (login == "admin" && haslo == "1234") {
        accept();
    } else {
        QMessageBox::warning(this, "Błąd logowania", "Nieprawidłowy login lub hasło.");
    }
}

void Logowanie::on_pushButtonAnuluj_clicked()
{
    reject();
}
