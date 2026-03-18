#ifndef LOGGER_H
#define LOGGER_H
#include <QObject>
#include <QString>
#include <QDateTime>
#include <QDebug>



class logger : public QObject
{
    Q_OBJECT;
public:
    explicit logger(QObject* parent);

public slots:
    void logChanged(const QString& fileName, qint64 size);
    void logDeleted(const QString& fileName);
    void logExists(const QString& fileName, qint64 size);
    void logNotExists(const QString& fileName);
    void logCreated(const QString& fileName, qint64 size);

private:
    void print(const QString& message);
    QString formatSize(qint64 size);
};

#endif // LOGGER_H
