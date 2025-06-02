#include "logowanie.h"
#include "ui_logowanie.h"
#include <QMessageBox>
#include <QCryptographicHash>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>

QString hashPassword(const QString &password) {
    QByteArray hashed = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return QString(hashed.toHex());
}

Logowanie::Logowanie(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Logowanie)
{
    ui->setupUi(this);

    QString configPath = "users.txt";
    QFileInfo checkFile(configPath);
    if (!checkFile.exists() || !checkFile.isFile()) {
        QFile file(configPath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << "admin " << "03ac674216f3e15c761ee1a5e255f067953623c8b388b4459e13f978d7c846f4" << "\n"; //admin; 1234
            file.close();
        }
        QMessageBox::warning(this, "Pierwsze uruchomienie", "Używasz domyślnego loginu i hasła. Proszę zmień domyślne hasło po zalogowaniu!");
    }
}

Logowanie::~Logowanie()
{
    delete ui;
}

void Logowanie::on_pushButtonZaloguj_clicked()
{
    QString login = ui->lineEditLogin->text();
    QString haslo = ui->lineEditHaslo->text();

    QFile file("users.txt");
    bool isLogged = false;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(" ");
            if (parts.size() == 2) {
                QString user = parts[0];
                QString passHash = parts[1];
                if (login == user && hashPassword(haslo) == passHash) {
                    isLogged = true;
                    break;
                }
            }
        }
        file.close();
    }

    if (isLogged) {
        accept();
    } else {
        QMessageBox::warning(this, "Błąd logowania", "Nieprawidłowy login lub hasło.");
    }
}

void Logowanie::on_pushButtonAnuluj_clicked()
{
    reject();
}
