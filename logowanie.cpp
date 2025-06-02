#include "logowanie.h"
#include "ui_logowanie.h"
#include <QMessageBox>
#include <QCryptographicHash>

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

QString hashPassword(const QString &password) {
    QByteArray hashed = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return QString(hashed.toHex());
}

void Logowanie::on_pushButtonZaloguj_clicked()
{
    QString login = ui->lineEditLogin->text();
    QString haslo = ui->lineEditHaslo->text();

    // Ustalony login i hash hasła
    QString correctLogin = "admin";
    QString correctPasswordHash = "03ac674216f3e15c761ee1a5e255f067953623c8b388b4459e13f978d7c846f4"; // hash SHA256 dla "1234"

    if (login == correctLogin && hashPassword(haslo) == correctPasswordHash) {
        accept();
    } else {
        QMessageBox::warning(this, "Błąd logowania", "Nieprawidłowy login lub hasło.");
    }
}

void Logowanie::on_pushButtonAnuluj_clicked()
{
    reject();
}
