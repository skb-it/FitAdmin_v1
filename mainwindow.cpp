#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "czlonkowie_manager.h"

extern CzlonkowieManager czlonkowieManager;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->toolButtonPanel, &QToolButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentIndex(0);  // Przełącz na stronę 0
    });

    connect(ui->toolButtonCzlonkowie, &QToolButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentIndex(1);  // Przełącz na stronę 1 (np. członkowie)
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_toolButtonDodajCzlonka_clicked()
{
    QString imie = ui->lineEditImie->text();
    QString nazwisko = ui->lineEditNazwisko->text();

    // Data wygaśnięcia - np. za 1 miesiąc od teraz
    QDateTime dataWygasniecia = QDateTime::currentDateTime().addMonths(1);

    // Tworzymy obiekt Czlonek - numer karnetu i data aktywacji ustawiane automatycznie
    Czlonek nowyCzlonek(imie.toStdString(), nazwisko.toStdString(), true, dataWygasniecia);

    // Dodajemy do managera
    czlonkowieManager.dodajCzlonka(nowyCzlonek);

    // Dodajemy do tabeli (pamiętaj, że numer karnetu i data aktywacji są w obiekcie)
    int row = ui->tableWidgetCzlonkowie->rowCount();
    ui->tableWidgetCzlonkowie->insertRow(row);
    ui->tableWidgetCzlonkowie->setItem(row, 0, new QTableWidgetItem(imie));
    ui->tableWidgetCzlonkowie->setItem(row, 1, new QTableWidgetItem(nazwisko));
    ui->tableWidgetCzlonkowie->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(nowyCzlonek.getNumerKarnetu())));
    ui->tableWidgetCzlonkowie->setItem(row, 3, new QTableWidgetItem("Tak"));  // zawsze aktywny
    ui->tableWidgetCzlonkowie->setItem(row, 4, new QTableWidgetItem(nowyCzlonek.getDataAktywacji().toString("yyyy-MM-dd hh:mm")));
    ui->tableWidgetCzlonkowie->setItem(row, 5, new QTableWidgetItem(dataWygasniecia.toString("yyyy-MM-dd hh:mm")));

    // Czyszczenie pól
    ui->lineEditImie->clear();
    ui->lineEditNazwisko->clear();

    // Data aktywacji nie potrzebna, ale ustaw datę wygaśnięcia na GUI, jeśli masz takie pole
    ui->dateTimeEditWygasniecie->setDateTime(QDateTime::currentDateTime().addMonths(1));
}

