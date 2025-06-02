#include "mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "czlonkowie_manager.h"
#include "timetablewidget.h"
#include "ui_mainwindow.h"
#include "sprzet_manager.h"

extern CzlonkowieManager czlonkowieManager;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timetable = new TimetableWidget;
    ui->verticalLayoutWykresZajec->addWidget(timetable);

    karnetyManager.wczytajZPliku("karnety.txt");
    ui->stackedWidget->setCurrentIndex(0); // zawsze ustawiaj stronę 0 po uruchomieniu aplikacji
    connect(ui->toolButtonPanel, &QToolButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->mainPage);
    });

    connect(ui->toolButtonCzlonkowie, &QToolButton::clicked, this, [this]() {
        czlonkowieManager.wczytajZPliku("czlonkowie.txt");
        odswiezTabeleCzlonkowie();
        ui->dateTimeEditRozpoczecie->setMinimumDate(QDate::currentDate());
        ui->dateTimeEditRozpoczecie->setDate(QDate::currentDate());
        ui->stackedWidget->setCurrentWidget(ui->czlonkowieStrona);
        ui->comboBoxKarnet->clear();
        for (const auto &k : karnetyManager.getKarnety()) {
            if (k.isAktywny()) {
                ui->comboBoxKarnet->addItem(k.getNazwa());
            }
        }
    });

    connect(ui->toolButtonKarnety, &QToolButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->karnetyStrona);
        karnetyManager.wczytajZPliku("karnety.txt");
        odswiezTabeleKarnety();
    });

    connect(ui->toolButtonDodajKarnet,
            &QToolButton::clicked,
            this,
            &MainWindow::on_toolButtonDodajKarnet_clicked);
    connect(ui->toolButtonUsunKarnet,
            &QToolButton::clicked,
            this,
            &MainWindow::on_toolButtonUsunKarnet_clicked);
    connect(ui->lineEditSzukajKarnet,
            &QLineEdit::textChanged,
            this,
            &MainWindow::on_lineEditSzukajKarnet_textChanged);
    connect(ui->tableWidgetKarnety,
            &QTableWidget::itemSelectionChanged,
            this,
            &MainWindow::on_tableWidgetKarnety_itemSelectionChanged);

    trenerzyManager.wczytajZPliku("trenerzy.txt");
    zajeciaManager.wczytajZPliku("zajecia.txt");

    connect(ui->toolButtonTrenerzy, &QToolButton::clicked, this, [this]() {
        trenerzyManager.wczytajZPliku("trenerzy.txt");
        odswiezTabeleTrenerzy();
        ui->stackedWidget->setCurrentWidget(ui->trenerzyStrona);
    });

    connect(ui->toolButtonZajecia, &QToolButton::clicked, this, [this]() {
        zajeciaManager.wczytajZPliku("zajecia.txt");
        odswiezTabeleZajecia();
        odswiezComboBoxTrenerzyZajecia();
        ui->dateTimeEditStart->setDateTime(QDateTime::currentDateTime());
        ui->dateTimeEditEnd->setDateTime(QDateTime::currentDateTime());
        ui->stackedWidget->setCurrentWidget(ui->zajeciaStrona);
        timetable->setZajecia(zajeciaManager.getZajecia());
    });

    connect(ui->toolButtonDodajTrenera,
            &QToolButton::clicked,
            this,
            &MainWindow::on_toolButtonDodajTrenera_clicked);

    connect(ui->toolButtonEdytuj, &QToolButton::clicked, this, [=]() {
        int row = ui->tableWidgetSprzet->currentRow();
        if (row < 0) return;

        QString nazwa = ui->tableWidgetSprzet->item(row, 1)->text();
        int ilosc = ui->tableWidgetSprzet->item(row, 2)->text().toInt();
        QString stan = ui->tableWidgetSprzet->item(row, 3)->text();
        QDate przeglad = QDate::fromString(ui->tableWidgetSprzet->item(row, 4)->text(), "yyyy-MM-dd");

        SprzetManager dialog(this);
        dialog.ustawDane(nazwa, ilosc, stan, przeglad);

        if (dialog.exec() == QDialog::Accepted) {
            ui->tableWidgetSprzet->setItem(row, 1, new QTableWidgetItem(dialog.pobierzNazwa()));
            ui->tableWidgetSprzet->setItem(row, 2, new QTableWidgetItem(QString::number(dialog.pobierzIlosc())));
            ui->tableWidgetSprzet->setItem(row, 3, new QTableWidgetItem(dialog.pobierzStan()));
            ui->tableWidgetSprzet->setItem(row, 4, new QTableWidgetItem(dialog.pobierzData().toString("yyyy-MM-dd")));
        }

    });

    connect(ui->toolButtonSprzet, &QToolButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentWidget(ui->sprzetStrona);
    });

    connect(ui->toolButtonEdytuj, &QToolButton::clicked, this, [=]() {
        int row = ui->tableWidgetSprzet->currentRow();
        if (row < 0) return;

        QString nazwa = ui->tableWidgetSprzet->item(row, 1)->text();
        int ilosc = ui->tableWidgetSprzet->item(row, 2)->text().toInt();
        QString stan = ui->tableWidgetSprzet->item(row, 3)->text();
        QDate przeglad = QDate::fromString(ui->tableWidgetSprzet->item(row, 4)->text(), "yyyy-MM-dd");

        SprzetManager dialog(this);
        dialog.ustawDane(nazwa, ilosc, stan, przeglad);

        if (dialog.exec() == QDialog::Accepted) {
            ui->tableWidgetSprzet->setItem(row, 1, new QTableWidgetItem(dialog.pobierzNazwa()));
            ui->tableWidgetSprzet->setItem(row, 2, new QTableWidgetItem(QString::number(dialog.pobierzIlosc())));
            ui->tableWidgetSprzet->setItem(row, 3, new QTableWidgetItem(dialog.pobierzStan()));
            ui->tableWidgetSprzet->setItem(row, 4, new QTableWidgetItem(dialog.pobierzData().toString("yyyy-MM-dd")));
        }
    });

    connect(ui->toolButtonDodaj, &QToolButton::clicked, this, [=]() {
        int row = ui->tableWidgetSprzet->rowCount();
        ui->tableWidgetSprzet->insertRow(row);

        ui->tableWidgetSprzet->setItem(row, 0, new QTableWidgetItem(QString::number(row + 1))); // ID
        ui->tableWidgetSprzet->setItem(row, 1, new QTableWidgetItem("Nowy sprzęt"));
        ui->tableWidgetSprzet->setItem(row, 2, new QTableWidgetItem("1"));
        ui->tableWidgetSprzet->setItem(row, 3, new QTableWidgetItem("Sprawny"));
        ui->tableWidgetSprzet->setItem(row, 4, new QTableWidgetItem(QDate::currentDate().toString("yyyy-MM-dd")));
    });

    connect(ui->toolButtonUsun, &QToolButton::clicked, this, [=]() {
        int row = ui->tableWidgetSprzet->currentRow();
        if (row >= 0) {
            ui->tableWidgetSprzet->removeRow(row);
        }
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
    if (imie.trimmed().isEmpty() || nazwisko.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Błąd", "Imie oraz Nazwisko nie mogą być puste!");
        return;
    }

    QString nazwaKarnetu = ui->comboBoxKarnet->currentText();

    int idx = ui->comboBoxKarnet->currentIndex();
    if (idx < 0) {
        QMessageBox::warning(this, "Błąd", "Wybierz karnet!");
        return;
    }
    const Karnet &wybranyKarnet = karnetyManager.getKarnety()[idx];

    QDate dataRozpoczecia = ui->dateTimeEditRozpoczecie->date();
    QDate dataWygasniecia = dataRozpoczecia.addDays(wybranyKarnet.getCzasTrwania());

    Czlonek nowyCzlonek(imie.toStdString(),
                        nazwisko.toStdString(),
                        true,
                        dataRozpoczecia,
                        dataWygasniecia,
                        nazwaKarnetu.toStdString(),
                        wybranyKarnet.getLimitWejsc());

    czlonkowieManager.dodajCzlonka(nowyCzlonek);
    czlonkowieManager.zapiszDoPliku("czlonkowie.txt");

    odswiezTabeleCzlonkowie();

    ui->lineEditImie->clear();
    ui->lineEditNazwisko->clear();

    ui->dateTimeEditRozpoczecie->setDate(QDate::currentDate());
}

void MainWindow::on_toolButtonUsunZajecia_clicked()
{
    auto selectedRanges = ui->tableWidgetZajecia->selectedRanges();
    if (selectedRanges.isEmpty()) {
        QMessageBox::warning(this, "Błąd", "Wybierz zajęcia do usunięcia!");
        return;
    }

    // Zbieramy wszystkie wybrane wiersze (bez powtórzeń)
    QSet<int> rowsToDelete;
    for (const QTableWidgetSelectionRange &range : selectedRanges) {
        for (int row = range.topRow(); row <= range.bottomRow(); ++row)
            rowsToDelete.insert(row);
    }

    // Usuwamy od końca, by nie przesuwać indeksów
    QList<int> sortedRows = rowsToDelete.values();
    std::sort(sortedRows.begin(), sortedRows.end(), std::greater<int>());

    auto &zajecia = zajeciaManager.getZajecia();

    for (int row : sortedRows) {
        if (row >= 0 && row < zajecia.size()) {
            zajeciaManager.usunZajecia(row);
        }
    }

    zajeciaManager.zapiszDoPliku("zajecia.txt");
    odswiezTabeleZajecia();
    timetable->setZajecia(zajeciaManager.getZajecia());
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

    if (nazwa.isEmpty()) {
        QMessageBox::warning(this, "Błąd", "Wprowadź nazwę karnetu!");
        return;
    }

    Karnet nowyKarnet(nazwa, cena, czasTrwania, limitWejsc, aktywny);

    if (wybranyKarnet == -1) { // Dodawanie nowego
        karnetyManager.dodajKarnet(nowyKarnet);
    } else { // Edycja istniejącego
        auto &karnety = karnetyManager.getKarnety();
        if (wybranyKarnet >= 0 && wybranyKarnet < (int) karnety.size()) {
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
    if (wybranyKarnet >= 0) {
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
    if (wybranyKarnet >= 0) {
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
    if (selected.size() > 0) {
        int row = ui->tableWidgetKarnety->currentRow();
        auto &karnety = karnetyManager.getKarnety();
        // row odpowiada indeksowi w filteredList, potrzebujemy prawdziwego indeksu!
        // Dlatego w odswiezTabeleKarnety() przechowamy mapowanie:
        if (row >= 0 && row < filteredIndexes.size()) {
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

void MainWindow::on_toolButtonDodajTrenera_clicked()
{
    QString imie = ui->lineEditImieTrener->text();
    QString nazwisko = ui->lineEditNazwiskoTrener->text();
    if (imie.trimmed().isEmpty() || nazwisko.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Błąd", "Imię i nazwisko nie mogą być puste!");
        return;
    }
    Trener t(kolejnyIdTrenera++, imie.toStdString(), nazwisko.toStdString());
    trenerzyManager.dodajTrenera(t);
    trenerzyManager.zapiszDoPliku("trenerzy.txt");
    odswiezTabeleTrenerzy();
    ui->lineEditImieTrener->clear();
    ui->lineEditNazwiskoTrener->clear();
}

void MainWindow::on_toolButtonDodajZajecia_clicked()
{
    int trenerIdx = ui->comboBoxTrenerProwadzacy->currentIndex();
    if (trenerIdx < 0 || trenerIdx >= trenerzyManager.getTrenerzy().size()) {
        QMessageBox::warning(this, "Błąd", "Wybierz trenera!");
        return;
    }
    const Trener &trener = trenerzyManager.getTrenerzy()[trenerIdx];
    QDateTime start = ui->dateTimeEditStart->dateTime();
    QDateTime end = ui->dateTimeEditEnd->dateTime();
    QString sala = ui->lineEditSala->text();
    int limit = ui->spinBoxLimitMiejsc->value();
    if (limit < 1) {
        QMessageBox::warning(this, "Błąd", "Limit miejsc musi być większy od zera!");
        return;
    }
    if (start >= end) {
        QMessageBox::warning(this, "Błąd", "Data zakończenia musi być po rozpoczęciu!");
        return;
    }
    Zajecia z(trener.getId(),
              QString::fromStdString(trener.getImie() + " " + trener.getNazwisko()),
              start,
              end,
              sala,
              limit);
    zajeciaManager.dodajZajecia(z);
    zajeciaManager.zapiszDoPliku("zajecia.txt");
    odswiezTabeleZajecia();
}

void MainWindow::odswiezTabeleTrenerzy()
{
    ui->tableWidgetTrenerzy->setRowCount(0);
    auto lista = trenerzyManager.getTrenerzy();
    for (const auto &t : lista) {
        int row = ui->tableWidgetTrenerzy->rowCount();
        ui->tableWidgetTrenerzy->insertRow(row);
        ui->tableWidgetTrenerzy->setItem(row, 0, new QTableWidgetItem(QString::number(t.getId())));
        ui->tableWidgetTrenerzy->setItem(row,
                                         1,
                                         new QTableWidgetItem(QString::fromStdString(t.getImie())));
        ui->tableWidgetTrenerzy
            ->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(t.getNazwisko())));
    }
}

void MainWindow::odswiezComboBoxTrenerzyZajecia()
{
    ui->comboBoxTrenerProwadzacy->clear();
    for (const auto &t : trenerzyManager.getTrenerzy()) {
        ui->comboBoxTrenerProwadzacy->addItem(QString::number(t.getId()) + " - "
                                              + QString::fromStdString(t.getImie()) + " "
                                              + QString::fromStdString(t.getNazwisko()));
    }
}

void MainWindow::odswiezTabeleZajecia()
{
    ui->tableWidgetZajecia->setRowCount(0);
    for (const auto &z : zajeciaManager.getZajecia()) {
        int row = ui->tableWidgetZajecia->rowCount();
        ui->tableWidgetZajecia->insertRow(row);
        ui->tableWidgetZajecia->setItem(row, 0, new QTableWidgetItem(z.getTrenerImieNazwisko()));
        ui->tableWidgetZajecia
            ->setItem(row, 1, new QTableWidgetItem(z.getStart().toString("yyyy-MM-dd HH:mm")));
        ui->tableWidgetZajecia
            ->setItem(row, 2, new QTableWidgetItem(z.getEnd().toString("yyyy-MM-dd HH:mm")));
        ui->tableWidgetZajecia->setItem(row, 3, new QTableWidgetItem(z.getSala()));
        ui->tableWidgetZajecia->setItem(row,
                                        4,
                                        new QTableWidgetItem(QString::number(z.getLimitMiejsc())));
        ui->tableWidgetZajecia->setItem(row,
                                        5,
                                        new QTableWidgetItem(QString::number(z.getWolnychMiejsc())));
    }
}

void MainWindow::odswiezTabeleKarnety()
{
    QString filter = ui->lineEditSzukajKarnet->text().trimmed().toLower();
    auto &lista = karnetyManager.getKarnety();
    ui->tableWidgetKarnety->setRowCount(0);
    filteredIndexes.clear();

    for (int i = 0; i < (int) lista.size(); ++i) {
        if (!filter.isEmpty() && !lista[i].getNazwa().toLower().contains(filter))
            continue;
        int row = ui->tableWidgetKarnety->rowCount();
        ui->tableWidgetKarnety->insertRow(row);
        ui->tableWidgetKarnety->setItem(row, 0, new QTableWidgetItem(lista[i].getNazwa()));
        ui->tableWidgetKarnety
            ->setItem(row, 1, new QTableWidgetItem(QString::number(lista[i].getCena(), 'f', 2)));
        ui->tableWidgetKarnety->setItem(row,
                                        2,
                                        new QTableWidgetItem(
                                            QString::number(lista[i].getCzasTrwania()) + " dni"));
        ui->tableWidgetKarnety->setItem(row,
                                        3,
                                        new QTableWidgetItem(
                                            lista[i].getLimitWejsc() == 0
                                                ? "Nielimitowane"
                                                : QString::number(lista[i].getLimitWejsc())));
        ui->tableWidgetKarnety->setItem(row,
                                        4,
                                        new QTableWidgetItem(lista[i].isAktywny() ? "Aktywny"
                                                                                  : "Nieaktywny"));
        filteredIndexes.append(i); // zapamiętaj rzeczywisty indeks w managerze
    }
}

void MainWindow::odswiezTabeleCzlonkowie()
{
    ui->tableWidgetCzlonkowie->setRowCount(0);
    auto lista = czlonkowieManager.getCzlonkowie();
    QDate currentTime = QDate::currentDate();
    for (int i = 0; i < (int) lista.size(); ++i) {
        int row = ui->tableWidgetCzlonkowie->rowCount();
        ui->tableWidgetCzlonkowie->insertRow(row);
        Czlonek czlonek = lista.at(i);
        bool aktywny = czlonek.getDataWygasniecia() >= currentTime
                       && currentTime >= czlonek.getDataAktywacji();
        ui->tableWidgetCzlonkowie
            ->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(czlonek.getImie())));
        ui->tableWidgetCzlonkowie
            ->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(czlonek.getNazwisko())));
        ui->tableWidgetCzlonkowie->setItem(row,
                                           2,
                                           new QTableWidgetItem(
                                               QString::fromStdString(czlonek.getNazwaKarnetu())));
        ui->tableWidgetCzlonkowie->setItem(row, 3, new QTableWidgetItem(aktywny ? "Tak" : "Nie"));
        ui->tableWidgetCzlonkowie->setItem(row,
                                           4,
                                           new QTableWidgetItem(
                                               czlonek.getDataAktywacji().toString("yyyy-MM-dd")));
        ui->tableWidgetCzlonkowie
            ->setItem(row,
                      5,
                      new QTableWidgetItem(czlonek.getDataWygasniecia().toString("yyyy-MM-dd")));
        ui->tableWidgetCzlonkowie
            ->setItem(row, 6, new QTableWidgetItem(QString::number(czlonek.getPozostalychWejsc())));
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
