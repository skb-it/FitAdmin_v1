#include "logowanie.h"
#include "./ui_logowanie.h"

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
