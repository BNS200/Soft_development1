#ifndef LOGGER_H
#define LOGGER_H
#include <QObject>

class logger : public QObject
{
public:
    explicit logger(QObject* parent = nullptr);

private:


public slots:
    void logChanged(const QString& fileName, size_t size);
    void logDeleted(const QString& fileName);
    void logExists(const QString& fileName, size_t size);
    void logNotExists(const QString& fileName);
    void logModified(const QString& fileName, size_t size);

};

#endif // LOGGER_H
