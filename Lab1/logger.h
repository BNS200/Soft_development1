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
    explicit logger(QObject* parent); // Конструктор без приведения типов

public slots:

    // Слоты для обработки различных событий
    void logChanged(const QString& fileName, qint64 size);
    void logDeleted(const QString& fileName);
    void logExists(const QString& fileName, qint64 size);
    void logNotExists(const QString& fileName);
    void logCreated(const QString& fileName, qint64 size);

private:
    void print(const QString& message); // Вывод  в консоль
    QString formatSize(qint64 size); // Форматирование вывода в консоль
};

#endif // LOGGER_H
