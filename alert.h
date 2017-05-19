#ifndef ALERT_H
#define ALERT_H

#include <QObject>

class Alert : public QObject
{
    Q_OBJECT
public:
    explicit Alert(QObject *parent = 0);
    ~Alert();

signals:

public slots:
    void a();
};

#endif // ALERT_H
