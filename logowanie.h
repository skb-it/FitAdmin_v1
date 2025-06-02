#ifndef LOGOWANIE_H
#define LOGOWANIE_H

#include <QDialog>

namespace Ui {
class Logowanie;
}

class Logowanie : public QDialog
{
    Q_OBJECT

public:
    explicit Logowanie(QWidget *parent = nullptr);
    ~Logowanie();

private slots:
    void on_pushButtonZaloguj_clicked();
    void on_pushButtonAnuluj_clicked();

private:
    Ui::Logowanie *ui;
};

#endif // LOGOWANIE_H
