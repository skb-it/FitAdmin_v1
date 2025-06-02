#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "karnety_manager.h"
#include "timetablewidget.h"
#include "trenerzy_manager.h"
#include "zajecia_manager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_toolButtonDodajCzlonka_clicked();
    void on_toolButtonDodajKarnet_clicked();
    void on_toolButtonZapiszKarnet_clicked();
    void on_toolButtonUsunKarnet_clicked();
    void on_toolButtonDezaktywujKarnet_clicked();
    void on_lineEditSzukajKarnet_textChanged(const QString &text);
    void on_tableWidgetKarnety_itemSelectionChanged();
    void on_toolButtonDodajZajecia_clicked();
    void on_toolButtonDodajTrenera_clicked();
    void on_toolButtonUsunZajecia_clicked();
    void on_toolButtonWyloguj_clicked();
    void on_toolButtonSklep_clicked();

private:
    Ui::MainWindow *ui;

private:
    TimetableWidget *timetable;
    QVector<int> filteredIndexes;
    void odswiezTabeleCzlonkowie();
    void odswiezTabeleKarnety();
    void wyczyscFormularzKarnet();
    int wybranyKarnet = -1; // -1 = tryb dodawania, >=0 = edycja istniejącego
    KarnetyManager karnetyManager;
    TrenerzyManager trenerzyManager;
    ZajeciaManager zajeciaManager;
    int kolejnyIdTrenera = 1;

    void odswiezComboBoxTrenerzyZajecia();
    void odswiezTabeleZajecia();
    void odswiezTabeleTrenerzy();
};

#endif // MAINWINDOW_H
