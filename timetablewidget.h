#ifndef TIME_TABLE_WIDGET_H
#define TIME_TABLE_WIDGET_H

#include "zajecia.h"

#include <QDateTime>
#include <QString>
#include <QWidget>
#include <vector>

class TimetableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TimetableWidget(QWidget *parent = nullptr);

    void setZajecia(const std::vector<Zajecia> &zajecia);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    std::vector<Zajecia> m_zajecia;
    QSize sizeHint() const override;
};

#endif // TIME_TABLE_WIDGET_H
