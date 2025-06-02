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

    ui->stackedWidget->setCurrentIndex(0); // zawsze ustawiaj stronę 0 po uruchomieniu aplikacji
    connect(ui->toolButtonPanel, &QToolButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentIndex(0);  // Przełącz na stronę 0
    });

    connect(ui->toolButtonCzlonkowie, &QToolButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentIndex(1);  // Przełącz na stronę 1 (np. członkowie)
        ui->comboBoxKarnet->clear();
        for (const auto& k : karnetyManager.getKarnety()) {
            if(k.isAktywny()){
                ui->comboBoxKarnet->addItem(k.getNazwa());
            }
        }
    });

    connect(ui->toolButtonKarnety, &QToolButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentIndex(2);
        karnetyManager.wczytajZPliku("karnety.txt");
        odswiezTabeleKarnety();
    });

    connect(ui->toolButtonDodajKarnet, &QToolButton::clicked, this, &MainWindow::on_toolButtonDodajKarnet_clicked);
    connect(ui->toolButtonUsunKarnet, &QToolButton::clicked, this, &MainWindow::on_toolButtonUsunKarnet_clicked);
    connect(ui->lineEditSzukajKarnet, &QLineEdit::textChanged, this, &MainWindow::on_lineEditSzukajKarnet_textChanged);
    connect(ui->tableWidgetKarnety, &QTableWidget::itemSelectionChanged, this, &MainWindow::on_tableWidgetKarnety_itemSelectionChanged);
    connect(ui->toolButtonDodajKarnet, &QToolButton::clicked, this, &MainWindow::on_toolButtonDodajKarnet_clicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_toolButtonDodajCzlonka_clicked()
{
    QString imie = ui->lineEditImie->text();
    QString nazwisko = ui->lineEditNazwisko->text();

    // Pobierz wybrany karnet z comboBox
    QString nazwaKarnetu = ui->comboBoxKarnet->currentText();

    // Możesz znaleźć wybrany karnet w managerze, aby ustawić czas trwania
    int idx = ui->comboBoxKarnet->currentIndex();
    if (idx < 0) {
        QMessageBox::warning(this, "Błąd", "Wybierz karnet!");
        return;
    }
    const Karnet& wybranyKarnet = karnetyManager.getKarnety()[idx];

    // Data wygaśnięcia zależna od wybranego karnetu
    QDateTime dataWygasniecia = QDateTime::currentDateTime().addDays(wybranyKarnet.getCzasTrwania());

    // Tworzymy obiekt Czlonek z nazwą karnetu
    Czlonek nowyCzlonek(imie.toStdString(), nazwisko.toStdString(), true, dataWygasniecia, nazwaKarnetu.toStdString(), wybranyKarnet.getLimitWejsc());

    // Dodaj do managera
    czlonkowieManager.dodajCzlonka(nowyCzlonek);

    // Dodaj do tabeli (bez numeru karnetu)
    int row = ui->tableWidgetCzlonkowie->rowCount();
    ui->tableWidgetCzlonkowie->insertRow(row);
    ui->tableWidgetCzlonkowie->setItem(row, 0, new QTableWidgetItem(imie));
    ui->tableWidgetCzlonkowie->setItem(row, 1, new QTableWidgetItem(nazwisko));
    ui->tableWidgetCzlonkowie->setItem(row, 2, new QTableWidgetItem(nazwaKarnetu));
    ui->tableWidgetCzlonkowie->setItem(row, 3, new QTableWidgetItem("Tak"));
    ui->tableWidgetCzlonkowie->setItem(row, 4, new QTableWidgetItem(QString::number(nowyCzlonek.getPozostalychWejsc())));
    ui->tableWidgetCzlonkowie->setItem(row, 5, new QTableWidgetItem(dataWygasniecia.toString("yyyy-MM-dd hh:mm")));

    // Czyszczenie pól
    ui->lineEditImie->clear();
    ui->lineEditNazwisko->clear();

    // Ustaw domyślną datę wygaśnięcia na GUI, jeśli masz takie pole
    ui->dateTimeEditWygasniecie->setDateTime(QDateTime::currentDateTime().addDays(wybranyKarnet.getCzasTrwania()));
}


void MainWindow::on_toolButtonDodajKarnet_clicked()
{
    wyczyscFormularzKarnet();
    wybranyKarnet = -1;
    ui->tableWidgetKarnety->clearSelection();
}

void MainWindow::on_toolButtonZapiszKarnet_clicked()
{
    QString nazwa = ui->lineEditNazwaKarnetu->text();
    double cena = ui->doubleSpinBoxCena->value();
    int czasTrwania = ui->spinBoxCzasTrwania->value();
    int limitWejsc = ui->spinBoxLimitWejsc->value();
    bool aktywny = (ui->comboBoxStatus->currentText() == "Aktywny");

    if(nazwa.isEmpty()) {
        QMessageBox::warning(this, "Błąd", "Wprowadź nazwę karnetu!");
        return;
    }

    Karnet nowyKarnet(nazwa, cena, czasTrwania, limitWejsc, aktywny);

    if(wybranyKarnet == -1) { // Dodawanie nowego
        karnetyManager.dodajKarnet(nowyKarnet);
    } else { // Edycja istniejącego
        auto &karnety = karnetyManager.getKarnety();
        if(wybranyKarnet >= 0 && wybranyKarnet < (int)karnety.size()) {
            karnety[wybranyKarnet] = nowyKarnet;
        }
    }
    karnetyManager.zapiszDoPliku("karnety.txt");
    odswiezTabeleKarnety();
    wyczyscFormularzKarnet();
    wybranyKarnet = -1;
    ui->tableWidgetKarnety->clearSelection();
}

void MainWindow::on_toolButtonUsunKarnet_clicked()
{
    if(wybranyKarnet >= 0) {
        karnetyManager.usunKarnet(wybranyKarnet);
        karnetyManager.zapiszDoPliku("karnety.txt");
        odswiezTabeleKarnety();
        wyczyscFormularzKarnet();
        wybranyKarnet = -1;
        ui->tableWidgetKarnety->clearSelection();
    } else {
        QMessageBox::warning(this, "Błąd", "Wybierz karnet do usunięcia!");
    }
}

void MainWindow::on_toolButtonDezaktywujKarnet_clicked()
{
    if(wybranyKarnet >= 0) {
        auto &karnety = karnetyManager.getKarnety();
        karnety[wybranyKarnet].setAktywny(false);
        karnetyManager.zapiszDoPliku("karnety.txt");
        odswiezTabeleKarnety();
    } else {
        QMessageBox::warning(this, "Błąd", "Wybierz karnet do dezaktywacji!");
    }
}

void MainWindow::on_lineEditSzukajKarnet_textChanged(const QString &text)
{
    odswiezTabeleKarnety();
}

void MainWindow::on_tableWidgetKarnety_itemSelectionChanged()
{
    auto selected = ui->tableWidgetKarnety->selectedItems();
    if(selected.size() > 0) {
        int row = ui->tableWidgetKarnety->currentRow();
        auto &karnety = karnetyManager.getKarnety();
        // row odpowiada indeksowi w filteredList, potrzebujemy prawdziwego indeksu!
        // Dlatego w odswiezTabeleKarnety() przechowamy mapowanie:
        if(row >= 0 && row < filteredIndexes.size()) {
            wybranyKarnet = filteredIndexes[row];
            const Karnet &k = karnety[wybranyKarnet];
            ui->lineEditNazwaKarnetu->setText(k.getNazwa());
            ui->doubleSpinBoxCena->setValue(k.getCena());
            ui->spinBoxCzasTrwania->setValue(k.getCzasTrwania());
            ui->spinBoxLimitWejsc->setValue(k.getLimitWejsc());
            ui->comboBoxStatus->setCurrentIndex(k.isAktywny() ? 0 : 1);
        }
    }
}

void MainWindow::odswiezTabeleKarnety()
{
    QString filter = ui->lineEditSzukajKarnet->text().trimmed().toLower();
    auto &lista = karnetyManager.getKarnety();
    ui->tableWidgetKarnety->setRowCount(0);
    filteredIndexes.clear();

    for(int i = 0; i < (int)lista.size(); ++i) {
        if(!filter.isEmpty() && !lista[i].getNazwa().toLower().contains(filter))
            continue;
        int row = ui->tableWidgetKarnety->rowCount();
        ui->tableWidgetKarnety->insertRow(row);
        ui->tableWidgetKarnety->setItem(row, 0, new QTableWidgetItem(lista[i].getNazwa()));
        ui->tableWidgetKarnety->setItem(row, 1, new QTableWidgetItem(QString::number(lista[i].getCena(), 'f', 2)));
        ui->tableWidgetKarnety->setItem(row, 2, new QTableWidgetItem(QString::number(lista[i].getCzasTrwania()) + " dni"));
        ui->tableWidgetKarnety->setItem(row, 3, new QTableWidgetItem(lista[i].getLimitWejsc() == 0 ? "Nielimitowane" : QString::number(lista[i].getLimitWejsc())));
        ui->tableWidgetKarnety->setItem(row, 4, new QTableWidgetItem(lista[i].isAktywny() ? "Aktywny" : "Nieaktywny"));
        filteredIndexes.append(i); // zapamiętaj rzeczywisty indeks w managerze
    }
}

// Pomocnicza funkcja do czyszczenia formularza:
void MainWindow::wyczyscFormularzKarnet()
{
    ui->lineEditNazwaKarnetu->clear();
    ui->doubleSpinBoxCena->setValue(0);
    ui->spinBoxCzasTrwania->setValue(1);
    ui->spinBoxLimitWejsc->setValue(0);
    ui->comboBoxStatus->setCurrentIndex(0);
}
