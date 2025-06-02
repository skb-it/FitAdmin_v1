#include "timetablewidget.h"
#include <QPainter>
#include <QFontMetrics>
#include <QDateTime>
#include <QColor>

static int dzienTygodnia(const QDateTime& dt) {
    int qt = dt.date().dayOfWeek(); // Qt: 1=pon, 7=ndz
    return qt - 1;
}

TimetableWidget::TimetableWidget(QWidget* parent)
    : QWidget(parent)
{}

void TimetableWidget::setZajecia(const std::vector<Zajecia>& zajecia)
{
    m_zajecia = zajecia;
    update();
}

void TimetableWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    const int godzinaStart = 6;
    const int godzinaEnd = 22;
    const int liczbaGodzin = godzinaEnd - godzinaStart;
    const int liczbaDni = 7;

    const int leftMargin = 60;
    const int topMargin = 30;
    const int bottomMargin = 30;
    const int rightMargin = 10;
    const int cellWidth = (width() - leftMargin - rightMargin) / liczbaDni;
    const int cellHeight = (height() - topMargin - bottomMargin) / liczbaGodzin;

    QPainter p(this);
    p.fillRect(rect(), Qt::white);

    QFont font = p.font();
    font.setPointSize(9);
    p.setFont(font);

    // Oś Y - godziny
    for (int h = godzinaStart; h <= godzinaEnd; ++h) {
        int y = topMargin + (h - godzinaStart) * cellHeight;
        p.setPen(Qt::gray);
        p.drawLine(leftMargin, y, width()-rightMargin, y);
        p.setPen(Qt::black);
        p.drawText(8, y+cellHeight/2+4, QString("%1:00").arg(h));
    }

    // Oś X - dni tygodnia
    QStringList dni = { "Pon", "Wt", "Śr", "Czw", "Pt", "Sob", "Nd" };
    for (int d = 0; d < liczbaDni; ++d) {
        int x = leftMargin + d * cellWidth;
        p.setPen(Qt::gray);
        p.drawLine(x, topMargin, x, height()-bottomMargin);
        p.setPen(Qt::black);
        p.drawText(x + cellWidth/2 - 18, topMargin - 8, dni[d]);
    }

    // Zajęcia
    for (const auto& z : m_zajecia) {
        int d = dzienTygodnia(z.getStart());
        if (d < 0 || d > 6) continue;

        int startGodzina = z.getStart().time().hour();
        int startMinuta = z.getStart().time().minute();
        int endGodzina = z.getEnd().time().hour();
        int endMinuta = z.getEnd().time().minute();

        double y_start = topMargin + ((startGodzina + startMinuta/60.0) - godzinaStart) * cellHeight;
        double y_end = topMargin + ((endGodzina + endMinuta/60.0) - godzinaStart) * cellHeight;
        double x = leftMargin + d * cellWidth + 2;
        double w = cellWidth - 4;
        double h = y_end - y_start;

        QRectF zajRect(x, y_start, w, h);
        qDebug() << zajRect;

        QColor color = QColor::fromHsv((d*40)%360, 120+((d*37)%100), 235);
        p.setBrush(color.lighter(130));
        p.setPen(Qt::darkGray);
        p.drawRect(zajRect);

        p.setPen(Qt::black);
        QString txt = QString("%1\n%2-%3\n%4 (%5/%6)")
                          .arg(z.getTrenerImieNazwisko())
                          .arg(z.getStart().time().toString("HH:mm"))
                          .arg(z.getEnd().time().toString("HH:mm"))
                          .arg(z.getSala())
                          .arg(z.getWolnychMiejsc())
                          .arg(z.getLimitMiejsc());

        QFontMetrics fm(p.font());
        p.drawText(zajRect, Qt::AlignCenter|Qt::TextWordWrap, txt);
    }

    p.setBrush(Qt::NoBrush);
    p.setPen(Qt::black);
    p.drawRect(leftMargin, topMargin, liczbaDni*cellWidth, liczbaGodzin*cellHeight);
}

QSize TimetableWidget::sizeHint() const
{
    return QSize(700, 600);
}
